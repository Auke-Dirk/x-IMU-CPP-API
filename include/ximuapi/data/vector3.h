/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_VECTOR3_H_
#define INCLUDE_XIMUAPI_DATA_VECTOR3_H_

namespace ximu {

// <summary>
// Simple vector class describing the x y z axis.
// </summary>
template<typename T>
class Vector3 {
 private:
  T _x;
  T _y;
  T _z;

 public: 
  Vector3(const Vector3& other)
    :
     _x(other.x()),
     _y(other.y()),
     _z(other.z()) {
    }
  Vector3()
    :
     _x(static_cast<T>(0)),
     _y(static_cast<T>(0)),
     _z(static_cast<T>(0)) {
    }

  Vector3(T x, T y, T z)
    :
    _x(x), _y(y), _z(z) {
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
};

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
typedef Vector3<short> Vector3s;
}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_DATA_VECTOR3_H_
