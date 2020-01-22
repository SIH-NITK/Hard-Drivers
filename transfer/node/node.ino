#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of ESP8266/NodeMCU
SoftwareSerial ss(3,1);

String data;
void setup() {
  //Serial Begin at 9600 Baud 
  Serial.begin(9600);
  ss.begin(9600);
}

void loop() {
  while(ss.available()>0)
  {
  data = ss.read();
  Serial.println(data);
  }
  
  //Read the serial data and store it
  delay(1000);
}
