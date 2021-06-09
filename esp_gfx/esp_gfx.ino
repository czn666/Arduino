#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
/********************esp32蓝牙配置***************************/
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
/************************************************************/


#define TFT_SCL         14
#define TFT_SDA         13
#define TFT_CS          15
#define TFT_RST         27
#define TFT_DC          2
//#define TFT_BLK         26

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_SDA,TFT_SCL ,TFT_RST);
float p = 3.1415926;
int value=10;
void setup(void) {
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name
}
  
void loop(){
  String str="",opentime="",cpu="",free_="",total="",memory="",now_tim="";
  char ch;
  int indexof[]={0};
  while(SerialBT.available()) {
    str+=char(SerialBT.read());
  }
  for(int i=0,j=0,c=0;i<str.length();i++){
    if(str[i]==','){
      indexof[j]=i;
      j++;      
      split_str(str.substring(c,i));
      c=++i;
    }
    if(i==str.length()-1){
      split_str(str.substring(c,str.length()));
    }
  }
  if(str.length()>0){
    Serial.println(str);
  }
  
 
}
void split_str(String str){
  String str_name="";
  String str_value="";
  if(str.length()>0){
    for(int i=0;i<str.length();i++){
    if(str[i]==':'){
      str_name=str.substring(0,i);
      str_value=str.substring(++i,str.length());
      break;
    }
  }
    if(str_name=="cpu"){
      Serial.println("CPU");
      setText(5,5,str,ST77XX_WHITE);
    }
    else if(str_name=="free"){
      Serial.println("FREE");
     setText(5,15,str,ST77XX_WHITE);
    }
    else if(str_name=="total"){
      Serial.println("TOTAL");
      setText(5,25,str,ST77XX_WHITE);
    }
    else if(str_name=="memory"){
      Serial.println("MEMORY");
      setText(5,35,str,ST77XX_WHITE);
    }else if(str_name=="opentime"){
      Serial.println("OPENTIME");
      setText(5,45,str_name,ST77XX_WHITE);
      setText(5,55,str_value,ST77XX_WHITE);
    }
    else if(str_name=="nowtime"){
      Serial.println("NOWTIME");
      setText(5,65,str_name,ST77XX_WHITE);
      setText(5,75,str_value,ST77XX_WHITE);
    }
  }
  
}
void setText(int x,int y,String str,uint16_t color){
  tft.setCursor(x, y);
  tft.setTextColor(color,ST77XX_BLACK);
  tft.setTextWrap(false);  //设置自动换行。
  tft.print(str);
}


void testdrawtext(int x,int y,char *text, uint16_t color) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);  //设置自动换行。
  tft.print(text);
}
void touch_Pin(){
 Serial.println(touchRead(T0));  // 打印出T0引脚的读数数值信息。
}
