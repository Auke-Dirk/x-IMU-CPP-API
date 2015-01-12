#ifndef INCLUDE_XIMUAPI_DATA_ANALOGUE_INPUT_DATA_H_
#define INCLUDE_XIMUAPI_DATA_ANALOGUE_INPUT_DATA_H_

#include "ximuapi/data/eight_channel_data.h"

namespace ximu {
 
/*
// <summary>
// channel: description
// a: Gets or sets channel AX0 voltage data in V.
// b: Gets or sets channel AX1 voltage data in V.
// c: Gets or sets channel AX2 voltage data in V.
// d: Gets or sets channel AX3 voltage data in V.
// e: Gets or sets channel AX4 voltage data in V.
// f: Gets or sets channel AX5 voltage data in V.
// g: Gets or sets channel AX6 voltage data in V.
// h: Gets or sets channel AX7 voltage data in V.
*/

class CalAnalogueInputData : public EightChannelData<float>
{
public:
 CalAnalogueInputData(float a,float b, float c, float d,
		      float e,float f, float g, float h) 
  :
  EightChannelData<float>(a,b,c,d,e,f,g,h)
  {}
};


class RawAnalogueInputData : public EightChannelData<short>
{
public:
 RawAnalogueInputData(short a, short b, short c, short d,
		      short e, short f, short g, short h) 
  :
  EightChannelData<short>(a,b,c,d,e,f,g,h)
  {}
};

}  // namespace ximu
#endif  // INCLUDE_XIMUAPI_DATA_ANALOGUE_INPUT_DATA_H_
