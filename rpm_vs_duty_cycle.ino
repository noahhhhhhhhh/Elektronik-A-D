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
const int threshold = 400;       //threshold for counting fan revolutions
const int threshold_low = 200;
long count,t,tbefore,rotations,rpm = 0;              //counting revolutions, time
long rpmvolt;
int dutycycle=0;                    //index for dutycycle
int currentstate = 0;
float v,r,T,Tinv,Tcels,Tcrit,Tcritlow;
float sensor_value;             //declaring variables
const long tstopp = 1000000;
int trun;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);

  lcd.setRGB(colorR, colorG, colorB);   //screen color
  pinMode(11, OUTPUT);
  pinMode(A0, INPUT);                   //rotary angle sensor
  pinMode(A3, INPUT);                   //temperature sensor
  pinMode(A2,INPUT);
  pinMode(12, OUTPUT);                   //LED
  Serial.begin(9600);
}

float countrounds(long trun){
  count = 0;
  tbefore = micros();
  t=micros()-tbefore;
  while(t<trun){
    
    rpmvolt = analogRead(A2);           //measuring input
    if((rpmvolt>threshold) && (currentstate==0)){
      count++;
      currentstate=1;}
    if((rpmvolt<threshold_low)&&(currentstate==1)){
      currentstate=0;}
    t = micros()-tbefore;  
      //delayMicroseconds(400);
      }
 return count;}

float roundstorpm(long rounds, long trun){
  float rpms=rounds/2*60*1000000/trun;
  return rpms;}  


void loop() {
  // put your main code here, to run repeatedly:
  //lcd.setCursor(0, 0);
  //v = analogRead(A3);   //measured voltage
  //r = (1023/v-1)*r0;     //resistance
  //Tinv = log(r/r0)/B+1/T0; //1/T;
  //T = 1/Tinv;
  //Tcels = T-273.15;
  
  
  //lcd.print(Tcels);                     //show on display
  //lcd.print(v);
  //lcd.print("GC ");
  
  
  //sensor_value = analogRead(A0);        //rotary sensor
  //Tcrit = map(sensor_value, 0, 1023, Tmin, Tmax);
  //Tcrit=Tmin+(Tmax-Tmin)/1023*sensor_value;   //upper limit
  //Tcritlow=Tcrit-Tdiff;                       //lower limit
  
  //if(Tcels>Tcrit){                      //if hot
    //digitalWrite(12, HIGH);             //turn on LED
    //lcd.setRGB(colorR_hot, colorG_hot, colorB_hot); //change screen color
    //lcd.setCursor(0, 1);
    //lcd.print("Th:");
    //lcd.print(Tcrit);}
    //Serial.print(above_threshold);}
  //else{                                 //if not hot
    //digitalWrite(12,LOW);                //turn off LED
    //lcd.setRGB(colorR, colorG, colorB);  //change screen color
    //lcd.setCursor(0, 1);
    //lcd.print("Th:");
    //lcd.print(Tcrit);}
    //Serial.print(below_threshold);}
    
  //Serial.print(",");
  //Serial.print(Tcels);
  //Serial.print(",");
  //Serial.println(Tcrit);

  //fan
  //if(Tcels<Tcritlow){
    //digitalWrite(11,LOW);}            //turn off fan if below lower limit
  //else if(Tcels>Tcrit){
    //digitalWrite(11,HIGH);}           //turn on fan if above higher limit

  //rpms
   //t = millis()-tbefore;               //time since last conversion to rpm
  //rpmvolt = analogRead(A2);           //measuring input
  //if (rpmvolt>threshold && currentstate==0){             //if signal for rotation
    //count++;
    //currentstate=1;}
  //if(rpmvolt<threshold_low && currentstate==1){
    //currentstate=0;}
  //if (t>tmeas){
    //rotations = count/2;
    //rpm = rotations*60*1000000/tmeas;
  
    count=countrounds(tstopp);
    rpm=roundstorpm(count, tstopp);

//tbefore=micros();
//while(t<tstopp){
 // rpmvolt = analogRead(A2);
 // if(rpmvolt>threshold && currentstate==0){
 //   count+=1;
 //   currentstate=1;}
 // if(rpmvolt<threshold && currentstate==1){
 //   currentstate=0;}
 //   t=micros()-tbefore;
 // }

    
    lcd.setCursor(0, 0);
    //lcd.print(count);
    
    lcd.print(rpm);
    lcd.print(" rpms");             //print frequency every tmeas
    Serial.println(rpm);            //print rpm to serial
    //count=0;                        //resetting counter
    //tbefore=tbefore+t;              //resetting tbefore
    analogWrite(11,dutycycle);
    dutycycle++;
    dutycycle=dutycycle%255;  
    lcd.setCursor(0, 1);
    lcd.print(dutycycle);
    t=0;
    count=0;
 // }
  
  
  

delay(5);
  
  
}
