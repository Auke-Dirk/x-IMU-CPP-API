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
  RAW_INERTIAL_AND_MAGNETIC_DATA,
  CAL_INERTIAL_AND_MAGNETIC_DATA,
  QUATERNION_DATA,
  DIGITAL_IO_DATA,
  RAW_ANALOGUE_INPUT_DATA,
  CAL_ANALOGUE_INPUT_DATA,
  PWM_OUTPUT_DATA,
  RAW_ADXL_345_BUS_DATA,
  CAL_ADXL_345_BUS_DATA,
};

// <summary>
// Command codes.
// </summary>
// <remarks>
// A matching enumeration exists in firmware source.
// </remarks> 
enum CommandCodes {
  NULL_COMMAND,
  FACTORY_RESET,
  RESET,
  SLEEP,
  RESET_SLEEP_TIMER,
  SAMPLE_GYROSCOPE_AXIS_AT_200DPS,
  CALCULATE_GYROSCOPE_SENSITIVITY,
  SAMPLE_GYROSCOPE_BIAS_TEMP1,
  SAMPLE_GYROSCOPE_BIAS_TEMP2,
  CALCULATE_GYROSCOPE_BIAS_PARAMETERS,
  SAMPLE_ACCELEROMETER_AXIS_AT_1G,
  CALCULATE_ACCELEROMETER_BIAS_AND_SENSITIVITY,
  MEASURE_MAGNETOMETER_BIAS_AND_SENSITIVITY,
  ALGORITHM_INITIALISE,
  ALGORITHM_TARE,
  ALGORITHM_CLEAR_TARE,
  ALGORITHM_INITIALISE_THEN_TARE
};

// <summary>
// Number of fractional bits used by fixed-point representations.
// </summary>
// <remarks>
// A matching enumeration exists in firmware source.
// </remarks> 
enum Qvals {
  CALIBRATED_BATTERY = 12,
  CALIBRATED_THERMOMETER = 8,
  CALIBRATED_GYROSCOPE = 4,
  CALIBRATED_ACCELEROMETER = 11,
  CALIBRATED_MAGNETOMETER = 11,
  QUATERNION = 15,
  BATTERY_SENSITIVITY = 5,
  BATTERY_BIAS = 8,
  THERMOMETER_SENSITIVITY = 6,
  THERMOMETER_BIAS = 0,
  GYROSCOPE_SENSITIVITY = 7,
  GYROSCOPE_SAMPLED_200DPS = 0,
  GYROSCOPE_BIAS_AT_25_DEGC = 3,
  GYROSCOPE_BIAS_TEMP_SENSITIVITY = 11,
  GYROSCOPE_SAMPLED_BIAS = 3,
  ACCELEROMETER_SENSITIVITY = 4,
  ACCELEROMETER_BIAS = 8,
  ACCELEROMETER_SAMPLED_1G = 4,
  MAGNETOMETER_SENSITIVITY = 4,
  MAGNETOMETER_BIAS = 8,
  MAGNETOMETER_HARDIRON_BIAS = 11,
  ALGORITHM_KP = 11,
  ALGORITHM_KI = 15,
  ALGORITHM_INIT_KP = 11,
  ALGORITHM_INIT_PERIOD = 11,
  CALIBRATED_ANALOGUE_INPUT = 12,
  ANALOGUE_INPUT_SENSITIVITY = 4,
  ANALOGUE_INPUT_BIAS = 8,
  CALIBRATED_ADXL_345 = 10,
  ADXL_345_BUS_SENSITIVITY = 6,
  ADXL_345_BUS_BIAS = 8,
  UNDEFINED_QVAL = 0
};

// <summary>
// Register addresses.
// </summary>
// <remarks>
// A matching enumeration exists in firmware source.
// </remarks>

// since a lot of enum values come across in other enumerations
// the biggest enum has its own namespace. To access this enum use 
// the full namespace within ximu, reg::RegisterAddresses::DEVICE_ID
namespace reg { 
  enum RegisterAddresses {
    FIRMWARE_VERSION_MAJOR_NUM,
    FIRMWARE_VERSION_MINOR_NUM,
    DEVICE_ID,
    BUTTON_MODE,
    BATTERY_SENSITIVITY,
    BATTERY_BIAS,
    THERMOMETER_SENSITIVITY,
    THERMOMETER_BIAS,
    GYROSCOPE_FULL_SCALE,
    GYROSCOPE_SENSITIVITY_X,
    GYROSCOPE_SENSITIVITY_Y,
    GYROSCOPE_SENSITIVITY_Z,
    GYROSCOPE_SAMPLED_PLUS_200DPS_X,
    GYROSCOPE_SAMPLED_PLUS_200DPS_Y,
    GYROSCOPE_SAMPLED_PLUS_200DPS_Z,
    GYROSCOPE_SAMPLED_MINUS_200DPS_X,
    GYROSCOPE_SAMPLED_MINUS_200DPS_Y,
    GYROSCOPE_SAMPLED_MINUS_200DPS_Z,
    GYROSCOPE_BIAS_AT_25DEGC_X,
    GYROSCOPE_BIAS_AT_25DEGC_Y,
    GYROSCOPE_BIAS_AT_25DEGC_Z,
    GYROSCOPE_BIAS_TEMP_SENSITIVITY_X,
    GYROSCOPE_BIAS_TEMP_SENSITIVITY_Y,
    GYROSCOPE_BIAS_TEMP_SENSITIVITY_Z,
    GYROSCOPE_SAMPLE_1_TEMP,
    GYROSCOPE_SAMPLE_1_BIAS_X,
    GYROSCOPE_SAMPLE_1_BIAS_Y,
    GYROSCOPE_SAMPLE_1_BIAS_Z,
    GYROSCOPE_SAMPLE_2_TEMP,
    GYROSCOPE_SAMPLE_2_BIAS_X,
    GYROSCOPE_SAMPLE_2_BIAS_Y,
    GYROSCOPE_SAMPLE_2_BIAS_Z,
    ACCELEROMETER_FULL_SCALE,
    ACCELEROMETER_SENSITIVITY_X,
    ACCELEROMETER_SENSITIVITY_Y,
    ACCELEROMETER_SENSITIVITY_Z,
    ACCELEROMETER_BIAS_X,
    ACCELEROMETER_BIAS_Y,
    ACCELEROMETER_BIAS_Z,
    ACCELEROMETER_SAMPLED_PLUS_1G_X,
    ACCELEROMETER_SAMPLED_PLUS_1G_Y,
    ACCELEROMETER_SAMPLED_PLUS_1G_Z,
    ACCELEROMETER_SAMPLED_MINUS_1G_X,
    ACCELEROMETER_SAMPLED_MINUS_1G_Y,
    ACCELEROMETER_SAMPLED_MINUS_1G_Z,
    MAGNETOMETER_FULL_SCALE,
    MAGNETOMETER_SENSITIVITY_X,
    MAGNETOMETER_SENSITIVITY_Y,
    MAGNETOMETER_SENSITIVITY_Z,
    MAGNETOMETER_BIASX,
    MAGNETOMETER_BIASY,
    MAGNETOMETER_BIASZ,
    MAGNETOMETER_HARDIRON_BIAS_X,
    MAGNETOMETER_HARDIRON_BIAS_Y,
    MAGNETOMETER_HARDIRON_BIAS_Z,
    ALGORITHM_MODE,
    ALGORITHM_KP,
    ALGORITHM_KI,
    ALGORITHM_INIT_KP,
    ALGORITHM_INIT_PERIOD,
    ALGORITHM_MINVALID_MAG,
    ALGORITHM_MAXVALID_MAG,
    ALGORITHM_TARE_QUAT_0,
    ALGORITHM_TARE_QUAT_1,
    ALGORITHM_TARE_QUAT_2,
    ALGORITHM_TARE_QUAT_3,
    SENSOR_DATA_MODE,
    DATE_TIME_DATA_RATE,
    BATTERY_AND_THERMOMETER_DATA_RATE,
    INERTIAL_AND_MAGNETIC_DATA_RATE,
    QUATERNION_DATA_RATE,
    SDCARD_NEW_FILENAME,
    BATTERY_SHUTDOWN_VOLTAGE,
    SLEEP_TIMER,
    MOTION_TRIG_WAKEUP,
    BLUETOOTH_POWER,
    AUXILIARY_PORT_MODE,
    DIGITAL_IO_DIRECTION,
    DIGITAL_IO_DATA_RATE,
    ANALOGUE_INPUT_DATA_MODE,
    ANALOGUE_INPUT_DATA_RATE,
    ANALOGUE_INPUT_SENSITIVITY,
    ANALOGUE_INPUT_BIAS,
    PWM_OUTPUT_FREQUENCY,
    ADXL_345_BUS_DATA_MODE,
    ADXL_345_BUS_DATA_RATE,
    ADXL_345A_SENSITIVITY_X,
    ADXL_345A_SENSITIVITY_Y,
    ADXL_345A_SENSITIVITY_Z,
    ADXL_345A_BIAS_X,
    ADXL_345A_BIAS_Y,
    ADXL_345A_BIAS_Z,
    ADXL_345B_SENSITIVITY_X,
    ADXL_345B_SENSITIVITY_Y,
    ADXL_345B_SENSITIVITY_Z,
    ADXL_345B_BIAS_X,
    ADXL_345B_BIAS_Y,
    ADXL_345B_BIAS_Z,
    ADXL_345C_SENSITIVITY_X,
    ADXL_345C_SENSITIVITY_Y,
    ADXL_345C_SENSITIVITY_Z,
    ADXL_345C_BIAS_X,
    ADXL_345C_BIAS_Y,
    ADXL_345C_BIAS_Z,
    ADXL_345D_SENSITIVITY_X,
    ADXL_345D_SENSITIVITY_Y,
    ADXL_345D_SENSITIVITY_Z,
    ADXL_345D_BIAS_X,
    ADXL_345D_BIAS_Y,
    ADXL_345D_BIAS_Z,
    UART_BAUDRATE,
    UART_HARDWARE_FLOWCONTROL,
    NUM_REGISTERS
  };

} // namespace addresses

}  // namespace ximu
#endif  // INCLUDE_XIMUAPI_ENUMERATIONS_H_
