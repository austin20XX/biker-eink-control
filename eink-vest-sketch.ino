#include <SPI.h>
#include "Adafruit_EPD.h"
#include "panels/ThinkInk_290_Tricolor_Z10.h"
#include "Featherwing.h"


// 2.9" Tricolor IL0373 chipset
ThinkInk_290_Tricolor_Z10 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS,
EPD_BUSY, EPD_SPI);

int aState, bState, cState = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(EPD_GPIO_A, INPUT_PULLUP);
  pinMode(EPD_GPIO_B, INPUT_PULLUP);
    pinMode(EPD_GPIO_C, INPUT_PULLUP);
  Serial.println("Pin Init");

  //TRICOLOR is the default here but being explicit
  display.begin(THINKINK_TRICOLOR);
  display.clearBuffer();
  //   Serial.println("Clear Buffer.");

  display.setTextSize(2);
  display.setCursor(0,0);
  display.setTextColor(EPD_BLACK);
  display.setTextWrap(true);
  // display.print("Austin Myers1");
  //   Serial.println("Print.");
  display.display();
    Serial.println("Setup Complete.");
}

void loop() {
  // put your main code here, to run repeatedly:
  aState = digitalRead(EPD_GPIO_A);
  bState = digitalRead(EPD_GPIO_B);
  cState = digitalRead(EPD_GPIO_C);
  //It is pulled up HIGH
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
    display.print("Austin Myers C");
    display.display();
  }
  //Slight delay for debouncing? Likely better ways... 
  //DEBOUNCE LIBRARY! bounce2, button
  delay(100);
}
