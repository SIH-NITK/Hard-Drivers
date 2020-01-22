#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of arduino
SoftwareSerial s(9,8);

//4,3
String str,str2;

//char* cString = (char*) malloc(sizeof(char)*(outMessage.length() + 1);
//outMessage.stoCharArray(cString, outMessage.length() + 1);


//Serial1.write(cString);
void setup() {
  //Serial S Begin at 9600 Baud
  s.begin(9600);
}

void loop() {
  str="Yayy its working!!!";
  str2="123456";
  //char* cString = (char*) malloc(sizeof(char)*(str.length() + 1));
  //str.toCharArray(cString, str.length() + 1);
  str+=str2;
  str = str.concat(str2);
  //Write '123' to Serial */
  s.write(str);
  //delay(1000);
  
}
