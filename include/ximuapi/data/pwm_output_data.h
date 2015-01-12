/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_PWM_OUTPUT_DATA_H_
#define INCLUDE_XIMUAPI_DATA_PWM_OUTPUT_DATA_H_

#include "four_channel_data.h"

namespace ximu {
class PWMOutputData : protected FourChannelData<ushort>
{
public:
PWMOutputData(ushort a0, ushort a2, ushort a4, ushort a6 ) 
:
  FourChannelData<ushort>(a0,a2,a4,a6)
  {}

};
}

#endif  // INCLUDE_XIMUAPI_DATA_PWM_OUTPUT_DATA_H_

