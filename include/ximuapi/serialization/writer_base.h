/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_SERIALIZATION_WRITER_BASE_H_
#define INCLUDE_XIMUAPI_SERIALIZATION_WRITER_BASE_H_

#include <vector>

#include "ximuapi/data/quaternion_data.h"
#include "ximuapi/data/datetime_data.h"
#include "ximuapi/data/register_data.h"
#include "ximuapi/data/digital_io_data.h"

namespace ximu {

  //  <summary>
  //  The WriterBase class helps to convert
  //  ximu data object to buffers that can potentially
  //  be send to the actual XIMU.
  //  </summary>
class WriterBase {
  // the actual buffer should be written
  // to the comport in the child class.
 public:
  virtual void sendSerialBuffer
    (std::vector<unsigned char>& buffer) = 0;
  void sendReadRegisterPacket(RegisterData& r);
  void sendWriteRegisterPacket(RegisterData& r);
  void sendReadDateTimePacket();
  void sendWriteDateTimePacket(DateTimeData& d);
  void sendCommandPacket(CommandCodes code);
  void sendDigitalIOPacket(DigitalIOData& d);
};

}  // namespace ximu
#endif  // INCLUDE_XIMUAPI_SERIALIZATION_WRITER_BASE_H_
