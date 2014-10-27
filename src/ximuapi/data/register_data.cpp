/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include "ximuapi/data/register_data.h"
#include "ximuapi/utils/fixed_float.h"
#include "ximuapi/utils/utility.h"

namespace ximu {

RegisterData::RegisterData(reg::RegisterAddresses address)
    :
    RegisterData(address, static_cast<unsigned short>(0)) {
}

RegisterData::RegisterData(reg::RegisterAddresses address, float value)
    :
    _address(address) {
  floatValue(value);
}

RegisterData::RegisterData(reg::RegisterAddresses address,
                           unsigned short value)
    :
    _address(address),
    _value(value) {
}

RegisterData::RegisterData(unsigned short address,
                           unsigned short value)
    :
    _value(value) {
  // check if address falls within the enum
  if (Utility::isWithinInclIncl(
          reg::RegisterAddresses::FIRMWARE_VERSION_MAJOR_NUM,
          reg::RegisterAddresses::NUM_REGISTERS,
          value)
      ) {
    _address = static_cast<reg::RegisterAddresses>(address);
  }
}

reg::RegisterAddresses RegisterData::address() const {
  return _address;
}

void RegisterData::address(reg::RegisterAddresses address) {
  _address = address;
}

unsigned short RegisterData::value() const {
  return _value;
}

void RegisterData::value(unsigned short value) {
  _value = value;
}

float RegisterData::floatValue() const {
  return FixedFloat::toFloat(_value, LookupQval());
}

// <summary>
// Sets 16-bit register value from float interpreted using fixed-point
// precision defined in ximu::Qvals
// </summary>
void RegisterData::floatValue(float value) {
  _value = FixedFloat::toFixed(value, LookupQval());
}


Qvals RegisterData::LookupQval() const {
  switch (_address) {
    /*  case reg::FIRMWARE_VERSION_MAJOR_NUM:
    case reg::FIRMWARE_VERSION_MINOR_NUM:
    case reg::DEVICE_ID:
    case reg::BUTTON_MODE:*/
    case reg::BATTERY_SENSITIVITY:
      return BATTERY_SENSITIVITY;
    case reg::BATTERY_BIAS:
      return BATTERY_BIAS;
    case reg::THERMOMETER_SENSITIVITY:
      return THERMOMETER_SENSITIVITY;
    case reg::THERMOMETER_BIAS:
      return THERMOMETER_BIAS;
      //  case reg::GYROSCOPE_FULL_SCALE:

    case reg::GYROSCOPE_SENSITIVITY_X:
    case reg::GYROSCOPE_SENSITIVITY_Y:
    case reg::GYROSCOPE_SENSITIVITY_Z:
      return GYROSCOPE_SENSITIVITY;

    case reg::GYROSCOPE_SAMPLED_PLUS_200DPS_X:
    case reg::GYROSCOPE_SAMPLED_PLUS_200DPS_Y:
    case reg::GYROSCOPE_SAMPLED_PLUS_200DPS_Z:
    case reg::GYROSCOPE_SAMPLED_MINUS_200DPS_X:
    case reg::GYROSCOPE_SAMPLED_MINUS_200DPS_Y:
    case reg::GYROSCOPE_SAMPLED_MINUS_200DPS_Z:
      return GYROSCOPE_SAMPLED_200DPS;

    case reg::GYROSCOPE_BIAS_AT_25DEGC_X:
    case reg::GYROSCOPE_BIAS_AT_25DEGC_Y:
    case reg::GYROSCOPE_BIAS_AT_25DEGC_Z:
      return GYROSCOPE_BIAS_AT_25_DEGC;

    case reg::GYROSCOPE_BIAS_TEMP_SENSITIVITY_X:
    case reg::GYROSCOPE_BIAS_TEMP_SENSITIVITY_Y:
    case reg::GYROSCOPE_BIAS_TEMP_SENSITIVITY_Z:
      return GYROSCOPE_BIAS_TEMP_SENSITIVITY;

    case reg::GYROSCOPE_SAMPLE_1_TEMP:
      return CALIBRATED_THERMOMETER;

    case reg::GYROSCOPE_SAMPLE_1_BIAS_X:
    case reg::GYROSCOPE_SAMPLE_1_BIAS_Y:
    case reg::GYROSCOPE_SAMPLE_1_BIAS_Z:
      return GYROSCOPE_SAMPLED_BIAS;

    case reg::GYROSCOPE_SAMPLE_2_TEMP:
      return CALIBRATED_THERMOMETER;

    case reg::GYROSCOPE_SAMPLE_2_BIAS_X:
    case reg::GYROSCOPE_SAMPLE_2_BIAS_Y:
    case reg::GYROSCOPE_SAMPLE_2_BIAS_Z:
      return GYROSCOPE_SAMPLED_BIAS;

      //  case reg::ACCELEROMETER_FULL_SCALE:
    case reg::ACCELEROMETER_SENSITIVITY_X:
    case reg::ACCELEROMETER_SENSITIVITY_Y:
    case reg::ACCELEROMETER_SENSITIVITY_Z:
      return ACCELEROMETER_SENSITIVITY;

    case reg::ACCELEROMETER_BIAS_X:
    case reg::ACCELEROMETER_BIAS_Y:
    case reg::ACCELEROMETER_BIAS_Z:
      return ACCELEROMETER_BIAS;

    case reg::ACCELEROMETER_SAMPLED_PLUS_1G_X:
    case reg::ACCELEROMETER_SAMPLED_PLUS_1G_Y:
    case reg::ACCELEROMETER_SAMPLED_PLUS_1G_Z:
    case reg::ACCELEROMETER_SAMPLED_MINUS_1G_X:
    case reg::ACCELEROMETER_SAMPLED_MINUS_1G_Y:
    case reg::ACCELEROMETER_SAMPLED_MINUS_1G_Z:
      return ACCELEROMETER_SAMPLED_1G;

      //    case reg::MAGNETOMETER_FULL_SCALE:
    case reg::MAGNETOMETER_SENSITIVITY_X:
    case reg::MAGNETOMETER_SENSITIVITY_Y:
    case reg::MAGNETOMETER_SENSITIVITY_Z:
      return MAGNETOMETER_SENSITIVITY;

    case reg::MAGNETOMETER_BIASX:
    case reg::MAGNETOMETER_BIASY:
    case reg::MAGNETOMETER_BIASZ:
      return MAGNETOMETER_BIAS;

    case reg::MAGNETOMETER_HARDIRON_BIAS_X:
    case reg::MAGNETOMETER_HARDIRON_BIAS_Y:
    case reg::MAGNETOMETER_HARDIRON_BIAS_Z:
      return MAGNETOMETER_HARDIRON_BIAS;

      //  case reg::ALGORITHM_MODE:
    case reg::ALGORITHM_KP:
      return ALGORITHM_KP;

    case reg::ALGORITHM_KI:
      return ALGORITHM_KI;

    case reg::ALGORITHM_INIT_KP:
      return ALGORITHM_INIT_KP;

    case reg::ALGORITHM_INIT_PERIOD:
      return ALGORITHM_INIT_PERIOD;

    case reg::ALGORITHM_MINVALID_MAG:
    case reg::ALGORITHM_MAXVALID_MAG:
      return CALIBRATED_MAGNETOMETER;

    case reg::ALGORITHM_TARE_QUAT_0:
    case reg::ALGORITHM_TARE_QUAT_1:
    case reg::ALGORITHM_TARE_QUAT_2:
    case reg::ALGORITHM_TARE_QUAT_3:
      return QUATERNION;

      /*case reg::SENSOR_DATA_MODE:
    case reg::DATE_TIME_DATA_RATE:
    case reg::BATTERY_AND_THERMOMETER_DATA_RATE:
    case reg::INERTIAL_AND_MAGNETIC_DATA_RATE:
    case reg::QUATERNION_DATA_RATE:
    case reg::SDCARD_NEW_FILENAME:*/
    case reg::BATTERY_SHUTDOWN_VOLTAGE:
      return CALIBRATED_BATTERY;

      /*case reg::SLEEP_TIMER:
    case reg::MOTION_TRIG_WAKEUP:
    case reg::BLUETOOTH_POWER:
    case reg::AUXILIARY_PORT_MODE:
    case reg::DIGITAL_IO_DIRECTION:
    case reg::DIGITAL_IO_DATA_RATE:
    case reg::ANALOGUE_INPUT_DATA_MODE:
    case reg::ANALOGUE_INPUT_DATA_RATE:*/

    case reg::ANALOGUE_INPUT_SENSITIVITY:
      return ANALOGUE_INPUT_SENSITIVITY;

    case reg::ANALOGUE_INPUT_BIAS:
      return ANALOGUE_INPUT_BIAS;

      /*case reg::PWM_OUTPUT_FREQUENCY:
       case reg::ADXL345_BUS_DATA_MODE:
    case reg::ADXL345_BUS_DATA_RATE:*/

    case reg::ADXL_345A_SENSITIVITY_X:
    case reg::ADXL_345A_SENSITIVITY_Y:
    case reg::ADXL_345A_SENSITIVITY_Z:
      return ADXL_345_BUS_SENSITIVITY;

    case reg::ADXL_345A_BIAS_X:
    case reg::ADXL_345A_BIAS_Y:
    case reg::ADXL_345A_BIAS_Z:
      return ADXL_345_BUS_BIAS;

    case reg::ADXL_345B_SENSITIVITY_X:
    case reg::ADXL_345B_SENSITIVITY_Y:
    case reg::ADXL_345B_SENSITIVITY_Z:
      return ADXL_345_BUS_SENSITIVITY;

    case reg::ADXL_345B_BIAS_X:
    case reg::ADXL_345B_BIAS_Y:
    case reg::ADXL_345B_BIAS_Z:
      return ADXL_345_BUS_BIAS;

    case reg::ADXL_345C_SENSITIVITY_X:
    case reg::ADXL_345C_SENSITIVITY_Y:
    case reg::ADXL_345C_SENSITIVITY_Z:
      return ADXL_345_BUS_SENSITIVITY;

    case reg::ADXL_345C_BIAS_X:
    case reg::ADXL_345C_BIAS_Y:
    case reg::ADXL_345C_BIAS_Z:
      return ADXL_345_BUS_BIAS;

    case reg::ADXL_345D_SENSITIVITY_X:
    case reg::ADXL_345D_SENSITIVITY_Y:
    case reg::ADXL_345D_SENSITIVITY_Z:
      return ADXL_345_BUS_SENSITIVITY;

    case reg::ADXL_345D_BIAS_X:
    case reg::ADXL_345D_BIAS_Y:
    case reg::ADXL_345D_BIAS_Z:
      return ADXL_345_BUS_BIAS;

      /*case reg::UART_BAUDRATE:
        case reg::UART_HARDWARE_FLOWCONTROL:
        case reg::NUM_REGISTERS*/
  }

  return UNDEFINED_QVAL;  // TODO(Auke-Dirk) should we throw exception?
}

}  // namespace ximu
