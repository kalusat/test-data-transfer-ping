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
  Serial.println("SELECT FUNCTION: DATASEND or PING >> ");
  while (Serial.available() == 0) {}
  String reply = Serial.readString();
  reply.trim();
  if (reply == "DATASEND") {
    int interrupt = 0;
    while (!interrupt) {
      if (checkInterrupt()) {
        interrupt = 1;
      } else {
        float temp = readTemperature();
        Serial.print("Sending temperature data: ");
        Serial.println(temp);
        sendData(temp);
        delay(200);
      }
    }
  } else if (reply == "PING") {
    sendData("PING");
    timeSave = clock();
  }
}

void onDataReceived(String data) {
  if (data == "PING") {
    clock_t currentTime = clock();
    float pingTime = (float)currentTime - (float)timeSave;
    char timePrint[32];
    sprintf(timePrint, "PING TIME: %.2f", pingTime);
    Serial.println(timePrint);
  }
}
