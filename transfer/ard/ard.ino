#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of arduino
SoftwareSerial s(9,8);
/*
//4,3
String str;

//char* cString = (char*) malloc(sizeof(char)*(outMessage.length() + 1);
//outMessage.stoCharArray(cString, outMessage.length() + 1);

*/
//Serial1.write(cString);
void setup() {
  //Serial S Begin at 9600 Baud
  s.begin(9600);
}

void loop() {
 /* str="Yayy its working!!!";
  char* cString = (char*) malloc(sizeof(char)*(str.length() + 1));
  str.toCharArray(cString, str.length() + 1);
  
  //Write '123' to Serial */
  s.write("Hello");
  //delay(1000);
  
}
