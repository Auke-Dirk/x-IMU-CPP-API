#include <iostream>
#include <vector>

/*
  Copyright 2014 Auke-Dirk Pietersma
*/


#include "ximuapi/enumerations.h"
#include "ximuapi/data/register_data.h"

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

  return 0;
}
