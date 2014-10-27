#include <iostream>
#include <vector>
#include <chrono>
/*
  Copyright 2014 Auke-Dirk Pietersma
*/


#include "ximuapi/enumerations.h"
#include "ximuapi/data/register_data.h"
#include "ximuapi/data/datetime_data.h"

// Example/test on constructing commands
int main(int argc, char* argv[]) {

  // Testing some values for the RegisterData class
  // all input and ouput values have been testing with the c# version
  
  ximu::RegisterData r1(ximu::reg::RegisterAddresses::ALGORITHM_TARE_QUAT_0, 1.234f);
  
  if (r1.value() != 32767)
    return 1;
  
  ximu::RegisterData r2(ximu::reg::RegisterAddresses::BATTERY_BIAS, static_cast<unsigned short>(148));
  
  if (r2.floatValue() != 0.578125)
    return 1;

  // DateTimeData
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
  

  return 0;
}
