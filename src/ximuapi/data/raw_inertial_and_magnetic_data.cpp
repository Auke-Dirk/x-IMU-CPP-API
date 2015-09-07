#include "ximuapi/data/raw_inertial_and_magnetic_data.h"

namespace ximu{

	RawInertialAndMagneticData::RawInertialAndMagneticData() {
	}
	RawInertialAndMagneticData::RawInertialAndMagneticData(
		const Vector3s& gyroscope,
		const Vector3s& accelerometer,
		const Vector3s& magnetometer)
		:
		_gyroscope(gyroscope),
		_accelerometer(accelerometer),
		_magnetometer(magnetometer) {
	}

	RawInertialAndMagneticData::~RawInertialAndMagneticData(){
	}

	Vector3s RawInertialAndMagneticData::gyroscope() const {
		return _gyroscope;
	}

	void RawInertialAndMagneticData::gyroscope(const Vector3s& vec) {
		_gyroscope = vec;
	}

	Vector3s RawInertialAndMagneticData::accelerometer() const {
		return _accelerometer;
	}

	void RawInertialAndMagneticData::accelerometer(const Vector3s& vec) {
		_accelerometer = vec;
	}

	Vector3s RawInertialAndMagneticData::magnetometer() const {
		return _magnetometer;
	}
	void RawInertialAndMagneticData::magnetometer(const Vector3s& vec) {
		_magnetometer = vec;
	}
}