#include <iostream>
#include <vector>


/*
  Copyright 2014 Auke-Dirk Pietersma
*/


#include "ximuapi/enumerations.h"
#include "ximuapi/packet/packet_construction.h"

// Example/test on constructing commands
int main(int argc, char* argv[]) {
  // the factory-reset command byte sequence has been extracted
  // from the c# gui application.
  // The test is to create the same byte sequence
  std::vector<unsigned char> packet;
  std::vector<unsigned char> factoryReset {0, 64, 0, 16, 144};

  ximu::PacketConstruction::constructCommandPacket(
      ximu::CommandCodes::FACTORY_RESET, back_inserter(packet));

  if (packet != factoryReset)
    return 1;

  // same test as the previous only now the command is the
  // algorithm clear tare command.
  packet.clear();
  std::vector<unsigned char> algClearTare {0, 64, 1, 113, 128};

  ximu::PacketConstruction::constructCommandPacket(
      ximu::CommandCodes::ALGORITHM_CLEAR_TARE, back_inserter(packet));

  if (packet != algClearTare)
    return 1;


  return 0;
}
