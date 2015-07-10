#include <SoftwareSerial.h>

#include <MsTimer2.h>

#include "TimerOne.h"

#include <Servo.h>

Servo myServo ;

SoftwareSerial mySerial(0,1);

const int IRledPin =  12;    // LED connected to digital pin 12

int temp = 0 ;

const int oguz_aut[4][10] = {'o','g','u','z','5','4','3','2','1','0','s','a','m','e','t','1','2','3','4','5',

'k','a','a','n','6','5','4','3','2','1','m','u','r','a','t','2','0','1','2','8'};

const int led1 = 8;

const int led2 = 10;

//const int resetPin = 13 ;

int gelen;

int authentication = 0 ;

int aut_mem[10] ;

int counter = 0 ;

int echoback_counter = 1 ;

int j = 0 ;

int i = 0 ;

void setup() {

 pinMode(led1, OUTPUT);

 pinMode(led2, OUTPUT);

 MsTimer2::set(10000, timeout_authentication); // 10000ms = 10Sn

 myServo.attach(9) ;

 myServo.write(180) ;

 Timer1.initialize(2000000) ; // 2 sn

 Timer1.attachInterrupt(tim1_interrupt) ;

 analogReference(INTERNAL) ;

 Serial.begin(9600);

 mySerial.begin(9600);

}

void(* resetFunc) (void) = 0;

void timeout_authentication(){

  if(authentication == 0){

    counter = 0 ;

    i = 0 ;

  }else{

    if(echoback_counter == 0) {

      authentication = 0 ;

      resetFunc() ;

    }else

    echoback_counter = 0 ;

    }

  

  

}

void tim1_interrupt(){

  

  if(authentication == 1){

    

    temp = analogRead(5) ;

    temp = map(temp, 0, 1023, 0, 110); 

    //temp = temp/10 ;

    if(temp > 50) { // sicaklik okumak icin dir 

        Serial.print("AC") ;

    }else{

      Serial.print(temp) ;

    }

  }

} 

void loop() {

 if (mySerial.available() > 0) {

   gelen = mySerial.read();

   if(authentication == 0){

      if(counter == 0)  MsTimer2::start(); 

      if(counter <= 9) {

        aut_mem[counter] = gelen ;

        counter++ ;

      }

      if(counter == 10){ // counter == 10

        i = 0 ;

        for(j=0 ; j<=3 ; j++){

          for(counter = 0 ; counter<= 9 ; counter++) {

             if(aut_mem[counter] == oguz_aut[j][counter]){

                i++ ;

             } else

                break ;

          }

          if(i == 10){ // match saglandi

              i = 0 ;

              counter = 0 ;

              //MsTimer2::stop();

              authentication = 1 ;

              break ;    

             }

             i=0 ;

          if(j == 3){ //eslenme saglanamadi

             counter = 0 ;

          }

        }

      }   

   }

    /*data burada*/

   else{

     if(gelen == 'E'){

      echoback_counter++ ;

     }

     if(gelen == '0') {

        counter = 0 ;

        authentication = 0 ;

        resetFunc() ;

     }

     if (gelen == '1') {            /*8. pini aktif et*/

       digitalWrite(led1, digitalRead(led1)^1);

       //Serial.println("Led1 yandi");

     }

     

     if (gelen == '2') {            /*10. pini aktif et*/

       digitalWrite(led2, digitalRead(led2)^1);

       //Serial.println("Led2 yandi");

     }

     

     if (gelen == '3') {            /*motor dönecek*/

       if(myServo.read() > 0)

          myServo.write(0) ;

       else

          myServo.write(180) ;

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
