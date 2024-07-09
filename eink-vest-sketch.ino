#include <SPI.h>
#include "Adafruit_EPD.h"
#include "panels/ThinkInk_290_Tricolor_Z10.h"
#include "Featherwing.h"

#include <Adafruit_ImageReader_EPD.h>
#include <SdFat.h>


// 2.9" Tricolor IL0373 chipset
ThinkInk_290_Tricolor_Z10 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS,
EPD_BUSY, EPD_SPI);

int aState, bState, cState = 0;

SdFat SD;
Adafruit_ImageReader_EPD reader(SD); // Image-reader object, pass in SD filesys

Adafruit_Image_EPD   img;        // An image loaded into RAM
int32_t              width  = 0, // BMP image dimensions
                     height = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(EPD_GPIO_A, INPUT_PULLUP);
  pinMode(EPD_GPIO_B, INPUT_PULLUP);
    pinMode(EPD_GPIO_C, INPUT_PULLUP);
  Serial.println("Pin Init Complete");

  //TRICOLOR is the default here but being explicit
  display.begin(THINKINK_TRICOLOR);
  display.clearBuffer();
  // display.setTextSize(2);
  // display.setCursor(0,0);
  // display.setTextColor(EPD_BLACK);
  // display.setTextWrap(true);

  display.display();
  Serial.println("Display started.");


  ImageReturnCode stat; // Status from image-reading functions

    if(!SD.begin(SD_CS, SD_SCK_MHZ(10))) { // Breakouts require 10 MHz limit due to longer wires
    Serial.println(F("SD begin() failed"));
    for(;;); // Fatal error, do not continue
    }

  Serial.println(F("OK!"));

  // Load full-screen BMP file 'blinka.bmp' at position (0,0) (top left).
  // Notice the 'reader' object performs this, with 'epd' as an argument.
  Serial.print(F("Loading eye.bmp to canvas..."));
  stat = reader.drawBMP((char *)"/eye.bmp", display, 0, 0);
  reader.printStatus(stat); // How'd we do?
  display.display();

  // Query the dimensions of image 'blinka.bmp' WITHOUT loading to screen:
  Serial.print(F("Querying eye.bmp image size..."));
  stat = reader.bmpDimensions("eye.bmp", &width, &height);
  reader.printStatus(stat);   // How'd we do?
  if(stat == IMAGE_SUCCESS) { // If it worked, print image size...
    Serial.print(F("Image dimensions: "));
    Serial.print(width);
    Serial.write('x');
    Serial.println(height);
  }

  delay(30 * 1000); // Pause 30 seconds before continuing because it's eInk

  Serial.print(F("Drawing canvas to EPD..."));
  display.clearBuffer();

  // Load small BMP 'blinka.bmp' into a GFX canvas in RAM. This should fail
  // gracefully on Arduino Uno and other small devices, meaning the image
  // will not load, but this won't make the program stop or crash, it just
  // continues on without it. Should work on larger ram boards like M4, etc.
  stat = reader.loadBMP("/eye.bmp", img);
  reader.printStatus(stat); // How'd we do?

  Serial.println("Setup Complete.");
}

void loop() {
  // put your main code here, to run repeatedly:
  aState = digitalRead(EPD_GPIO_A);
  bState = digitalRead(EPD_GPIO_B);
  cState = digitalRead(EPD_GPIO_C);
  //It is pulled up HIGH, so low indicates a press
   if (aState == LOW) {
    Serial.println("A");
    display.print("Austin Myers A");  
    display.display();
  }
  else if (bState == LOW) {
    Serial.println("B");
    display.print("Austin Myers B");
    display.display();
  }
  else if (cState == LOW) {
    Serial.println("C");
    // display.print("Austin Myers C");
    display.clearBuffer();
    display.display();
  }
  //Slight delay for debouncing? Likely better ways... 
  //DEBOUNCE LIBRARY! bounce2, button
  delay(100);
}
