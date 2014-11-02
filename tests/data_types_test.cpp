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

// Example/test on constructing commands
int main(int argc, char* argv[]) {

  // all input and ouput values have been testing with the c# version


  ////////////////////////////////////////////////////////
  //			RegisterData			//
  ////////////////////////////////////////////////////////
  
  ximu::RegisterData r1(ximu::reg::RegisterAddresses::ALGORITHM_TARE_QUAT_0, 1.234f);
  
  if (r1.value() != 32767)
    return 1;
  
  ximu::RegisterData r2(ximu::reg::RegisterAddresses::BATTERY_BIAS, static_cast<unsigned short>(148));
  
  if (r2.floatValue() != 0.578125)
    return 1;

  /////////////////////////////////////////////////////////
  //			DateTimeData			 //
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
  //		Quaternion                    //
  //////////////////////////////////////////////

  // Constructors
  ximu::Quaternion<float> q1;
  ximu::Quaternion<float> q2(1,0,0,0);
  ximu::QuaternionData q3; // typedef as float as in c#

  std::vector<float> qData = {1.0f, 0.0f, 0.0f, 0.0f};
  ximu::QuaternionData q4(qData.begin(), qData.end());

  if (q1 != q2 || q1 != q3 || q1 != q4)
    return 1;
  
  // normalize 
  ximu::QuaternionData q5(1,2,3,4);
  q5.normalize();
  
  ximu::QuaternionData q6(0.182,0.365,0.547,0.732);
  
  // test if the values are quite similar.
  if (!ximu::Utility::isWithinError(q5.values(), q6.values(), 0.01f))
    return 1;
  
  // conjugate
  ximu::QuaternionData q7(1,2,3,4);
  if (q7.conjugate() != ximu::QuaternionData(1,-2,-3,-4))
    return 1;
  
  // euler angles
  std::vector<float> eulerAngles = {78.690, -47.166, 168.690};
  if (!ximu::Utility::isWithinError(q5.eulerAngles(), eulerAngles, 0.01f))
    return 1;
  
  // rotation matrix
  std::vector<float> rotationMatrix = {
    -0.666, 0.666, 0.333,
    0.133, -0.333, 0.933,
    0.733, 0.666, 0.133 
  };
  if (!ximu::Utility::isWithinError(q5.rotationMatrix(), rotationMatrix, 0.01f))
    return 1;
  
  return 0;
}
