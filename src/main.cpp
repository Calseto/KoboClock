#include <Arduino.h>
#include <SPI.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <virtuabotixRTC.h>


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
int DIN = D7;
int CS = D3;
int CLK = D5;

virtuabotixRTC myRTC(D1,D2,D0);

unsigned long currentM=0;
unsigned long prevM=0;
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS, MAX_DEVICES);

int jam=0;
int menit=0;
int detik=0;

int mode=0;
int mode1=0;

char Fjam[20];
char Fday[20];
char Fdate[20];

String input;

struct animations
{
  textEffect_t   anim_in; // Animation type
  textEffect_t   anim_out;// Animation type
  const char *   textOut;   // Text to display 
  uint16_t       speed;        // Animation speed (multiplier for library default)
  uint16_t       pause;        // pause (multiplier for library default)
  textPosition_t just;
};

animations animList[] =
{
  { PA_NO_EFFECT,PA_NO_EFFECT,"tulisan" , 3, 0, PA_CENTER },
};

void showDate(){

  sprintf(Fdate,"%d/%d/%d          ",myRTC.dayofmonth,myRTC.month,myRTC.year);
  if (P.displayAnimate())// animates and returns true when an animation is completed
  {
    P.displayText(Fdate, animList[0].just, 69,  
                  20,PA_SCROLL_LEFT,PA_NO_EFFECT);
  }
}

void showDay(){
  jam=myRTC.dayofweek;
  if (P.displayAnimate())// animates and returns true when an animation is completed
  {
    switch(jam)
    {
    case 1:
      sprintf(Fday,"Senin");
    break;
    case 2:
      sprintf(Fday,"Selasa");
    break;
    case 3:
      sprintf(Fday,"Rabu");
    break;
    case 4:
      sprintf(Fday,"Kamis");
    break;
    case 5:
      sprintf(Fday,"Jumat");
    break;
    case 6:
      sprintf(Fday,"Sabtu");
    break;
    case 7:
      sprintf(Fday,"Minggu");
    break;
    default:
      break;
    }
    P.displayText(Fday, animList[0].just, 4, 0,PA_NO_EFFECT,PA_NO_EFFECT);
  }
}

void showHour(){
  if (P.displayAnimate())// animates and returns true when an animation is completed
  {
    sprintf(Fjam,"%d : %d",myRTC.hours,myRTC.minutes); 
    P.displayText(Fjam, animList[0].just, animList[0].speed,  
                  animList[0].pause, animList[0].anim_in, animList[0].anim_out);
  }
}

void setAlarm(){
  if (P.displayAnimate())// animates and returns true when an animation is completed
  {
    P.displayText("Set Alarm", animList[0].just, 69, 20,PA_SCROLL_LEFT,PA_NO_EFFECT);
  }
}

void setup() {
  P.begin();
  Serial.begin(9600);
  myRTC.setDS1302Time(10,15,13,5,18,11,2022);
  animList[0].textOut= Fjam;
  for (uint8_t i=0; i<ARRAY_SIZE(animList); i++)
  {
    animList[i].speed = P.getSpeed(); 
    animList[i].pause = 500;
  }
}


void loop() {
  myRTC.updateTime();
  currentM=millis();
  if(mode1==0){
  if(mode==0)showHour();
  if(mode==1)showDay();
  if(mode==2)showDate();


  if(Serial.available()){
    mode1=1;
  }
  if(mode>2){
    mode=0;
  }
  if(currentM-prevM>5000){
    prevM=currentM;
    mode++;
  }
  }
  else{
    setAlarm();
  }
}