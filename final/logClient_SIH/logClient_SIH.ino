//************************************************************
// this is a simple example that uses the painlessMesh library to 
// setup a node that logs to a central logging node
// The logServer example shows how to configure the central logging nodes
//************************************************************
#include "painlessMesh.h"
#include<SoftwareSerial.h>

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

#define CS 5

Scheduler     userScheduler; // to control your personal task
painlessMesh  mesh;

// Prototype
void receivedCallback( uint32_t from, String &msg );

//-----------------------------------------------
  SoftwareSerial ss(3,1);
  void Ard_Interread();
  long t_ini;
  //String data;
  String toSend = "*000100000000000000000000000000000";
//-----------------------------------------------

size_t logServerId = 0;

// Send message to the logServer every 10 seconds 
Task myLoggingTask(10000, TASK_FOREVER, []() {
#if ARDUINOJSON_VERSION_MAJOR==6
        DynamicJsonDocument jsonBuffer(1024);
        JsonObject msg = jsonBuffer.to<JsonObject>();
#else
        DynamicJsonBuffer jsonBuffer;
        JsonObject& msg = jsonBuffer.createObject();
#endif
    msg["topic"] = "sensor";
    msg["value"] = toSend;

    String str;
#if ARDUINOJSON_VERSION_MAJOR==6
    serializeJson(msg, str);
#else
    msg.printTo(str);
#endif
    if (logServerId == 0) // If we don't know the logServer yet
        mesh.sendBroadcast(str);
    else
        mesh.sendSingle(logServerId, str);

    // log to serial
#if ARDUINOJSON_VERSION_MAJOR==6
    serializeJson(msg, Serial);
#else
    msg.printTo(Serial);
#endif
    Serial.printf("\n");
});

void setup() {
  Serial.begin(115200);
    
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, 6 );
  mesh.onReceive(&receivedCallback);

  // Add the task to the your scheduler
  userScheduler.addTask(myLoggingTask);
  myLoggingTask.enable();
  //--------------------------
  t_ini = millis();
  pinMode(CS,OUTPUT);
  ss.begin(115200);
}

void loop() {
  // it will run the user scheduler as well
  mesh.update();

  //------------------------------------
  long t_fin = millis();
  if(t_fin - t_ini > 1231){
      Ard_Interread();
      t_ini = millis();
    }
  //------------------------------------  
}

void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("logClient: Received from %u msg=%s\n", from, msg.c_str());

  // Saving logServer
#if ARDUINOJSON_VERSION_MAJOR==6
  DynamicJsonDocument jsonBuffer(1024 + msg.length());
  DeserializationError error = deserializeJson(jsonBuffer, msg);
  if (error) {
    Serial.printf("DeserializationError\n");
    return;
  }
  JsonObject root = jsonBuffer.as<JsonObject>();
#else
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(msg);
#endif
  if (root.containsKey("topic")) {
      if (String("logServer").equals(root["topic"].as<String>())) {
          // check for on: true or false
          logServerId = root["nodeId"];
          Serial.printf("logServer detected!!!\n");
      }
      Serial.printf("Handled from %u msg=%s\n", from, msg.c_str());
  }
}

//-----------------------------------------
  void Ard_Interread(){
      long t0 = millis();
      String data;
      digitalWrite(CS, HIGH);
      while(millis()-t0<10);
      while(ss.available()>0)
      {
        data = ss.read();
        Serial.println(data);
      }
      toSend = "*0001" + data;
      digitalWrite(CS, LOW);
  }
