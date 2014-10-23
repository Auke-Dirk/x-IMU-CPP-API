/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include "ximuapi/utils/fixed_float.h"

// Example/Test the encoding and decoding of data packets
int main(int argc, char* argv[]) {


  // these values have been used as test data in the c# application
  float fl1 = 0.301269531;
  short fx1 = 1234;

  if (ximu::FixedFloat::toFloat(fx1, ximu::Qvals::CALIBRATED_BATTERY) != fl1)
    return 1;

  if (ximu::FixedFloat::toFixed(fl1, ximu::Qvals::CALIBRATED_BATTERY) != fx1)
    return 1;

  float fl2 = 0.173278809;
  short fx2 = 5678;

  if (ximu::FixedFloat::toFloat(fx2, ximu::Qvals::QUATERNION) != fl2)
    return 1;

  if (ximu::FixedFloat::toFixed(fl2, ximu::Qvals::QUATERNION) != fx2)
    return 1;
 
  return 0;
}
