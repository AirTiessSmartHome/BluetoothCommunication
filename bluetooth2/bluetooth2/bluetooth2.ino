#include <SoftwareSerial.h>
#include "TimerOne.h"
#include <Servo.h>
Servo myServo;
SoftwareSerial mySerial(0, 1);
const int led1 = 9;
const int led2 = 8;
int temp = 0 ;
int gelen ;
int counter = 30 ;
int pos ;
void setup() {
 //myServo.attach(9) ;
 Timer1.initialize(5000000) ;
 Timer1.attachInterrupt(tim1_interrupt) ;
 analogReference(INTERNAL) ;
 Serial.begin(9600);
 mySerial.begin(9600);
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
}

void tim1_interrupt(){
  
  temp = analogRead(5) ;
  //temp = (temp*1100)/1023 ;
  temp = temp/10 ;
  if(temp > 34) { // sicaklik okumak icin dir 
      Serial.println(temp) ;
      digitalWrite(led2, HIGH) ;
  }else{
    Serial.println(temp) ;
    
  }
   
}
void loop() {
  
 /* for(pos = 0; pos < 90; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  for(pos = 90; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }  */
 if (mySerial.available() > 0) {
  gelen = mySerial.read();
  if (gelen == '1') {
   digitalWrite(led1, digitalRead(led1)^1);
   Serial.print("1on");
   //Serial.println("Led1 yandi");
  }
   if (gelen == '2') {
   digitalWrite(led2, digitalRead(led2)^1);
    Serial.print("2on");
   //Serial.println("Led2 yandi");
   }
    if(gelen == '3'){
      //delay(5000) ;
      //Serial.print(10) ;
      ;
    }   
  } 
}



