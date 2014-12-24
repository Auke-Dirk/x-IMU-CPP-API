/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_PACKET_PACKET_DECONSTRUCTION_H_
#define INCLUDE_XIMUAPI_PACKET_PACKET_DECONSTRUCTION_H_

#include <vector>
#include <cmath>
#include <numeric>

#include "ximuapi/enumerations.h"
#include "ximuapi/packet/packet_encoding.h"
#include "ximuapi/data/register_data.h"
#include "ximuapi/data/datetime_data.h"
#include "ximuapi/data/digital_io_data.h"
#include "ximuapi/data/quaternion_data.h"
#include "ximuapi/data/cal_inertial_and_magnetic_data.h"
#include "ximuapi/utils/fixed_float.h"
#include "ximuapi/data/vector3.h"
#include "ximuapi/utils/utility.h"

namespace ximu {
// <summary>
// Packet deconstruction class. Contains static methods for packet
// deconstruction. This class assume's that the inputiterators
// are of correct length. 
// </summary>

class PacketDeconstruction {
 public:

  //  <summary>
  //  Construct a QuaternionData type
  //  from a collection of unsigned chars
  //  </summary>
  template<typename InputIterator>
  static QuaternionData deconstructQuaternionData(InputIterator begin, InputIterator end) {
    return
    QuaternionData (
      FixedFloat::toFloat(begin[1], begin[2], Qvals::QUATERNION),
      FixedFloat::toFloat(begin[3], begin[4], Qvals::QUATERNION),
      FixedFloat::toFloat(begin[5], begin[6], Qvals::QUATERNION),
      FixedFloat::toFloat(begin[7], begin[8], Qvals::QUATERNION));
  }

  //  <summary>
  //  Construct a Read-Intertial and Magnetic data type
  //  from a collection of unsigned chars
  //  </summary>
  template<typename InputIterator>
  static CalInertialAndMagneticData deconstructCalInertialAndMagneticData(
    InputIterator begin, InputIterator end) {
    return
    CalInertialAndMagneticData (
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
  }
  // <summary>
  // Construct a Write DateTimeData packet
  // </summary>
  template<typename InputIterator>
  static DateTimeData deconstructWriteDateTimeData(InputIterator begin,InputIterator end) {
    return
    ximu::DateTimeData (
      (10 * ((begin[1] & 0xF0) >> 4) + begin[1] & 0x0F) + 2000,
      (10 * ((begin[2] & 0xF0) >> 4) + begin[2] & 0x0F),
      (10 * ((begin[3] & 0xF0) >> 4) + begin[3] & 0x0F),
      (10 * ((begin[4] & 0xF0) >> 4) + begin[4] & 0x0F),
      (10 * ((begin[5] & 0xF0) >> 4) + begin[5] & 0x0F),
      (10 * ((begin[6] & 0xF0) >> 4) + begin[6] & 0x0F)
    );
  } 

  // <summary>
  // Tries to construct a digital io data packet
  // </summary>
  template<typename InputIterator>
  static DigitalIOData deconstructDigitalIOData(InputIterator begin, InputIterator end) {
    return DigitalIOData (begin[1],begin[2]);
  }
  

};

}  // ximu
#endif  // INCLUDE_XIMUAPI_PACKET_PACKET_DECONSTRUCTION_H_