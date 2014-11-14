/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include <vector>
#include "ximuapi/serialization/writer_base.h"
#include "ximuapi/packet/packet_construction.h"

namespace ximu {

void WriterBase::sendReadRegisterPacket(RegisterData& r) {
  std::vector<unsigned char> buffer;
  PacketConstruction::constructReadRegisterPacket(r, back_inserter(buffer));
  sendSerialBuffer(buffer);
}

void WriterBase::sendWriteRegisterPacket(RegisterData& r) {
  std::vector<unsigned char> buffer;
  PacketConstruction::constructWriteRegisterPacket(r, back_inserter(buffer));
  sendSerialBuffer(buffer);
}

void WriterBase::sendCommandPacket(CommandCodes code) {
  std::vector<unsigned char> buffer;
  PacketConstruction::constructCommandPacket(
      code, back_inserter(buffer));
  sendSerialBuffer(buffer);
}

void WriterBase::sendReadDateTimePacket() {
  std::vector<unsigned char> buffer;
  PacketConstruction::constructReadDateTimePacket(back_inserter(buffer));
  sendSerialBuffer(buffer);
}

void WriterBase::sendWriteDateTimePacket(DateTimeData& d) {
  std::vector<unsigned char> buffer;
  PacketConstruction::constructWriteDateTimePacket(
      d, back_inserter(buffer));
  sendSerialBuffer(buffer);
}

}  // namespace ximu
