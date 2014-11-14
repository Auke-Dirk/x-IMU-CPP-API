#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include "ximuapi/serialization/writer_base.h"

/*
  Copyright 2014 Auke-Dirk Pietersma
*/

// Example on how to send ximu data

// user implementation of a ximu writer
// Extend ximu::WriterBase and implement the 'sendSerialBuffer'
// method, allowing you to send data to serial port/file etc.
class ApplicationXimuWriter : public ximu::WriterBase {
 public:
  ApplicationXimuWriter()
  :
      _send(0) {
  }
  size_t SendCount() {
    return _send;
  }
 private:
  size_t _send;
  virtual void sendSerialBuffer(std::vector<unsigned char>& data) {
    // send it to your file/serial port/ ec
    ++_send;
  }
};

int main(int argc, char* argv[]) {
  ApplicationXimuWriter writer;

  writer.sendCommandPacket(ximu::CommandCodes::ALGORITHM_CLEAR_TARE);
  writer.sendCommandPacket(ximu::CommandCodes::ALGORITHM_INITIALISE_THEN_TARE);

  ximu::RegisterData reg(ximu::reg::ACCELEROMETER_BIAS_X, 1.0f);
  writer.sendReadRegisterPacket(reg);
  writer.sendWriteRegisterPacket(reg);

  writer.sendReadDateTimePacket();
  ximu::DateTimeData dt;
  writer.sendWriteDateTimePacket(dt);

  if (writer.SendCount() != 6)
    return 1;

  return 0;
}
