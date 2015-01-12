/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_EIGHT_CHANNEL_DATA_H_
#define INCLUDE_XIMUAPI_DATA_EIGHT_CHANNEL_DATA_H_

#include <type_traits>

namespace ximu {
// <summary>
// Generic Class that specifies 8
// channel data
// T is the internal data 
// T is the external exposed data
// </summary>
  
template<typename T> 
class EightChannelData
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
  T _channelE;
  T _channelF;
  T _channelG;
  T _channelH;
  
 public:
  EightChannelData(const base_type a,const base_type b,const base_type c,const base_type d,
		   const base_type e,const base_type f,const base_type g,const base_type h
  )
  :
    _channelA(a),_channelB(b),
    _channelC(c),_channelD(d),
    _channelE(e),_channelF(f),
    _channelG(g),_channelH(h) {
    }
  EightChannelData() {
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
  
  base_type e() { 
    return _channelE;
  }
  
  void e(base_type value) {
    _channelE = value;
  }
  
  base_type f() { 
    return _channelF;
  }
  
  void f(base_type value) {
    _channelF = value;
  }
  
  base_type g() { 
    return _channelG;
  }
  
  void g(base_type value) {
    _channelG = value;
  }
  
  base_type h() { 
    return _channelH;
  }
  
  void h(base_type value) {
    _channelH = value;
  }
};

}  // namespace ximu
#endif  // INCLUDE_XIMUAPI_DATA_EIGHT_CHANNEL_DATA_H_




