#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of arduino
SoftwareSerial s(9,8);

String str;

void setup() {
  //Serial S Begin at 9600 Baud
  s.begin(9600);
}

void loop() {
  str="Yayy its working!!!";
  char* cString = (char*) malloc(sizeof(char)*(str.length() + 1));
  str.toCharArray(cString, str.length() + 1);
  
  //Write '123' to Serial
  s.write(cString);
  //delay(1000);
  
}
