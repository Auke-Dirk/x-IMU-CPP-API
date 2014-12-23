/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_DIGITAL_IO_DATA_H_
#define INCLUDE_XIMUAPI_DATA_DIGITAL_IO_DATA_H_

#include "ximuapi/data/digital_port_bits.h"

namespace ximu {

class DigitalIOData
{
 private:
  DigitalPortBits _direction;
  DigitalPortBits _state;
 
 public:
  DigitalIOData();
  DigitalIOData(
     unsigned char direction,
     unsigned char state);
  DigitalIOData(
    const DigitalPortBits& direction,
    const DigitalPortBits& state);
   
  DigitalPortBits direction() const;
  DigitalPortBits state() const;
};
}  // namespace ximu
#endif  // INCLUDE_XIMUAPI_DATA_DIGITAL_IO_DATA_H_