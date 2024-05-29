#include <SPI.h>
#include "Adafruit_EPD.h"
#include "panels/ThinkInk_290_Tricolor_Z10.h"
#include "Featherwing.h"


#define EPD_DC 10
#define EPD_CS 9
#define EPD_BUSY -1 // can set to -1 to not use a pin (will wait a fixed delay)
#define SRAM_CS 6
#define EPD_RESET -1  // can set to -1 and share with microcontroller Reset!
#define EPD_SPI &SPI // primary SPI
// 2.9" Tricolor IL0373 chipset
ThinkInk_290_Tricolor_Z10 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS,
EPD_BUSY, EPD_SPI);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //TRICOLOR is the default here but being explicit
  display.begin(THINKINK_TRICOLOR);
  display.clearBuffer();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.setTextColor(EPD_RED);
  display.setTextWrap(true);
  display.print("Austin Myers");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
}
