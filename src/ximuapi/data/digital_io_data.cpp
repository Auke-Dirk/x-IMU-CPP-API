/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include "ximuapi/data/digital_io_data.h"

namespace ximu {

  DigitalIOData::DigitalIOData()
  :
    _direction(0),
    _state(0) {
  }
    
  DigitalIOData::DigitalIOData(
    unsigned char direction,
    unsigned char state)
  :
    _direction(direction),
    _state(state){
  }
  
  DigitalIOData::DigitalIOData(
    const DigitalPortBits& direction,
    const DigitalPortBits& state)
  :
    _direction(direction.byte()),
    _state(state.byte()){
    }
  
  DigitalPortBits DigitalIOData::direction() const {
    return _direction;
  }
  
  DigitalPortBits DigitalIOData::state() const {
    return _state;
  }
  
}  // namespace ximu
