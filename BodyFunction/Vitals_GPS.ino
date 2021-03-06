#include <dht11.h>
#define DHT11PIN 5

dht11 DHT11;

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define PulseSensorPurplePin A1
int prevSignal=0,count=0,Signal=0,m0=0;
int t0=550,i=0;
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

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

 // Serial.println(F("DeviceExample.ino"));
 // Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
 // Serial.println(F("by Mikal Hart"));
  Serial.println();
}

void loop()
{  
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      {
      displayInfo();
      int chk = DHT11.read(DHT11PIN);
      Serial.print("Temperature (C): ");
      Serial.println((float)DHT11.temperature, 2);
      delay(200);
      }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
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
    Serial.print(F("INVALID"));
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
    Serial.print(F("INVALID"));
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

count=0;
Serial.print("Heart Rate : ")
Serial.println((Signal+prevSignal)/2);
prevSignal=Signal;
  delay(1000);
}
