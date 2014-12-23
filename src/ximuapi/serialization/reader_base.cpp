/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include <vector>
#include "ximuapi/serialization/reader_base.h"

namespace ximu {
ReaderBase::ReaderBase()
  :
  PacketReader(), _maxBufferSize(1000) {
}

// description of a framebuffer
bool isFrameBuffer(unsigned char entry) {
  return (entry & 0x80) == 0x80;
}


bool ReaderBase::isFull() {
  return _buffer.size() == _maxBufferSize;
}

bool ReaderBase::isEmpty() {
  return _buffer.size() == 0;
}

void ReaderBase::read() {
  bool done = false;

  // todo @aukedirk no-magic numbers
  while (_buffer.size() > 4 && !done) {
    // locate potential header byte
    auto frameBuffer = std::find_if(
        _buffer.begin(), _buffer.end(), isFrameBuffer);

    // we did not find the framebuffer
    if (frameBuffer == _buffer.end())
      return;

    //  todo @auke-dirk investigate enum
    //  pass to the packetreader
    switch (PacketReader::read(_buffer.begin(), frameBuffer + 1)) {
      case PacketReader::INVALID_CHECKSUM:
      case PacketReader::OKE:
      case PacketReader::INVALID_PACKET_SIZE:
        _buffer.erase(_buffer.begin(), frameBuffer + 1);
        break;
      default:
        _buffer.erase(_buffer.begin(), frameBuffer + 1);
    }
  }
}

void ReaderBase::recievedQuaternionData(QuaternionData& q) {}
void ReaderBase::recievedDatTimeData(DateTimeData& d) {}
void ReaderBase::recievedRegisterData(RegisterData& r) {}
void ReaderBase::recievedCalInertialAndMagneticData(
    CalInertialAndMagneticData& c) {}
void ReaderBase::recievedDigitalIOData(DigitalIOData& diod){}
}  // namespace ximu
