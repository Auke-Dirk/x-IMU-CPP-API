/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_UTILS_UTILITY_H_
#define INCLUDE_XIMUAPI_UTILS_UTILITY_H_

#include <algorithm>
#include <vector>

namespace ximu {

class Utility {
 public:
  // Tests if the query falls within the range, [x1,x2,x3]
  template<typename T1, typename T2>
  static bool isWithinInclIncl(T1 lhs, T1 rhs, T2 query) {
    return query >= lhs && query <= rhs;
  }

  // Tests if the query falls within the range, <x1,x2,x3>
  template<typename T1, typename T2>
  static bool isWithinExclExcl(T1 lhs, T1 rhs, T2 query) {
    return query > lhs && query < rhs;
  }

  // Compaires two containers, and returns if there
  // element wise difference is within an err bound.
  template<typename T1, typename T2>
  static bool isWithinError(T1 lhs, T1 rhs, T2 err) {
    T1 deltas;
    //  transform to distances
    std::transform(lhs.begin(), lhs.end(), rhs.begin(),
                   std::back_inserter(deltas),
                   [&](double l, double r) {
                     return std::abs(l - r);
                   });
    // accumulate
    T2 clErr =  std::accumulate(deltas.begin(), deltas.end(),
                                static_cast<T2>(0.0));

    return clErr <= err;  // calculated error
  }
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_UTILS_UTILITY_H_
