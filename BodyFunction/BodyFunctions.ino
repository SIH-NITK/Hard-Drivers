//Heart Rate and Temperature

#include <dht11.h>
#define DHT11PIN 4
#define sensorPin A1                             // A0 is the input pin for the heart rate sensor

dht11 DHT11;
float sensorValue = 0;                             // Variable to store the value coming from the sensor
int count = 0;
unsigned long starttime = 0;
int heartrate = 0;


void setup (void) 
{
Serial.begin (9600);                               // Start Serial Communication @ 9600
}


void loop ()
{
 heartRate();
 bodyTemp();
}



void heartRate()
{
starttime = millis();

while (millis()-starttime<10000)                   // Reading pulse sensor for 10 seconds
{
sensorValue = analogRead(sensorPin);
//Serial.println(sensorValue);
//delay(500);
if (sensorValue > 550)         // Threshold value is 550 (~ 2.7V)
count++;
}
heartrate = count*6;                               // Multiply the count by 6 to get beats per minute
Serial.print ("BPM = ");
Serial.println (heartrate);                        // Display BPM in the Serial Monitor
Serial.println ();
count = 0;
}

void bodyTemp()
{
 int chk = DHT11.read(DHT11PIN);
 Serial.print("Temperature (C): ");
 Serial.println((float)DHT11.temperature, 2);
  
}
