/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_QUATERNION_DATA_H_
#define INCLUDE_XIMUAPI_DATA_QUATERNION_DATA_H_

#include <math.h>
#include <vector>
#include <algorithm>

#include "ximuapi/utils/utility.h"
#include "ximuapi/utils/math.h"

namespace ximu {


// <summary>
// Quaternion data class.
// </summary>
// <remarks>
// See http://www.x-io.co.uk/res/doc/quaternions.pdf for more information on
// quaternions.
// </remarks>
template<typename T>
class Quaternion {
 private:
  std::vector<T> _quaternion;
  T _w;
  T _x;
  T _y;
  T _z;

 public:
// Constructors
  Quaternion()
    :
  _w(static_cast<T>(1)),
  _x(static_cast<T>(0)),
  _y(static_cast<T>(0)),
  _z(static_cast<T>(0)) {
  }


  Quaternion(T w, T x , T y, T z)
    :
  _w(w), _x(x), _y(y), _z(z) {
  }

  template<typename InputIterator>
  Quaternion(InputIterator begin, InputIterator end) {
      if (std::distance(begin, end) == 4) {
        _w = *begin;
        _x = *(++begin);
        _y = *(++begin);
        _z = *(++begin);
      }
  }

  // <summary>
  // Quaternion data class.
  // </summary>
  void normalize() {
    T norm = Math::t_sqrt<T>(
    _w * _w + _x * _x +
    _y * _y + _z * _z);

    _w /= norm;
    _x /= norm;
    _y /= norm;
    _z /= norm;
  }

  // Returns the w component
  T w() const {
    return _w;
  }

  // Returns the x component
  T x() const {
    return _x;
  }

  // Returns the y component
  T y() const {
    return _y;
  }

  // Returns the z component
  T z() const {
    return _z;
  }

  // returns all the elements
  std::vector<T> values() {
    return std::vector<T> {
    _w, _x, _y, _z
    };
  }

  // <summary>
  // Returns the quaternion conjugate.
  // </summary>
  Quaternion conjugate() const {
    return Quaternion<T>(_w, -_x, -_y, -_z);
  }

  // <summary>
  // Converts data to rotation matrix.
  // </summary>
  // <remarks>
  // Index order is row major. See http://en.wikipedia.org/wiki/Row-major_order
  // </remarks>
  std::vector<T> rotationMatrix() const {
    T R11 = 2 * _w * _w - 1 + 2 * _x * _x;
    T R12 = 2 * (_x * _y + _w * _z);
    T R13 = 2 * (_x * _z - _w * _y);
    T R21 = 2 * (_x * _y - _w * _z);
    T R22 = 2 * _w * _w - 1 + 2 * _y * _y;
    T R23 = 2 * (_y * _z + _w * _x);
    T R31 = 2 * (_x * _z + _w * _y);
    T R32 = 2 * (_y * _z - _w * _x);
    T R33 = 2 * _w * _w - 1 + 2 * _z * _z;

    return std::vector<T> {
      R11, R12, R13,
      R21, R22, R23,
      R31, R32, R33
    };
  }

  /// <summary>
  /// Converts data to ZYX Euler angles (in degrees).
  /// </summary>
  std::vector<T> eulerAngles() const {
    T phi = static_cast<T>(atan2(
            2 * (_y * _z - _w * _x), 2 * _w * _w - 1 + 2 * _z * _z));
    T theta = static_cast<T>(-atan((2.0 * (_x * _z + _w * _y)) /
              sqrt(1.0 - pow((2.0 * _x * _z + 2.0 * _w * _y), 2.0))));
    T psi = static_cast<T>(atan2(
            2 * (_x * _y - _w * _z), 2 * _w * _w - 1 + 2 * _x * _x));

  return std::vector<T>{
              Math::rad2Deg(phi), Math::rad2Deg(theta), Math::rad2Deg(psi)
         };
  }
};

  // Tests wheter the two quaternions are equal
  template<typename T>
  bool operator==(const Quaternion<T>& lhs, const Quaternion<T> & rhs) {
    return lhs.w() == rhs.w() && lhs.x() == rhs.x() &&
        lhs.y()== rhs.y() && lhs.z() == rhs.z();
  }
  // test for inequality
  template<typename T>
  bool operator!= (const Quaternion<T>& lhs, const Quaternion<T>& rhs) {
    return !(lhs == rhs);
  }

// typedef float to original QuaternionData as in  c#
typedef Quaternion<float> QuaternionData;


}  // namespace ximu
#endif  // INCLUDE_XIMUAPI_DATA_QUATERNION_DATA_H_
