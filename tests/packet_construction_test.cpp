#include <iostream>
#include <vector>


/*
  Copyright 2014 Auke-Dirk Pietersma
*/


#include "ximuapi/enumerations.h"
#include "ximuapi/packet/packet_construction.h"
#include "ximuapi/data/register_data.h"
#include "ximuapi/data/datetime_data.h"

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


  // Constucting RegisterData read/write 
  // write packet
  ximu::RegisterData r1(ximu::reg::RegisterAddresses::ADXL_345C_SENSITIVITY_X,11.0f);
  std::vector<unsigned char> r1Enc {1, 64, 12, 32,  22, 0, 206};	
  std::vector<unsigned char> r1Test;
  ximu::PacketConstruction::constructWriteRegisterPacket(r1,back_inserter(r1Test));

  if (r1Test != r1Enc)
    return 1;
  
  //read packet
  ximu::RegisterData r2(ximu::reg::RegisterAddresses::BATTERY_SHUTDOWN_VOLTAGE);
  std::vector<unsigned char> r2Enc {1, 0, 9, 4, 208};
  std::vector<unsigned char> r2Test;
  ximu::PacketConstruction::constructReadRegisterPacket(r2,back_inserter(r2Test));


  if (r2Test != r2Enc)
    return 1;

  // Constucting of the DateTimeData
  std::vector<unsigned char> dtd1Enc {2, 69, 2, 32, 56, 64, 74, 48, 75, 192};
  std::vector<unsigned char> dtd1Test;
  ximu::DateTimeData dtd1(2014, 12, 07, 10, 25, 30);
  ximu::PacketConstruction::constructWriteDateTimePacket(dtd1,back_inserter(dtd1Test));
  
  if (dtd1Enc != dtd1Test)
    return 1;
 
  
  
  return 0;
}
