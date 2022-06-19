#include <SPI.h>
#include "mcp2515_can.h"

const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;

long unsigned int msgId;
unsigned char msgLen = 0;
unsigned char msgBuf[8];
char msgString[128];

mcp2515_can CAN(SPI_CS_PIN);

void setup() {
    Serial.begin(115200);

  while (CAN_OK != CAN.begin(CAN_500KBPS, MCP_16MHz)) {
    Serial.println("CAN BUS Init Failed");
    delay(100);
  }
  Serial.println("CAN BUS  Init OK!");
  CAN.setMode(MODE_LISTENONLY);
}

void loop() {
  if (!digitalRead(CAN_INT_PIN)) {
    CAN.readMsgBufID(&msgId, &msgLen, msgBuf);

    sprintf(msgString, "ID: 0x%.8lx;", msgId);
    Serial.print(msgString);

    sprintf(msgString, "MSG: 0x%.8lx;", msgBuf);
    Serial.println(msgString);
  }
}