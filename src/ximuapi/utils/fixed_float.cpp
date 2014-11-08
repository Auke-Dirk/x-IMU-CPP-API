/*
  Copyright 2014 Auke-Dirk Pietersma
*/


#include "ximuapi/utils/fixed_float.h"

namespace ximu {

float FixedFloat::toFloat(short fixedValue, Qvals q) {
  return static_cast<float>(fixedValue) /
      static_cast<float>((1 << static_cast<int>(q)));
}

short FixedFloat::toFixed(char msb, char lsb) {
  return (static_cast<short>(msb) << 8) | static_cast<short>(lsb);
}

float FixedFloat::toFloat(char msb, char lsb, Qvals q) {
  return toFloat(toFixed(msb, lsb), q);
}


short FixedFloat::toFixed(float floatValue, Qvals q) {
  int tmp = static_cast<int>(
      floatValue * static_cast<int>(1 << static_cast<int>(q)));

  if (tmp > 32767)
    tmp = 32767;
  else if (tmp < -32768)
    tmp = -32768;

  return static_cast<short>(tmp);
}

}  // namespace ximu
