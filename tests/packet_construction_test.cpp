#include <iostream>
#include <vector>


/*
  Copyright 2014 Auke-Dirk Pietersma
*/


#include "ximuapi/enumerations.h"
#include "ximuapi/packet/packet_construction.h"


int main(int argc, char* argv[]) {


  std::vector<unsigned char> packet;

ximu::PacketConstruction::constructCommandPacket(ximu::CommandCodes::FACTORY_RESET,back_inserter(packet));

  return 0;
}
