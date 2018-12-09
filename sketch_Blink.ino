void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(8,HIGH);   //turn on LED
  delay(1000);            //wait
  digitalWrite(8,LOW);    //turn off LED
  delay(1000);            //wait

}
