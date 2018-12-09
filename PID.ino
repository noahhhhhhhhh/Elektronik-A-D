#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

float Tcels,v,r,Tinv;   //declaring constants used for temperature

const int colorR = 0;      //colors
const int colorG = 255;
const int colorB = 0;

const int colorR_hot = 255;      //colors
const int colorG_hot = 0;
const int colorB_hot = 0;

const float r0 = 100000 ;     //zero power resistance in Ohm
const float B = 4500 ;        //nominal B-consant
const float T0 = 298.15 ;      //room temperature in Kelvin

float T,T_current;                      //Temperature
const float sp = 25;          //desired temperature
float proportional,error, integral,sum_err, derivative,gradient;    //variables used for stuff
float prev_err = 0;
float prev_time=0;
float current_time;
float timestep;
float PID;
const float k_p = 1;
const float k_i = 0.5;
const float k_d = 0.1;
const float LOWPASS_ALPHA=0.5;

float temperature(){       //returns temperature
  v = analogRead(A3);     //measured voltage
  r = (1023/v-1)*r0;      //resistance
  Tinv = log(r/r0)/B+1/T0; //1/T;
  T = 1/Tinv;
  Tcels = T-273.15;
  return Tcels;
  }
  
void setup() {
  // put your setup code here, to run once:
lcd.begin(16, 2);

lcd.setRGB(colorR, colorG, colorB);   //screen color
pinMode(11, OUTPUT);
pinMode(A0, INPUT);                   //rotary angle sensor
pinMode(A3, INPUT);                   //temperature sensor
pinMode(A2,INPUT);
Serial.begin(9600);
T = temperature();
}



  
void loop() {
  // put your main code here, to run repeatedly:
  T=temperature();
  //T = (1-LOWPASS_ALPHA)*T + LOWPASS_ALPHA*(T_current);
error = T-sp;
proportional = k_p*error;     //proportional

if (-0.5 < error && error < 0.5){
  sum_err+=error;
  }
integral=k_i*sum_err;       //integral

current_time=millis();
timestep = (current_time-prev_time)/1000;
gradient=(error-prev_err)/timestep;
derivative = k_d*gradient;         //derivative
  
prev_err = error;
prev_time = current_time;

PID = proportional+integral+derivative;
if (PID<0){PID=0;}
if (PID>1){PID=1;}
PID*=255;
//analogWrite(11,255);
analogWrite(11,PID);
lcd.setCursor(0,0);
lcd.print(T);
lcd.setCursor(0,1);
lcd.print(PID);

//Serial.print(sp);
//Serial.print(",");
Serial.println(T);
delay(500);
}
