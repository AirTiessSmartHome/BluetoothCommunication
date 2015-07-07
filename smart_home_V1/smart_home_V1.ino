#include <SoftwareSerial.h>

#include "TimerOne.h"

#include <Servo.h>

Servo myServo ;

SoftwareSerial mySerial(0,1);

int IRledPin =  12;    // LED connected to digital pin 12

int temp = 0 ;

const int led1 = 8;

const int led2 = 10;

int gelen;

void setup() {

 //myServo.attach(9) ;

 //myServo.write(90);  // set servo to mid-point

 Timer1.initialize(2000000) ;

 Timer1.attachInterrupt(tim1_interrupt) ;

 analogReference(INTERNAL) ;

 Serial.begin(9600);

 mySerial.begin(9600);

 pinMode(led1, OUTPUT);

 pinMode(led2, OUTPUT);

}

void tim1_interrupt(){

  

  temp = analogRead(5) ;

  temp = map(temp, 0, 1023, 0, 110); 

  //temp = temp/10 ;

  if(temp > 50) { // sicaklik okumak icin dir 

      Serial.print("AC") ;

  }else{

    Serial.print(temp) ;

  }

   

} 

void loop() {

 if (mySerial.available() > 0) {

   gelen = mySerial.read();



    /*data burada*/



   if (gelen == '1') {            /*8. pini aktif et*/

     digitalWrite(led1, digitalRead(led1)^1);

     //Serial.println("Led1 yandi");

   }

   

   if (gelen == '2') {            /*9. pini aktif et*/

     digitalWrite(led2, digitalRead(led2)^1);

     //Serial.println("Led2 yandi");

   }

   

   if (gelen == '3') {            /*motor dönecek*/

     //Serial.println("Sensor Read");

   }

   

   if (gelen == '4') {            /*TV yi açsın / kapatsın*/

     ShutDown();

     //Serial.println("TV ON/OFF");

   }



   if (gelen == '5') {            /*TV sesini aç*/

     soundUp();

     //Serial.println("Sound Up");

   }



   if (gelen == '6') {            /*TV sesini kıs*/

     soundDown();

     //Serial.println("Sound Down");

   }



   if (gelen == '7') {            /*TV kanal ileri*/

     channelUp();

     //Serial.println("Channel Up");

   }



   if (gelen == '8') {            /*TV kanal geri*/

     channelDown();

     //Serial.println("Channel Down");

   }

 }

}



void pulseIR(long microsecs) {

  // we'll count down from the number of microseconds we are told to wait

 

  cli();  // this turns off any background interrupts

 

  while (microsecs > 0) {

    // 38 kHz is about 13 microseconds high and 13 microseconds low

   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen

   delayMicroseconds(10);         // hang out for 10 microseconds

   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds

   delayMicroseconds(10);         // hang out for 10 microseconds

 

   // so 26 microseconds altogether

   microsecs -= 26;

  }

 

  sei();  // this turns them back on

}



void ShutDown() {

    delayMicroseconds(38672); //Time off (Left Column on serial monitor)

    pulseIR(4420);           //Time on  (Right Column on serial monitor)

    delayMicroseconds(4340);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(600);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1540);

    pulseIR(640);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(500);

    pulseIR(600);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1560);

    pulseIR(600);

    delayMicroseconds(45420);

    pulseIR(4440);

    delayMicroseconds(4340);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(580);  

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1560);

    pulseIR(620);

    delayMicroseconds(480);

    pulseIR(600);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1580);

    pulseIR(600);

}



void channelUp() {

    delayMicroseconds(5068);

    pulseIR(4440);

    delayMicroseconds(4300);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(560);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(560);

    pulseIR(540);

    delayMicroseconds(560);

    pulseIR(540);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(560);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(560);

    pulseIR(540);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(560);

    pulseIR(540);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(45420);

    pulseIR(4460);

    delayMicroseconds(4320);

    pulseIR(540);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(560);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(560);

    pulseIR(540);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(560);

    pulseIR(540);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(540);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(560);

    pulseIR(520);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

}



void channelDown() {

    delayMicroseconds(43340);

    pulseIR(4400);

    delayMicroseconds(4340);

    pulseIR(560);

    delayMicroseconds(1640);

    pulseIR(540);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(540);

    delayMicroseconds(1640);

    pulseIR(540);

    delayMicroseconds(1640);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(1640);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(560);

    pulseIR(540);

    delayMicroseconds(1620);

    pulseIR(540);

    delayMicroseconds(1640);

    pulseIR(540);

    delayMicroseconds(1640);

    pulseIR(540);

    delayMicroseconds(1640);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(540);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(45440);

    pulseIR(4420);

    delayMicroseconds(4320);

    pulseIR(580);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(540);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1620);

    pulseIR(540);

    delayMicroseconds(1640);

    pulseIR(540);

    delayMicroseconds(1640);

    pulseIR(520);

    delayMicroseconds(540);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(540);

    pulseIR(560);

    delayMicroseconds(1640);

    pulseIR(520);

    delayMicroseconds(540);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(1640);

    pulseIR(540);

    delayMicroseconds(1640);

    pulseIR(540);

    delayMicroseconds(1640);

    pulseIR(520);

    delayMicroseconds(1640);

    pulseIR(540);

    delayMicroseconds(540);

    pulseIR(580);

    delayMicroseconds(1620);

    pulseIR(540);

    delayMicroseconds(1620);

    pulseIR(540);

    delayMicroseconds(1620);

    pulseIR(560);

}



void soundUp() {

    delayMicroseconds(22172);

    pulseIR(4400);

    delayMicroseconds(4340);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(600);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(600);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(480);

    pulseIR(600);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(45440);

    pulseIR(4420);

    delayMicroseconds(4340);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(600);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(600);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1580);

    pulseIR(600);

}



void soundDown() {

    delayMicroseconds(37660);

    pulseIR(4400);

    delayMicroseconds(4340);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1560);

    pulseIR(620);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(480);

    pulseIR(600);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(500);

    pulseIR(600);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(1620);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(45440);

    pulseIR(4420);

    delayMicroseconds(4300);

    pulseIR(620);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1580);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(580);

    delayMicroseconds(500);

    pulseIR(600);

    delayMicroseconds(520);

    pulseIR(560);

    delayMicroseconds(1600);

    pulseIR(580);

    delayMicroseconds(520);

    pulseIR(580);

    delayMicroseconds(1600);

    pulseIR(560);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1580);

    pulseIR(600);

    delayMicroseconds(1580);

    pulseIR(600);

}
