#include <SPI.h>
#include "mcp2515_can.h"

const int spiCSPin = 10;
const int ledPin = 2;
boolean ledON = 1;

mcp2515_can CAN(spiCSPin);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);

  while (CAN_OK != CAN.begin(CAN_500KBPS, MCP_16MHz)) {
    Serial.println("CAN BUS Init Failed");
    delay(100);
  }
  
  Serial.println("CAN BUS  Init OK!");
  CAN.setMode(MODE_NORMAL);
}

void loop() {
    unsigned char len = 0;
    unsigned char buf[8];

    if (CAN_MSGAVAIL == CAN.checkReceive()) {
      CAN.readMsgBuf(&len, buf);

      unsigned long canId = CAN.getCanId();

      Serial.print("ID: 0x");
      Serial.print(canId, HEX);

      Serial.print(" MSG: ");
      
      for (int j = 0; j < len; j++) {
        Serial.print(buf[j], HEX);
      }

      Serial.println();
    }
}