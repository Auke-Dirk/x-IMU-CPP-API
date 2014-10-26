/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_UTILS_UTILITY_H_
#define INCLUDE_XIMUAPI_UTILS_UTILITY_H_

namespace ximu {

class Utility {
 public:
  // Tests if the query falls within the range, [x1,x2,x3]
  template<typename T, typename T2>
  static bool isWithinInclIncl(T lhs, T rhs, T2 query) {
    return query >= lhs && query <= rhs;
  }
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_UTILS_UTILITY_H_
