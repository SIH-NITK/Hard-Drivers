const int buttonPin = 2;     
const int ledPin =  13; 
bool sos_flag = 0;            

void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
}

void loop() {
  attachInterrupt(0, sos_ISR, CHANGE);
}

void sos_ISR() {
  delay(100);
  sos_flag = !sos_flag;
  digitalWrite(13,sos_flag);
  
}
