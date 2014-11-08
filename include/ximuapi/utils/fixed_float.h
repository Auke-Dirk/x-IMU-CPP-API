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

/// <summary>
/// Concatenates 2 bytes to return a short.
/// </summary>
/// <param name="MSB">
/// Most Significant Byte.
/// </param>
/// <param name="LSB">
/// Least Significant Byte.
/// </param>
/// <returns>
/// MSB and LSB concatenated to create a short.
/// </returns>
static short toFixed(char msb, char lsb);

/// <summary>
/// Concatenates 2 bytes to return a float.
/// </summary>
/// <param name="MSB">
/// Most Significant Byte.
/// </param>
/// <param name="LSB">
/// Least Significant Byte.
/// </param>
/// <returns>
/// MSB and LSB concatenated to create a float.
/// </returns>
static float toFloat(char msb, char lsb, Qvals q);

// <summary>
// Returns 16-bit fixed-point value from specified floating-point
// value with saturation.
// </summary>
static short toFixed(float floatValue, Qvals q);
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_UTILS_FIXED_FLOAT_H_
