#include <stdio.h>
#include <HardwareSerial.h>



int i=0;

void setup() {


  Serial.begin(115200);          
  Serial.print(i++);
delay(2000);



}


void loop() {



 Serial.print(i++);


    delay(2000);
}