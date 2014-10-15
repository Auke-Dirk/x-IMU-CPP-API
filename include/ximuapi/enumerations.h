/*
  Copyright 2014 Auke-Dirk Pietersma legal
*/

#ifndef INCLUDE_XIMUAPI_ENUMERATIONS_H_
#define INCLUDE_XIMUAPI_ENUMERATIONS_H_

namespace ximu {

// <summary>
// Compatible firmware versions. Only major number required.
// </summary>
enum CompatibleFirmwareVersions{
  V10_X = 10
};

// <summary>
// Packet headers.
// </summary>
// <remarks>
// A matching enumeration exists in firmware source.
// </remarks>
enum PacketHeaders{
  ERROR,
  COMMAND,
  READ_REGISTER,
  WRITE_REGISTER,
  READ_DATETIME,
  WRITE_DATETIME,
  RAW_BATTERY_AND_THERMOMETER_DATA,
  CAL_BATTERY_AND_THERMOMETER_DATA,
  RAW_INERTIALAND_MAGNETIC_DATA,
  CAL_INERTIALAND_MAGNETIC_DATA,
  QUATERNION_DATA,
  DIGITAL_IO_DATA,
  RAW_ANALOGUE_INPUT_DATA,
  CAL_ANALOGUE_INPUT_DATA,
  PWM_OUTPUT_DATA,
  RAW_ADXL_345_BUS_DATA,
  CAL_ADXL_345_BUS_DATA,
};

}  // namespace ximu
#endif  // INCLUDE_XIMUAPI_ENUMERATIONS_H_
