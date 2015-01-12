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
#include "ximuapi/data/analogue_input_data.h"
#include "ximuapi/data/register_data.h"
#include "ximuapi/data/datetime_data.h"
#include "ximuapi/data/digital_io_data.h"
#include "ximuapi/data/quaternion_data.h"
#include "ximuapi/data/cal_inertial_and_magnetic_data.h"
#include "ximuapi/data/adxl_345_bus_data.h"
#include "ximuapi/data/pwm_output_data.h"
#include "ximuapi/data/eight_channel_data.h"
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
  
  
  // <summary>
  // Construct a Calibrated ADXL345 bus data class
  // </summary>
  template<typename InputIterator>
  static CalAdxl345BusData deconstructCalAdxl345BusData(
    InputIterator begin, InputIterator end)
  {
    return CalAdxl345BusData(
      Vector3f(
	FixedFloat::toFloat(begin[1],begin[2],Qvals::CALIBRATED_ADXL_345),
	FixedFloat::toFloat(begin[3],begin[4],Qvals::CALIBRATED_ADXL_345),
	FixedFloat::toFloat(begin[5],begin[6],Qvals::CALIBRATED_ADXL_345)
      ),
      
      Vector3f(
	FixedFloat::toFloat(begin[7],begin[8],Qvals::CALIBRATED_ADXL_345),
	FixedFloat::toFloat(begin[9],begin[10],Qvals::CALIBRATED_ADXL_345),
	FixedFloat::toFloat(begin[11],begin[12],Qvals::CALIBRATED_ADXL_345)
      ),
      
      Vector3f(
	FixedFloat::toFloat(begin[13],begin[14],Qvals::CALIBRATED_ADXL_345),
	FixedFloat::toFloat(begin[15],begin[16],Qvals::CALIBRATED_ADXL_345),
	FixedFloat::toFloat(begin[17],begin[18],Qvals::CALIBRATED_ADXL_345)
      ),
      
      Vector3f(
	FixedFloat::toFloat(begin[19],begin[20],Qvals::CALIBRATED_ADXL_345),
	FixedFloat::toFloat(begin[21],begin[22],Qvals::CALIBRATED_ADXL_345),
	FixedFloat::toFloat(begin[23],begin[24],Qvals::CALIBRATED_ADXL_345)
      )
    );
  }
  
  // <summary>
  // Construct a Calibrated ADXL345 bus data class
  // </summary>
  template<typename InputIterator>
  static RawAdxl345BusData deconstructRawAdxl345BusData(
    InputIterator begin, InputIterator end)
  {
    return RawAdxl345BusData(
      Vector3s(
	FixedFloat::toFixed(begin[1],begin[2]),
	FixedFloat::toFixed(begin[3],begin[4]),
	FixedFloat::toFixed(begin[5],begin[6])
      ),
      
      Vector3s(
	FixedFloat::toFixed(begin[7],begin[8]),
	FixedFloat::toFixed(begin[9],begin[10]),
	FixedFloat::toFixed(begin[11],begin[12])
      ),
      
      Vector3s(
	FixedFloat::toFixed(begin[13],begin[14]),
	FixedFloat::toFixed(begin[15],begin[16]),
	FixedFloat::toFixed(begin[17],begin[18])
      ),
      
      Vector3s(
	FixedFloat::toFixed(begin[19],begin[20]),
	FixedFloat::toFixed(begin[21],begin[22]),
	FixedFloat::toFixed(begin[23],begin[24])
      )
    );
  }
  
  // <summary>
  // Construct a PWM output data
  // </summary>
  template<typename InputIterator>
  static PWMOutputData deconstructPWMOutputData (
    InputIterator begin, InputIterator end)
  {
    return PWMOutputData(
      FixedFloat::toFixed(begin[1],begin[2]),   
      FixedFloat::toFixed(begin[3],begin[4]),
      FixedFloat::toFixed(begin[5],begin[6]),
      FixedFloat::toFixed(begin[7],begin[8])
    );
  }
  
  // <summary>
  // Construct Raw Analogue input data
  // </summar>
  template<typename InputIterator>
  static RawAnalogueInputData deconstructRawAnalogueInputData
  (InputIterator begin, InputIterator end)
  {
    return RawAnalogueInputData (
      FixedFloat::toFixed(begin[1],begin[2]),
      FixedFloat::toFixed(begin[3],begin[4]),
      FixedFloat::toFixed(begin[5],begin[6]),
      FixedFloat::toFixed(begin[7],begin[8]),
      FixedFloat::toFixed(begin[9],begin[10]),
      FixedFloat::toFixed(begin[11],begin[12]),
      FixedFloat::toFixed(begin[13],begin[14]),
      FixedFloat::toFixed(begin[15],begin[16])
    );
  }
  
  
  // <summary>
  // Construct Cal Analogue input data
  // </summar>
  template<typename InputIterator>
  static CalAnalogueInputData deconstructCalAnalogueInputData
  (InputIterator begin, InputIterator end)
  {
    return CalAnalogueInputData (
      FixedFloat::toFloat(begin[1],begin[2],Qvals::CALIBRATED_ANALOGUE_INPUT),
      FixedFloat::toFloat(begin[3],begin[4],Qvals::CALIBRATED_ANALOGUE_INPUT),
      FixedFloat::toFloat(begin[5],begin[6],Qvals::CALIBRATED_ANALOGUE_INPUT),
      FixedFloat::toFloat(begin[7],begin[8],Qvals::CALIBRATED_ANALOGUE_INPUT),
      FixedFloat::toFloat(begin[9],begin[10],Qvals::CALIBRATED_ANALOGUE_INPUT),
      FixedFloat::toFloat(begin[11],begin[12],Qvals::CALIBRATED_ANALOGUE_INPUT),
      FixedFloat::toFloat(begin[13],begin[14],Qvals::CALIBRATED_ANALOGUE_INPUT),
      FixedFloat::toFloat(begin[15],begin[16],Qvals::CALIBRATED_ANALOGUE_INPUT)
    );
  }
  
  
  template<typename InputIterator, typename T>
  static EightChannelData<T> deconstructEightChannelData (
    InputIterator begin, InputIterator end)
  {
    return EightChannelData<T> (
      FixedFloat::toFixed(begin[1],begin[2]),
      FixedFloat::toFixed(begin[3],begin[4]),
      FixedFloat::toFixed(begin[5],begin[6]),
      FixedFloat::toFixed(begin[7],begin[8]),
      FixedFloat::toFixed(begin[9],begin[10]),
      FixedFloat::toFixed(begin[11],begin[12]),
      FixedFloat::toFixed(begin[13],begin[14]),
      FixedFloat::toFixed(begin[15],begin[16])
    );
  }
};

}  // ximu
#endif  // INCLUDE_XIMUAPI_PACKET_PACKET_DECONSTRUCTION_H_