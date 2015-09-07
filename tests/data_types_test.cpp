#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <limits>
/*
Copyright 2014 Auke-Dirk Pietersma
*/


#include "ximuapi/enumerations.h"
#include "ximuapi/data/register_data.h"
#include "ximuapi/data/datetime_data.h"
#include "ximuapi/data/quaternion_data.h"
#include "ximuapi/data/vector3.h"
#include "ximuapi/data/cal_inertial_and_magnetic_data.h"
#include "ximuapi/data/raw_inertial_and_magnetic_data.h"
#include "ximuapi/data/digital_port_bits.h"
#include "ximuapi/data/digital_io_data.h"
#include "ximuapi/data/raw_battery_and_thermometer_data.h"
#include "ximuapi/data/cal_battery_and_thermometer_data.h"

#include "ximuapi\data\analogue_input_data.h"
#include "ximuapi\data\adxl_345_bus_data.h"
#include "ximuapi\data\pwm_output_data.h"



bool CompareFloates(float A, float B)
{
	return (A - B < FLT_EPSILON) && (-(A - B) < FLT_EPSILON);
}

// Example/test on constructing commands
int main(int argc, char* argv[]) {
	// all input and ouput values have been testing with the c# version

	////////////////////////////////////////////////////////
	//                 RegisterData                       //
	////////////////////////////////////////////////////////

	ximu::RegisterData r1(
		ximu::reg::RegisterAddresses::ALGORITHM_TARE_QUAT_0, 1.234f);
	if (r1.value() != 32767)
		return 1;

	ximu::RegisterData r2(ximu::reg::RegisterAddresses::BATTERY_BIAS,
		static_cast<unsigned short>(148));
	if (r2.floatValue() != 0.578125)
		return 1;

	/////////////////////////////////////////////////////////
	//                 DateTimeData                        //
	/////////////////////////////////////////////////////////

	ximu::DateTimeData dtd1;
	if (dtd1.year() != 2000 || dtd1.month() != 1 || dtd1.day() != 1 ||
		dtd1.hours() != 0 || dtd1.minutes() != 0 || dtd1.seconds() != 0)
		return 1;

	// test the setters
	dtd1.year(2001);
	dtd1.month(2);
	dtd1.day(3);
	dtd1.hours(4);
	dtd1.minutes(5);
	dtd1.seconds(6);


	if (dtd1.year() != 2001 || dtd1.month() != 2 || dtd1.day() != 3 ||
		dtd1.hours() != 4 || dtd1.minutes() != 5 || dtd1.seconds() != 6)
		return 1;

	// test with c/c++ time struct
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t tt = std::chrono::system_clock::to_time_t(now);
	std::tm l_tm = *localtime(&tt);

	ximu::DateTimeData dtd2(l_tm);

	if (l_tm.tm_year != dtd2.year() || l_tm.tm_mon != dtd2.month() ||
		l_tm.tm_mday != dtd2.day() || l_tm.tm_hour != dtd2.hours() ||
		l_tm.tm_min != dtd2.minutes() || l_tm.tm_sec != dtd2.seconds()
		)
		return 1;

	//////////////////////////////////////////////
	//            Quaternion                    //
	//////////////////////////////////////////////

	// Constructors
	ximu::Quaternion<float> q1;
	ximu::Quaternion<float> q2(1, 0, 0, 0);
	ximu::QuaternionData q3;  // typedef as float as in c#

	std::vector<float> qData = { 1.0f, 0.0f, 0.0f, 0.0f };
	ximu::QuaternionData q4(qData.begin(), qData.end());

	if (q1 != q2 || q1 != q3 || q1 != q4)
		return 1;

	// normalize
	ximu::QuaternionData q5(1, 2, 3, 4);
	q5.normalize();

	ximu::QuaternionData q6(0.182, 0.365, 0.547, 0.732);

	// test if the values are quite similar.
	if (!ximu::Utility::isWithinError(q5.values(), q6.values(), 0.01f))
		return 1;

	// conjugate
	ximu::QuaternionData q7(1, 2, 3, 4);
	if (q7.conjugate() != ximu::QuaternionData(1, -2, -3, -4))
		return 1;

	// euler angles
	std::vector<float> eulerAngles1 = { 78.690f, -47.166f, 168.690f };
	std::vector<float> eulerAngles2 = q5.eulerAngles();

	if (!ximu::Utility::isWithinError(eulerAngles1, eulerAngles2, 0.001f))
		return 1;

	// rotation matrix
	std::vector<float> rotationMatrix = {
		-0.666f, 0.666f, 0.333f,
		0.133f, -0.333f, 0.933f,
		0.733f, 0.666f, 0.133f
	};

	float a = rotationMatrix[6];
	float b = rotationMatrix[7];
	float c = rotationMatrix[8];

	if (!ximu::Utility::isWithinError(q5.rotationMatrix(), rotationMatrix, 0.01f))
		return 1;

	//////////////////////////////////////////////
	//        CalInertialAndMagneticData        //
	//////////////////////////////////////////////
	ximu::Vector3f gyro(1.0f, 2.0f, 3.0f);
	ximu::Vector3f acce(4.0f, 5.0f, 6.0f);
	ximu::Vector3f magn(7.0f, 8.0f, 9.0f);
	ximu::CalInertialAndMagneticData ciamd(gyro, acce, magn);

	if (ciamd.gyroscope().x() != gyro.x() ||
		ciamd.gyroscope().y() != gyro.y() ||
		ciamd.gyroscope().z() != gyro.z() ||
		ciamd.accelerometer().x() != acce.x() ||
		ciamd.accelerometer().y() != acce.y() ||
		ciamd.accelerometer().z() != acce.z() ||
		ciamd.magnetometer().x() != magn.x() ||
		ciamd.magnetometer().y() != magn.y() ||
		ciamd.magnetometer().z() != magn.z()) {

		return 1;
	}


	//////////////////////////////////////////////
	////        RawInertialAndMagneticData      //
	//////////////////////////////////////////////
	
	ximu::Vector3s gyro_r(1.0f, 2.0f, 3.0f);
	ximu::Vector3s acce_r(4.0f, 5.0f, 6.0f);
	ximu::Vector3s magn_r(7.0f, 8.0f, 9.0f);
	ximu::RawInertialAndMagneticData riamd(gyro_r, acce_r, magn_r);

	if (riamd.gyroscope().x() != gyro_r.x() ||
		riamd.gyroscope().y() != gyro_r.y() ||
		riamd.gyroscope().z() != gyro_r.z() ||
		riamd.accelerometer().x() != acce_r.x() ||
		riamd.accelerometer().y() != acce_r.y() ||
		riamd.accelerometer().z() != acce_r.z() ||
		riamd.magnetometer().x() != magn_r.x() ||
		riamd.magnetometer().y() != magn_r.y() ||
		riamd.magnetometer().z() != magn_r.z()) {

		return 1;
	}
	

	/////////////////////////////////
	// 	Digital Port Bits	 //
	/////////////////////////////////
	ximu::DigitalPortBits dpb1(false, false, false, false, false, false, false, false);
	ximu::DigitalPortBits dpb2(true, true, true, true, true, true, true, true);

	for (size_t portIndex = 0; portIndex != 8; ++portIndex) {
		if (dpb1.get(portIndex))
			return 1;
		if (!dpb2.get(portIndex))
			return 1;
	}

	if (dpb1.byte() != 0 || dpb2.byte() != 255)
		return 1;
	if (dpb1 != ximu::DigitalPortBits(0) || dpb2 != ximu::DigitalPortBits(255) || dpb1 == dpb2)
		return 1;


	if (dpb1.ax0() || !dpb2.ax0())
		return 1;
	if (dpb1.ax1() || !dpb2.ax1())
		return 1;
	if (dpb1.ax2() || !dpb2.ax2())
		return 1;
	if (dpb1.ax3() || !dpb2.ax3())
		return 1;
	if (dpb1.ax4() || !dpb2.ax4())
		return 1;
	if (dpb1.ax5() || !dpb2.ax5())
		return 1;
	if (dpb1.ax6() || !dpb2.ax6())
		return 1;
	if (dpb1.ax7() || !dpb2.ax7())
		return 1;

	/////////////////////
	// Digital IO Data //
	/////////////////////
	ximu::DigitalIOData diod1(dpb1, dpb2);
	if (diod1.direction() != dpb1)
		return 1;
	if (diod1.state() != dpb2)
		return 1;


	//////////////////////////////////////////////
	//            CalAnalogueInputData          //
	//////////////////////////////////////////////


	std::vector<float> fTestSet = { std::numeric_limits<float>::min(),
		std::numeric_limits<float>::max(),
		0.0f, 12.0f, -500.12f,
		0.014f, -1020.1234f, 12.4f };

	ximu::CalAnalogueInputData carInTest(fTestSet[0], fTestSet[1], fTestSet[2], fTestSet[3],
		fTestSet[4], fTestSet[5], fTestSet[6], fTestSet[7]);

	if (!CompareFloates(carInTest.a(), fTestSet[0]) || !CompareFloates(carInTest.b(), fTestSet[1]) ||
		!CompareFloates(carInTest.c(), fTestSet[2]) || !CompareFloates(carInTest.d(), fTestSet[3]) ||
		!CompareFloates(carInTest.e(), fTestSet[4]) || !CompareFloates(carInTest.f(), fTestSet[5]) ||
		!CompareFloates(carInTest.g(), fTestSet[6]) || !CompareFloates(carInTest.h(), fTestSet[7]))
		return 1;

	std::vector<short> sTestSet = { std::numeric_limits<short>::min(),
		std::numeric_limits<short>::max(),
		2, -2, 4, 555, -640, 1024 };

	//////////////////////////////////////////////
	//            RawAnalogueInputData          //
	//////////////////////////////////////////////

	ximu::RawAnalogueInputData rawInTest(sTestSet[0], sTestSet[1], sTestSet[2], sTestSet[3],
		sTestSet[4], sTestSet[5], sTestSet[6], sTestSet[7]);

	if (rawInTest.a() != sTestSet[0] || rawInTest.b() != sTestSet[1] ||
		rawInTest.c() != sTestSet[2] || rawInTest.d() != sTestSet[3] ||
		rawInTest.e() != sTestSet[4] || rawInTest.f() != sTestSet[5] ||
		rawInTest.g() != sTestSet[6] || rawInTest.h() != sTestSet[7])
		return 1;


	//////////////////////////////////////////////
	//            CalAdxl345BusData             //
	//////////////////////////////////////////////

	std::vector<ximu::Vector3f> vec3fTestSet = { ximu::Vector3f(std::numeric_limits<float>::min(), 0.0f, 12.12f),
		ximu::Vector3f(std::numeric_limits<float>::max(), -12.12f, 53.85f),
		ximu::Vector3f(0.0f, 0.0f, 0.0f),
		ximu::Vector3f(12.12f, -56.12f, 45.89f) };

	ximu::CalAdxl345BusData calBusData(vec3fTestSet[0], vec3fTestSet[1], vec3fTestSet[2], vec3fTestSet[3]);

	if (!CompareFloates(calBusData.a().x(), vec3fTestSet[0].x()) ||
		!CompareFloates(calBusData.b().y(), vec3fTestSet[1].y()) ||
		!CompareFloates(calBusData.c().z(), vec3fTestSet[2].z()))
		return 1;

	//////////////////////////////////////////////
	//            RawAdxl345BusData             //
	//////////////////////////////////////////////


	std::vector<ximu::Vector3s> vec3sTestSet = { ximu::Vector3s(std::numeric_limits<short>::min(), 0, 12),
		ximu::Vector3s(std::numeric_limits<short>::max(), -12, 53),
		ximu::Vector3s(0, 0, 0),
		ximu::Vector3s(12, -56, 45) };

	ximu::RawAdxl345BusData rawBusData(vec3sTestSet[0], vec3sTestSet[1], vec3sTestSet[2], vec3sTestSet[3]);

	if (rawBusData.a().x() != vec3sTestSet[0].x() ||
		rawBusData.b().y() != vec3sTestSet[1].y() ||
		rawBusData.c().z() != vec3sTestSet[2].z())
		return 1;


	//////////////////////////////////////////////
	//            PWMOutputData                 //
	//////////////////////////////////////////////

	std::vector<unsigned short> usTestSet{ 0, 2, 4, 6 };
	ximu::PWMOutputData pwmOutputData(usTestSet[0], usTestSet[1], usTestSet[2], usTestSet[3]);

	// getters are inherited as protected methods

	//if (pwmOutputData.a() != usTestSet[0] ||
	// pwmOutputData.b() != usTestSet[1] ||
	// pwmOutputData.c() != usTestSet[2] ||
	// pwmOutputData.d() != usTestSet[3])
	// return 1;


	//////////////////////////////////////////////
	//       CalBatteryAndThermometerData       //
	//////////////////////////////////////////////

	float _batVolt0f = 0.32;
	float _themp0f = 37.5;
	float _batVolt1f = 2.999;
	float _themp1f = -11.5;

	ximu::CalBatteryAndThermometerData cbatd(_batVolt0f, _themp0f);

	if (!CompareFloates(cbatd.batteryVoltage(), _batVolt0f), !CompareFloates(cbatd.thermometer(), _themp0f))
		return 1;
	
	cbatd.batteryVoltage(_batVolt1f);
	cbatd.thermometer(_themp1f);

	if (!CompareFloates(cbatd.batteryVoltage(), _batVolt1f), !CompareFloates(cbatd.thermometer(), _themp1f))
		return 1;


	short _batVolt0s = 11;
	short _themp0s = 21;
	short _batVolt1s = 5;
	short _themp1s = -5;

	//////////////////////////////////////////////
	//       RawBatteryAndThermometerData       //
	//////////////////////////////////////////////

	ximu::RawBatteryAndThermometerData rbatd(_batVolt0s, _themp0s);

	if (rbatd.batteryVoltage() != _batVolt0s || rbatd.thermometer() != _themp0s)
		return 1;

	rbatd.batteryVoltage(_batVolt1s);
	rbatd.thermometer(_themp1s);

	if (rbatd.batteryVoltage() != _batVolt1s || rbatd.thermometer() != _themp1s)
		return 1;
		

	return 0;
}
