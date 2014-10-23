/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_UTILS_FIXED_FLOAT_H_
#define INCLUDE_XIMUAPI_UTILS_FIXED_FLOAT_H_


#include "ximuapi/enumerations.h"

namespace ximu {

// <summary>
// 16-bit fixed-point / floating-point conversion class.
// </summary>
class FixedFloat {
 public:
// <summary>
// Returns floating-point value from specified 16-bit fixed-point.
// </summary>
static float toFloat(short fixedValue, Qvals q);

// <summary>
// Returns 16-bit fixed-point value from specified floating-point
// value with saturation.
// </summary>
static short toFixed(float floatValue, Qvals q);
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_UTILS_FIXED_FLOAT_H_
