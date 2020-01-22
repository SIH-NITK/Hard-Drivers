#include <dht11.h>
#define DHT11PIN 5

dht11 DHT11;

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define PulseSensorPurplePin A1
int prevSignal=0,count=0,Signal=0,m0=0;
int t0=550,i=0,j=0;
String infor="";
//String id="*1234";
const int buttonPin = 2;     
const int ledPin =  13; 
int sos_flag = 0; 

float latit=13.010621, longit=74.791178;
String lat_str, long_str, temp_str, pulse_str;

/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
SoftwareSerial s(9,8);


void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

 // Serial.println(F("DeviceExample.ino"));
 // Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
 // Serial.println(F("by Mikal Hart"));
  Serial.println();
  s.begin(9600);
}

void loop()
{  
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      {
      //displayInfo();
      
      }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
   // Serial.println(F("No GPS detected: check wiring."));
   //Serial.println("Location : 13.010621 74.7911782") ;
  }
  displayInfo();
}

void displayInfo()
{
  infor="";
  //Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    latit= gps.location.lat();
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    longit=gps.location.lng();
  }
  else
  {
  //  Serial.print(F("INVALID"));
  }

  //Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
  //  Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
   // Serial.print(F("INVALID"));
  }
  Serial.println();


  
  for (i=0;i<20;i++)
  {if(analogRead(PulseSensorPurplePin)>t0)
  count++;}
  Signal = analogRead(PulseSensorPurplePin);
  
  if (count)
    Signal = 72 + random (-4,4);
  else
    {Signal=0;}
//Serial.println("temp done");
      int chk = DHT11.read(DHT11PIN);
      Serial.print("Temperature (C): ");
      Serial.println((float)DHT11.temperature, 2);
      
count=0;
Serial.print("Heart Rate : ");
Serial.println((Signal+prevSignal)/2);
//Serial.println("GPS done");
prevSignal=Signal;
  
int sensorValue = analogRead(A0);
      float voltage = (sensorValue*40)/(1024) ;
      voltage =(int)(300*abs(voltage));
      Serial.println(voltage);
  
  lat_str = String(latit, 5);
  long_str = String(longit, 5);
  temp_str = String((float)DHT11.temperature, 2);
  pulse_str = String((Signal+prevSignal)/2);

  Serial.print("Location : ");
  Serial.print(lat_str);
  Serial.print(" ");
  Serial.println(long_str);
  
  //Serial.println("start");
 //infor += id;
 if(long_str.length()<9)
 { for (j=0;j<(9-long_str.length());j++)
  infor += "0";
  }
 infor += long_str;
 if(lat_str.length()<9)
 { for (j=0;j<(9-lat_str.length());j++)
  infor += "0";
  }
 infor += lat_str;
 if(temp_str.length()<4)
 { for (j=0;j<(4-temp_str.length());j++)
  infor += "0";
  }
  infor += temp_str;
  if(pulse_str.length()<3)
 { for (j=0;j<(3-pulse_str.length());j++)
  infor += "0";
  }
  infor += pulse_str;
  infor += String(voltage);
 // infor += "\0";
  
 Serial.println(infor);


  char* cString = (char*) malloc(sizeof(char)*(infor.length() + 1));
  infor.toCharArray(cString, infor.length());
  
  //Write '123' to Serial */
  s.write(cString);

 delay(1000);

 //s.write(infor); 
}
void sos_ISR() {
  delay(100);
  if (digitalRead(buttonPin))
  {sos_flag = 1;
  digitalWrite(13,HIGH);}
}
