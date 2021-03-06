/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include <vector>
#include "ximuapi/serialization/reader_base.h"
#include <iostream>

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
    {
        if (_buffer.size() > 30)
            _buffer.clear();
        return;
    }

    // All messages are between 4 and 30 bytes
    size_t msgLength = std::distance(_buffer.begin(),frameBuffer);
    if (msgLength < 4 || msgLength > 30)
    {
        _buffer.erase(_buffer.begin(), frameBuffer + 1);
    }
    else
    {
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
}

void ReaderBase::recievedQuaternionData(QuaternionData& q) {}
void ReaderBase::recievedDateTimeData(DateTimeData& d) {}
void ReaderBase::recievedRegisterData(RegisterData& r) {}
void ReaderBase::recievedCalInertialAndMagneticData(
    CalInertialAndMagneticData& c) {}
void ReaderBase::recievedDigitalIOData(DigitalIOData& diod){}
void ReaderBase::recievedCalAdxl345BusData(CalAdxl345BusData& adxl) {}
void ReaderBase::recievedRawAdxl345BusData(RawAdxl345BusData& adxl) {}
void ReaderBase::recievedPWMOutputData(PWMOutputData& pwm) {}
void ReaderBase::recievedCalAnalogueInputData(CalAnalogueInputData& ad) {}
void ReaderBase::recievedRawAnalogueInputData(RawAnalogueInputData& ad) {}
}  // namespace ximu
