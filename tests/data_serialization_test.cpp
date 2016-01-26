#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include "ximuapi/serialization/reader_base.h"

/*
  Copyright 2014 Auke-Dirk Pietersma
*/

// Example on how to deserialize/read ximu data

// user implementation of a ximu reader
// Extend ximu::ReaderBase and implement the 'recieved' methods
// for those data-types that you are interested in.
class ApplicationXimuReader : public ximu::ReaderBase {
 public:
  ApplicationXimuReader()
  :
      _quatCount(0), _calInAndMagCount(0),
      _digitalIOCount(0) {
  }
  size_t QuaternionCount() {
    return _quatCount;
  }

  size_t CalInertialAndMagneticDataCount() {
    return _calInAndMagCount;
  }

 private:
  size_t _quatCount;
  size_t _calInAndMagCount;
  size_t _digitalIOCount;
  
  virtual void recievedQuaternionData(ximu::QuaternionData& q) {
      ++_quatCount;
  }
  virtual void recievedCalInertialAndMagneticData(
    ximu::CalInertialAndMagneticData& c){
      ++_calInAndMagCount;
      auto mag = c.magnetometer();
      auto acc = c.accelerometer();
      auto gyro = c.gyroscope();
    }
  virtual void recievedDateTimeData(ximu::DateTimeData& d){
  }
  virtual void recievedDigitalIOData(ximu::DigitalIOData& diod) {
    ++_digitalIOCount;
  }
};

int main(int argc, char* argv[]) {
  ApplicationXimuReader reader;

  std::string file("ximu.dmp");
  std::vector<unsigned char> bytes;

  // read the dump
  std::ifstream binData(file.c_str(), std::ios_base::in | std::ios::binary);
  unsigned char chr = binData.get();

  while (binData.good()) {
    bytes.push_back(chr);
    chr = binData.get();
  }
  size_t numBytes = bytes.size();

  // simulate a port
  std::random_device rdev;
  std::mt19937 rgen(rdev());

  // we are simulating recieving between 2 and a 100 bytes
  std::uniform_int_distribution<int> dist(2, 100);

  auto head = bytes.begin();
  auto tail = bytes.begin();
  while (numBytes > 0) {
    int steps = dist(rgen);
    if (numBytes - steps < bytes.size()) {
      head = tail;
      std::advance(tail, steps);
       numBytes -= steps;
    } else {
      head = tail;
      tail = bytes.end();
      numBytes = 0;
    }
    reader.fill(head, tail);
    reader.read();
  }

  // test the number of packets found
  // packet count has been confirmed with the c# verion.

  if (reader.QuaternionCount() != 565)
    return 1;

  if (reader.CalInertialAndMagneticDataCount() != 2260)
    return 1;
  return 0;
}
