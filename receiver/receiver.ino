#include <time.h>
#include "CanSatNeXT.h"

clock_t timeSave;

void setup() {
  Serial.begin(115200);
  CanSatInit(42);
  Serial.println("READY");
}

int checkInterrupt() {
  if (Serial.available() != 0) {
    String rstr = Serial.readString();
    rstr.trim();
    if (rstr == "Q") {
      return 1;
    }
  }
  return 0;
}

void loop() {
  Serial.println("FUNC >> ");
  while (Serial.available() == 0) {}
  String reply = Serial.readString();
  reply.trim();
  if (reply == "MSG") {
    sendData("BEGIN MSG");
    int interrupt = 0;
    while (!interrupt) {
      Serial.println("MESSAGE (Q to quit) >> ");
      while(Serial.available() == 0) {}
      String msg = Serial.readString();
      msg.trim();
      if (msg.equalsIgnoreCase("Q") || msg.equalsIgnoreCase("QUIT")) {
        sendData("END MODE");
        interrupt = 1;
      } else {
        sendData(msg);
        Serial.print(msg);
        Serial.println(" [SENT]");
      }
    }
  } else if (reply == "PING") {
    sendData("PING");
    timeSave = clock();
  } else if (reply == "TMP") {
    sendData("QUERY TMP");
    Serial.println("Sent data query for temperature");
  } else {
    Serial.println("ERROR : Unknown Function");
  }
}

void onDataReceived(String data) {
  if (data == "PING") {
    clock_t currentTime = clock();
    float pingTime = (float)currentTime - (float)timeSave;
    char timePrint[32];
    sprintf(timePrint, "PING TIME: %.2f ms (FUNC) >>", pingTime);
    Serial.println(timePrint);
  } else if (data.startsWith("TMP")) {
    data.replace("TMP ", "");
    Serial.println("TEMPERATURE: " + data);
  }
}