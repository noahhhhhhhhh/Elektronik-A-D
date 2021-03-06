#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
const int colorR = 0;      //colors
const int colorG = 255;
const int colorB = 0;

const int colorR_hot = 255;      //colors
const int colorG_hot = 0;
const int colorB_hot = 0;

const int above_threshold = 40;   //lines drawn to indicate whether below or above threshold (at 20 resp. 40)
const int below_threshold = 20;

const float r0 = 100000;     //zero power resistance in Ohm
const float B = 4500 ;        //nominal B-consant
const float T0 = 298.15;      //room temperature in Kelvin

const float Tmin = 20;       //critical temperatures in Celsius
const float Tmax = 40;
const float Tdiff = 1.5;       //Difference between upper and lower limit

const int tmeas = 1000;          //time over which rpms are calculated
const int threshold = 50;       //threshold for counting fan revolutions
int count,t,tbefore,rotations,rpm = 0;              //counting revolutions, time
int rpmvolt;

float v,r,T,Tinv,Tcels,Tcrit,Tcritlow;
float sensor_value;             //declaring variables

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);

  lcd.setRGB(colorR, colorG, colorB);   //screen color
  pinMode(11, OUTPUT);
  pinMode(A0, INPUT);                   //rotary angle sensor
  pinMode(A3, INPUT);                   //temperature sensor
  pinMode(12, OUTPUT);                   //LED
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  v = analogRead(A3);   //measured voltage
  r = (1023/v-1)*r0;     //resistance
  Tinv = log(r/r0)/B+1/T0; //1/T;
  T = 1/Tinv;
  Tcels = T-273.15;
  
  
  lcd.print(Tcels);                     //show on display
  //lcd.print(v);
  lcd.print("GC ");
  
  
  sensor_value = analogRead(A0);        //rotary sensor
  //Tcrit = map(sensor_value, 0, 1023, Tmin, Tmax);
  Tcrit=Tmin+(Tmax-Tmin)/1023*sensor_value;   //upper limit
  Tcritlow=Tcrit-Tdiff;                       //lower limit
  
  if(Tcels>Tcrit){                      //if hot
    digitalWrite(12, HIGH);             //turn on LED
    lcd.setRGB(colorR_hot, colorG_hot, colorB_hot); //change screen color
    //lcd.setCursor(0, 1);
    lcd.print("Th:");
    lcd.print(Tcrit);}
    //Serial.print(above_threshold);}
  else{                                 //if not hot
    digitalWrite(12,LOW);                //turn off LED
    lcd.setRGB(colorR, colorG, colorB);  //change screen color
    //lcd.setCursor(0, 1);
    lcd.print("Th:");
    lcd.print(Tcrit);}
    //Serial.print(below_threshold);}
    
  //Serial.print(",");
  Serial.print(Tcels);
  Serial.print(",");
  //Serial.println(Tcrit);

  //fan
  if(Tcels<Tcritlow){
    digitalWrite(11,LOW);}            //turn off fan if below lower limit
  else if(Tcels>Tcrit){
    digitalWrite(11,HIGH);}           //turn on fan if above higher limit

 
  
  
  

  delay(1);
  
  
}
