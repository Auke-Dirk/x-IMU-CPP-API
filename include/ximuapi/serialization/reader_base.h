/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_SERIALIZATION_READER_BASE_H_
#define INCLUDE_XIMUAPI_SERIALIZATION_READER_BASE_H_

#include <deque>

#include "ximuapi/data/quaternion_data.h"
#include "ximuapi/data/datetime_data.h"
#include "ximuapi/data/register_data.h"
#include "ximuapi/data/digital_io_data.h"
#include "ximuapi/serialization/packet_reader.h"

namespace ximu {
  //  <summary>
  //  ReaderBase class. Provides the user with easy
  //  access to serializing input buffer to Ximu Data objects.
  //   ReaderBase is not threadsafe.
  //  </summary>

class ReaderBase : protected PacketReader {
 private:
  std::deque<unsigned char> _buffer;
  size_t _maxBufferSize;

 public:
  ReaderBase();

  // returns the buffer state
  bool isFull();

  // returns the buffer state
  bool isEmpty();

  // read as much from the buffer as possible
  void read();

  // methods to fill the buffer
  template<typename InputIterator>
  void fill(InputIterator begin, InputIterator end) {
    size_t toCopy = std::distance(begin, end);
    size_t spaceLeft = _maxBufferSize - _buffer.size();

    std::copy_n(begin, toCopy < spaceLeft ? toCopy : spaceLeft,
                std::back_inserter(_buffer));
  }
  // methods to fill the buffer
  template<typename InputIterator>
  void fill(InputIterator begin, size_t count) {
    size_t spaceLeft = _maxBufferSize - _buffer.size();

    std::copy_n(begin, count < spaceLeft ? count : spaceLeft,
                std::back_inserter(_buffer));
  }

  // implement/override the following methods to obtain the
  // Ximu Data objects
  virtual void recievedQuaternionData(QuaternionData& q);
  virtual void recievedDatTimeData(DateTimeData& d);
  virtual void recievedRegisterData(RegisterData& r);
  virtual void recievedCalInertialAndMagneticData(
    CalInertialAndMagneticData& c);
  virtual void recievedDigitalIOData(DigitalIOData& diod);
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_SERIALIZATION_READER_BASE_H_
