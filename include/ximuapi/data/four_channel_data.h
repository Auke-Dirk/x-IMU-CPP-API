/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_FOUR_CHANNEL_DATA_H_
#define INCLUDE_XIMUAPI_DATA_FOUR_CHANNEL_DATA_H_

#include <type_traits>

namespace ximu {
// <summary>
// Generic Class that specifies four
// channel data
// T is the internal data 
// T is the external exposed data
// </summary>
  
template<typename T> 
class FourChannelData
{
 private:
  
  // No need to copy non-integral types
  // often the T will be a vector3f of std::vector
  struct internal_type_trait
  {
    // add & to Template
    typedef typename std::conditional<std::is_integral<T>::value, T, T& >::type base_type;
  };
  typedef typename internal_type_trait::base_type base_type;
  
  T _channelA;
  T _channelB;
  T _channelC;
  T _channelD;
 
 public:
  FourChannelData(const base_type a,const base_type b,const base_type c,const base_type d)
  :
    _channelA(a),_channelB(b),
    _channelC(c),_channelD(d) {
    }
  FourChannelData() {
  }
  
  base_type a() { 
    return _channelA;
  }
  
  void a(base_type value) {
    _channelA = value;
  }
  
  base_type b() { 
    return _channelB;
  }
  
  void b(base_type value) {
    _channelB = value;
  }
  
  base_type c() { 
    return _channelC;
  }
  
  void c(base_type value) {
    _channelC = value;
  }
  
  base_type d() { 
    return _channelD;
  }
  
  void d(base_type value) {
    _channelD = value;
  }
};




}  // namespace ximu
#endif  // INCLUDE_XIMUAPI_DATA_FOUR_CHANNEL_DATA_H_




