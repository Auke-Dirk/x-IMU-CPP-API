/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include "ximuapi/data/cal_inertial_and_magnetic_data.h"

namespace ximu {

CalInertialAndMagneticData::CalInertialAndMagneticData() {
}
CalInertialAndMagneticData::CalInertialAndMagneticData(
     const Vector3f& gyroscope,
     const Vector3f& accelerometer,
     const Vector3f& magnetometer)
    :
    _gyroscope(gyroscope),
    _accelerometer(accelerometer),
    _magnetometer(magnetometer) {
}

Vector3f CalInertialAndMagneticData::gyroscope() const {
  return _gyroscope;
}

void CalInertialAndMagneticData::gyroscope(const Vector3f& vec) {
  _gyroscope = vec;
}

Vector3f CalInertialAndMagneticData::accelerometer() const {
  return _accelerometer;
}

void CalInertialAndMagneticData::accelerometer(const Vector3f& vec) {
  _accelerometer = vec;
}

Vector3f CalInertialAndMagneticData::magnetometer() const {
  return _magnetometer;
}
void CalInertialAndMagneticData::magnetometer(const Vector3f& vec) {
  _magnetometer = vec;
}

}  // namespace ximu
