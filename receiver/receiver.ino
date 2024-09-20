#include "CanSatNeXT.h"

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
  } else {
    Serial.print("Received data: ");
    Serial.println(data);
  }
}