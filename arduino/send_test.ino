#include <SPI.h>
#include "mcp2515_can.h"

mcp2515_can CAN(10);

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   while(!Serial){};
   while (CAN_OK != CAN.begin(CAN_500KBPS)) {
      Serial.println("CAN init fail, retry...");
      delay(100);
   }
   Serial.println("CAN init ok!");
}

unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void loop() {
  // put your main code here, to run repeatedly:
  stmp[7] = stmp[7] + 1;
   if (stmp[7] == 100) {
      stmp[7] = 0;
      stmp[6] = stmp[6] + 1;
      if (stmp[6] == 100) {
         stmp[6] = 0;
         stmp[5] = stmp[5] + 1;
      }
   }
   
   CAN.sendMsgBuf(0x00, 0, 0, 8, stmp, true);
   delay(100); // send data per 100ms
   Serial.println("CAN BUS sendMsgBuf ok!");

}