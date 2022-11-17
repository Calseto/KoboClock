#include <Arduino.h>
#include <SPI.h>
#include <LedControl.h>

int DIN = 11;
int CS = 10;
int CLK = 13;
LedControl lc(DIN,CLK,CS,1); 
int active_display=0;

//int Cat[8] ={B10001000,B11111000,B10101000,B01110001,B00100001,B01111001,B01111101,B10111110 };
byte Apple [8]={B00011000,B00001000,B01110110,B11111111,B11111111,B11111111,B01111010,B00110100};

void setup() {
  for(int i=0;i<4;i++){
  lc.shutdown(i,false);
  lc.setIntensity(i,3);
  lc.clearDisplay(i);
  }
  delay(3000);
  for(int i=0;i<8;i++) lc.setRow(active_display,i,Apple[i]);
  delay(3000);
  lc.clearDisplay(0);
  delay(3000);
}
  
void loop(){
  
  for(int i=0;i<8;i++) lc.setRow(active_display,i,Apple[i]);
  delay(3000);
  lc.clearDisplay(active_display);
  active_display++;
  if (active_display==4) active_display=0;
}