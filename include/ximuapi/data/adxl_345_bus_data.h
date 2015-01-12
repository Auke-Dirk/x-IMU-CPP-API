/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_ADXL_345_BUS_DATA_H_
#define INCLUDE_XIMUAPI_DATA_ADXL_345_BUS_DATA_H_
#include <string>

#include "ximuapi/data/four_channel_data.h"
#include "ximuapi/utils/utility.h"
#include "ximuapi/data/vector3.h"


/*
 // <summary> Explenations of the channels a through d
 //   a: Gets or sets accelerometer data in 'g'. Elements 0, 1 and 2 represent the sensor x, y and z axes respectively.
 //   b: Gets or sets accelerometer data in 'g'. Elements 0, 1 and 2 represent the sensor x, y and z axes respectively.
 //   c: Gets or sets accelerometer data in 'g'. Elements 0, 1 and 2 represent the sensor x, y and z axes respectively.
 //   d: Gets or sets accelerometer data in 'g'. Elements 0, 1 and 2 represent the sensor x, y and z axes respectively.
 // </summary>
 */




namespace ximu {
class CalAdxl345BusData : public FourChannelData<Vector3f>
{
public:
 CalAdxl345BusData(Vector3f a, Vector3f b, Vector3f c, Vector3f d) 
  :
  FourChannelData<ximu::Vector3f>(a,b,c,d)
  {}
};

class RawAdxl345BusData : public FourChannelData<Vector3s>
{
public:
 RawAdxl345BusData(Vector3s a, Vector3s b, Vector3s c, Vector3s d) 
  :
  FourChannelData<ximu::Vector3s>(a,b,c,d)
  {}
};

}  // namespace ximu
#endif  // INCLUDE_XIMUAPI_DATA_CAL_ADXL_345_BUS_DATA_H_