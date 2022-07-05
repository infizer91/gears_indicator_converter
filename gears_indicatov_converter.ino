/*
Gear's converter for cirocco - robot to at

Copyright 2022, Infizer <https://github.com/infizer91>
Date: 04.07.2022

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License at <http://www.gnu.org/licenses/> for
more details.
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
*/

#include <can.h>     // https://github.com/autowp/arduino-mcp2515
#include <mcp2515.h> // https://github.com/autowp/arduino-mcp2515

#include <SPI.h>

#define CAN_FREQ MCP_16MHZ

struct can_frame canMsg;

MCP2515 can(10);

void setup() {
  Serial.begin(115200);
  SPI.begin();

  can.reset();
  can.setBitrate(CAN_125KBPS, CAN_FREQ);
  can.setNormalMode();
}

void loop() {
  if (can.readMessage( & canMsg) == MCP2515::ERROR_OK) {
    if (canMsg.can_id == 0x128) {
      if (canMsg.data[2] != 0x42) {
        if (canMsg.data[1] == 0x90) {
          canMsg.data[1] = 0x32;
        } else if (canMsg.data[1] == 0x80) {
          canMsg.data[1] = 0x34;
        } else if (canMsg.data[1] == 0x70) {
          canMsg.data[1] = 0x36;
        } else if (canMsg.data[1] == 0x60) {
          canMsg.data[1] = 0x38;
        } else if (canMsg.data[1] == 0x50) {
          canMsg.data[1] = 0x3a;
        } else if (canMsg.data[1] == 0x40) {
          canMsg.data[1] = 0x3c;
        }
      }

      canMsg.data[2] = 0;
      can.sendMessage( & canMsg);
    }
  }
}
