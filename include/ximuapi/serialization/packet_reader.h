/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_SERIALIZATION_PACKET_READER_H_
#define INCLUDE_XIMUAPI_SERIALIZATION_PACKET_READER_H_

#include <deque>
#include <vector>

#include "ximuapi/packet/packet_construction.h"
#include "ximuapi/packet/packet_deconstruction.h"
#include "ximuapi/data/quaternion_data.h"
#include "ximuapi/data/datetime_data.h"
#include "ximuapi/data/register_data.h"
#include "ximuapi/data/digital_io_data.h"
#include "ximuapi/data/cal_inertial_and_magnetic_data.h"
#include "ximuapi/data/vector3.h"
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
  enum ReadResult{
    OKE,
    NOT_IMPLEMENTED,
    INVALID_CHECKSUM,
    INVALID_PACKET_SIZE
  };

  // Supported data formats
  virtual void recievedQuaternionData(QuaternionData& q) = 0;
  virtual void recievedCalInertialAndMagneticData(
    CalInertialAndMagneticData& c) = 0;
  virtual void recievedDateTimeData(DateTimeData& d) = 0;
  virtual void recievedDigitalIOData(DigitalIOData& diod) = 0;
    
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

    // get the header
    auto header = static_cast<ximu::PacketHeaders>(buffer[0]);

    // packets have an associated size
    if (buffer.size() != PacketSize(header))
      return ReadResult::INVALID_PACKET_SIZE;

    // todo @aukedirk make use of enum returned
    switch (header) {
      case PacketHeaders::CAL_INERTIAL_AND_MAGNETIC_DATA:
      {
	auto cimd = PacketDeconstruction::deconstructCalInertialAndMagneticData(
          buffer.begin(), buffer.end());
        recievedCalInertialAndMagneticData(cimd);  
	return ReadResult::OKE;
      }
      case PacketHeaders::QUATERNION_DATA:
      {
	auto qd = PacketDeconstruction::deconstructQuaternionData(
		      buffer.begin(),buffer.end());
	recievedQuaternionData(qd);
	return ReadResult::OKE;
      }
      case PacketHeaders::WRITE_DATETIME:
      {
	auto wdt = PacketDeconstruction::deconstructWriteDateTimeData(
	  buffer.begin(),buffer.end());
	recievedDateTimeData(wdt);
	return ReadResult::OKE;
      }
      case PacketHeaders::DIGITAL_IO_DATA:
      {
	auto did = PacketDeconstruction::deconstructDigitalIOData(
	  buffer.begin(),buffer.end());
	recievedDigitalIOData(did);
	return ReadResult::OKE;
      }
    }
    return ReadResult::NOT_IMPLEMENTED;
  }

  // obtain the number of bytes used for this packet
  size_t PacketSize(ximu::PacketHeaders header);
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_SERIALIZATION_PACKET_READER_H_
