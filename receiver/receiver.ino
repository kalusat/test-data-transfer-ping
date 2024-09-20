#include "CanSatNeXT.h"

int mode = 0;

void setup() {
  Serial.begin(115200);
  CanSatInit(42);
  Serial.println("READY");
}

void loop() {

}

void onDataReceived(String data) {
  if (data == "PING") {
    sendData("PING");
    Serial.println("RECEIVED AND RETURNED PING");
  } else if (data == "BEGIN MSG") {
    mode = 1;
  } else if (data == "BEGIN TMP") {
    mode = 2;
  } else if (data == "END MODE") {
    mode = 0;
  } else {
    if (mode == 1) {
      Serial.print("Received message: ");
    } else if (mode == 2) {
      Serial.print("Received temperature data: ");
    } else {
      Serial.print("Received unknown data: ");
    }
    Serial.println(data);
  }
}