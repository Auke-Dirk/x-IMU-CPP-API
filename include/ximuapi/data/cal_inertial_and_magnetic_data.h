/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_CAL_INERTIAL_AND_MAGNETIC_DATA_H_
#define INCLUDE_XIMUAPI_DATA_CAL_INERTIAL_AND_MAGNETIC_DATA_H_

#include "ximuapi/data/vector3.h"

namespace ximu {

// <summary>
// Calibrated gyroscope, accelerometer and magnetometer
// data class.
// </summary>
class CalInertialAndMagneticData {
 private:
  Vector3f _gyroscope;
  Vector3f _accelerometer;
  Vector3f _magnetometer;

 public:
  // <summary>
  // Constructors
  // </summary>
  CalInertialAndMagneticData();
  CalInertialAndMagneticData(
      const Vector3f& gyroscope,
      const Vector3f& accelerometer,
      const Vector3f& magnetometer);

  // <summary>
  // Gets or sets the calibrated gyroscope data in degrees per second.
  // </summary>
  Vector3f gyroscope() const;
  void gyroscope(const Vector3f& vec);

  // <summary>
  // Gets or sets the calibrated accelerometer data in 'g'.
  // </summary>
  Vector3f accelerometer() const;
  void accelerometer(const Vector3f& vec);

  // <summary>
  // ets or sets the calibrated magnetometer data in Gauss.
  // </summary>
  Vector3f magnetometer() const;
  void magnetometer(const Vector3f& vec);
};
}  // namespace ximu
#endif  // INCLUDE_XIMUAPI_DATA_CAL_INERTIAL_AND_MAGNETIC_DATA_H_
