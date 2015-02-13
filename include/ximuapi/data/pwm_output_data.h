/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_PWM_OUTPUT_DATA_H_
#define INCLUDE_XIMUAPI_DATA_PWM_OUTPUT_DATA_H_

#include "four_channel_data.h"

namespace ximu {
class PWMOutputData : protected FourChannelData<unsigned short>
{
public:
PWMOutputData(unsigned short a0, unsigned short a2, unsigned short a4, unsigned short a6 ) 
:
  FourChannelData<unsigned short>(a0,a2,a4,a6)
  {}

};
}

#endif  // INCLUDE_XIMUAPI_DATA_PWM_OUTPUT_DATA_H_

