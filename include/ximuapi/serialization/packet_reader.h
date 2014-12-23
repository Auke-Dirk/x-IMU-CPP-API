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
        if (readCalInertialAndMagneticData(
                buffer.begin(), buffer.end()))
          return ReadResult::OKE;

      case PacketHeaders::QUATERNION_DATA:
        if (readQuaternionData(buffer.begin(), buffer.end()))
          return ReadResult::OKE;

      case PacketHeaders::WRITE_DATETIME:
	if (readWriteDateTime(buffer.begin(),buffer.end()))
	  return ReadResult::OKE;
    
      case PacketHeaders::DIGITAL_IO_DATA:
	if (readDigitalIOData(buffer.begin(),buffer.end()))
	    return ReadResult::OKE;
    }
    return ReadResult::NOT_IMPLEMENTED;
  }

  //  <summary>
  //  Tries to construct a QuaternionData type
  //  from a collection of unsigned chars
  //  </summary>
  template<typename InputIterator>
  bool readQuaternionData(InputIterator begin, InputIterator end) {
    QuaternionData q(
      FixedFloat::toFloat(begin[1], begin[2], Qvals::QUATERNION),
      FixedFloat::toFloat(begin[3], begin[4], Qvals::QUATERNION),
      FixedFloat::toFloat(begin[5], begin[6], Qvals::QUATERNION),
      FixedFloat::toFloat(begin[7], begin[8], Qvals::QUATERNION));

    // pass on the quaterion
    recievedQuaternionData(q);

    return true;
  }

  //  <summary>
  //  Tries to construct a Read-Intertial and Magnetic data type
  //  from a collection of unsigned chars
  //  </summary>
  template<typename InputIterator>
  bool readCalInertialAndMagneticData(
    InputIterator begin, InputIterator end) {
    CalInertialAndMagneticData c(
      // gyroscope
      Vector3f(
          FixedFloat::toFloat(begin[1], begin[2], Qvals::CALIBRATED_GYROSCOPE),
          FixedFloat::toFloat(begin[3], begin[4], Qvals::CALIBRATED_GYROSCOPE),
          FixedFloat::toFloat(begin[5], begin[6], Qvals::CALIBRATED_GYROSCOPE)),
      // accelerometer
      Vector3f(
          FixedFloat::toFloat(begin[7], begin[8],
                              Qvals::CALIBRATED_ACCELEROMETER),
          FixedFloat::toFloat(begin[9], begin[10],
                              Qvals::CALIBRATED_ACCELEROMETER),
          FixedFloat::toFloat(begin[11], begin[12],
                              Qvals::CALIBRATED_ACCELEROMETER)),
      // magnetometer
      Vector3f(
          FixedFloat::toFloat(begin[13], begin[14],
                              Qvals::CALIBRATED_ACCELEROMETER),
          FixedFloat::toFloat(begin[15], begin[16],
                              Qvals::CALIBRATED_ACCELEROMETER),
          FixedFloat::toFloat(begin[17], begin[18],
                              Qvals::CALIBRATED_MAGNETOMETER)));
    // pass on the data
    recievedCalInertialAndMagneticData(c);

    return true;
  }
  // <summary>
  // Tries to construct a Write DateTimeData packet
  // </summary>
  template<typename InputIterator>
  bool readWriteDateTime(InputIterator begin,InputIterator end) {
  
    ximu::DateTimeData data(
      (10 * ((begin[1] & 0xF0) >> 4) + begin[1] & 0x0F) + 2000,
      (10 * ((begin[2] & 0xF0) >> 4) + begin[2] & 0x0F),
      (10 * ((begin[3] & 0xF0) >> 4) + begin[3] & 0x0F),
      (10 * ((begin[4] & 0xF0) >> 4) + begin[4] & 0x0F),
      (10 * ((begin[5] & 0xF0) >> 4) + begin[5] & 0x0F),
      (10 * ((begin[6] & 0xF0) >> 4) + begin[6] & 0x0F)
    );
    
    // pass on
    recievedDateTimeData(data);
    return true;
  }

  // <summary>
  // Tries to construct a digital io data packet
  // </summary>
  template<typename InputIterator>
  bool readDigitalIOData(InputIterator begin, InputIterator end) {
    DigitalIOData diod(begin[1],begin[2]);
    recievedDigitalIOData(diod);
    return true;
  }
  
  // obtain the number of bytes used for this packet
  size_t PacketSize(ximu::PacketHeaders header);
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_SERIALIZATION_PACKET_READER_H_
