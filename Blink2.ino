void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);  
  pinMode(12, OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  const long timer1 = 100;        //blinking intervals in millis
  const long timer2 = 300;
  unsigned long t = millis();     //time
  if ((t%timer1)==0){             //if timer1 is multiple of t
    if (((t/timer1)%2)==0){       //every second time
      digitalWrite(8,HIGH);
      }   //turn on LED
    else{
      digitalWrite(8,LOW);
      };
  if ((t%timer2)==0){           //if timer2 is multiple of t
    if (((t/timer2)%2)==0){     //every second time
      digitalWrite(12,HIGH);
      }                         //turn on LED
    else{
      digitalWrite(12,LOW);     //turn off L
      }
    };
  }
}
