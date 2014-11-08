/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_SERIALIZATION_PACKET_READER_H_
#define INCLUDE_XIMUAPI_SERIALIZATION_PACKET_READER_H_

#include <deque>
#include <vector>

#include "ximuapi/packet/packet_construction.h"
#include "ximuapi/data/quaternion_data.h"
#include "ximuapi/data/datetime_data.h"
#include "ximuapi/data/register_data.h"
#include "ximuapi/utils/utility.h"
#include "ximuapi/utils/fixed_float.h"



namespace ximu {
  //  <summary>
  //  The PacketReader class, will read an input buffer
  //  and convert that buffer to data objects. These
  //  objects can be recieved by overloading.
  //  </summary>
class PacketReader {
 public:
  enum ReadResult{INVALID_CHECKSUM, OKE};

  virtual void recievedQuaternionData(QuaternionData& q) = 0;

  // Read the input buffer
  template<typename InputIterator>
  ReadResult read(InputIterator begin, InputIterator end) {
    // working buffer
    std::vector<unsigned char> buffer;

    // decode packet
    PacketEncoding::decodePacket(begin, end, std::back_inserter(buffer));

    // test checksum
    auto checksum = PacketConstruction::checksum(
        buffer.begin(), buffer.end() - 1);

    if (checksum != buffer.back())
      return ReadResult::INVALID_CHECKSUM;

    // todo @aukedirk make use of enum returned
    switch (static_cast<ximu::PacketHeaders>(buffer[0])) {
      case PacketHeaders::QUATERNION_DATA:
        if (readQuaternionData(buffer.begin(), buffer.end()))
          return ReadResult::OKE;
    }
    return ReadResult::OKE;
  }

  //  <summary>
  //  Tries to construct a QuaternionData type
  //  from a collection of unsigned chars
  //  </summary>
  template<typename InputIterator>
  bool readQuaternionData(InputIterator begin, InputIterator end) {
    if (std::distance(begin, end) != 10)
      return false;

    QuaternionData q(
      FixedFloat::toFloat(begin[1], begin[2], Qvals::QUATERNION),
      FixedFloat::toFloat(begin[3], begin[4], Qvals::QUATERNION),
      FixedFloat::toFloat(begin[5], begin[6], Qvals::QUATERNION),
      FixedFloat::toFloat(begin[7], begin[8], Qvals::QUATERNION));

    // pass on the quaterion
    recievedQuaternionData(q);

    return true;
  }

  // obtain the number of bytes used for this packet
  size_t PacketSize(ximu::PacketHeaders header);
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_SERIALIZATION_PACKET_READER_H_
