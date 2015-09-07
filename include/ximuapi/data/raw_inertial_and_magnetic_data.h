#ifndef INCLUDE_XIMUAPI_DATA_RAW_INTERTIAL_AND_MAGNETIC_DATA_H_
#define INCLUDE_XIMUAPI_DATA_RAW_INTERTIAL_AND_MAGNETIC_DATA_H_

#include "ximuapi/data/vector3.h"

namespace ximu {

	/// <summary>
	/// Calibrated gyroscope, accelerometer and magnetometer
	/// data class.
	/// </summary>

	class RawInertialAndMagneticData
	{
	private:
		Vector3s _gyroscope;
		Vector3s _accelerometer;
		Vector3s _magnetometer;


	public:
		/// <summary>
		/// Constructors
		/// </summary>
		RawInertialAndMagneticData();
		RawInertialAndMagneticData(
			const Vector3s& gyroscope,
			const Vector3s& accelerometer,
			const Vector3s& magnetometer);
		~RawInertialAndMagneticData();

		/// <summary>
		/// Gets or sets the calibrated gyroscope data in degrees per second.
		/// </summary>
		Vector3s gyroscope() const;
		void gyroscope(const Vector3s& vec);

		/// <summary>
		/// Gets or sets the calibrated accelerometer data in 'g'.
		/// </summary>
		Vector3s accelerometer() const;
		void accelerometer(const Vector3s& vec);

		/// <summary>
		/// ets or sets the calibrated magnetometer data in Gauss.
		/// </summary>
		Vector3s magnetometer() const;
		void magnetometer(const Vector3s& vec);
	};

}

#endif //INCLUDE_XIMUAPI_DATA_RAW_INTERTIAL_AND_MAGNETIC_DATA_H_