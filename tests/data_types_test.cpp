#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
/*
  Copyright 2014 Auke-Dirk Pietersma
*/


#include "ximuapi/enumerations.h"
#include "ximuapi/data/register_data.h"
#include "ximuapi/data/datetime_data.h"
#include "ximuapi/data/quaternion_data.h"
#include "ximuapi/data/vector3.h"
#include "ximuapi/data/cal_inertial_and_magnetic_data.h"
#include "ximuapi/data/digital_port_bits.h"


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

  std::vector<float> qData = {1.0f, 0.0f, 0.0f, 0.0f};
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
  std::vector<float> eulerAngles1 = {78.690, -47.166, 168.690};
  std::vector<float> eulerAngles2 = q5.eulerAngles();

  if (!ximu::Utility::isWithinError(eulerAngles1, eulerAngles2, 0.001f))
    return 1;

  // rotation matrix
  std::vector<float> rotationMatrix = {
    -0.666, 0.666, 0.333,
    0.133, -0.333, 0.933,
    0.733, 0.666, 0.133
  };

  float a= rotationMatrix[6];
  float b= rotationMatrix[7];
  float c= rotationMatrix[8];

  if (!ximu::Utility::isWithinError(q5.rotationMatrix(), rotationMatrix, 0.01f))
    return 1;

  //////////////////////////////////////////////
  //        CalInertialAndMagneticData        //
  //////////////////////////////////////////////
  ximu::Vector3f gyro(1.0f,2.0f,3.0f);
  ximu::Vector3f acce(4.0f,5.0f,6.0f);
  ximu::Vector3f magn(7.0f,8.0f,9.0f);
  ximu::CalInertialAndMagneticData ciamd(gyro,acce,magn) ;
  
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
  
  
  /////////////////////////////////
  // 	Digital Port Bits	 //
  /////////////////////////////////
  ximu::DigitalPortBits dpb1(false,false,false,false,false,false,false,false);
  ximu::DigitalPortBits dpb2(true,true,true,true,true,true,true,true);
  
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
  
  return 0;
}
