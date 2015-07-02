#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,1);
const int led1 = 9;
const int led2 = 8;
int gelen;
void setup() {
 Serial.begin(9600);
 mySerial.begin(9600);
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
}

void loop() {
 if (mySerial.available() > 0) {
   gelen = mySerial.read();

    /*data burada*/

   if (gelen == '1') {            /*8. pini aktif et*/
     digitalWrite(led1, HIGH);
     Serial.println("Led1 yandi");
   }
   
   if (gelen == '2') {            /*9. pini aktif et*/
     digitalWrite(led2, HIGH);
     Serial.println("Led2 yandi");
   }
   
   if (gelen == '3') {            /*ısı sensörünü okusun*/
     digitalWrite(led1, LOW);
     Serial.println("Led1 sondu");
   }
   
   if (gelen == '4') {            /*TV yi açsın*/
     digitalWrite(led2, LOW);
     Serial.println("Led2 sondu");
   }

   if (gelen == '5') {            /*TV yi kapatsın*/
     digitalWrite(led2, LOW);
     Serial.println("Led2 sondu");
   }

   if (gelen == '6') {            /*TV sesini aç*/
     digitalWrite(led2, LOW);
     Serial.println("Led2 sondu");
   }

   if (gelen == '7') {            /*TV sesini kapat*/
     digitalWrite(led2, LOW);
     Serial.println("Led2 sondu");
   }

   if (gelen == '8') {            /*TV kanal ileri*/
     digitalWrite(led2, LOW);
     Serial.println("Led2 sondu");
   }

   if (gelen == '9') {            /*TV kanal geri*/
     digitalWrite(led2, LOW);
     Serial.println("Led2 sondu");
   }
 }
}
