#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include "image.h"
#include <pgmspace.h>

#define TFT_SCL         14
#define TFT_SDA         13
#define TFT_CS          15
#define TFT_RST         16
#define TFT_DC          4
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_SDA,TFT_SCL ,TFT_RST);
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
float p = 3.1415926;

void setup(void) {

  tft.initR(INITR_144GREENTAB);
  tft.setRotation(0);
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));
  tft.fillScreen(ST77XX_BLACK);
  drawpicture();
}
  
void loop(){

//testdrawtext("time:2021,5,26", ST77XX_WHITE);

}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(30, 30);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void drawpicture(){
  tft.drawRGBBitmap(0,0,shit,128,128);
}
