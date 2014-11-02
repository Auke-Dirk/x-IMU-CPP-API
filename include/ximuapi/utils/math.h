/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_UTILS_MATH_H_
#define INCLUDE_XIMUAPI_UTILS_MATH_H_

#include <math.h>

namespace ximu {

class Math {
 public:  
  // <summary>
  // Converts from radians to degrees.
  // </summary>
  // <param name="radians">
  // Angular quantity in radians.
  // </param> 
  // <returns>
  // Angular quantity in degrees.
  // </returns>
  template<typename T>
  static T rad2Deg(T radians)
  {
    return 57.2957795130823 * radians;
  }
  
  // <summary>
  // square root
  // </summary>
  template<typename T1, typename T2>
  static T1 t_sqrt(T2 value) {
    return static_cast<T1>(sqrt(value));
  }
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_UTILS_MATH_H_
