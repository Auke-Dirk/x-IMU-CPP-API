/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include <vector>
#include "ximuapi/serialization/packet_reader.h"

namespace ximu {


size_t PacketReader::PacketSize(ximu::PacketHeaders header) {
  switch (header) {
    case ximu::PacketHeaders::QUATERNION_DATA:
      return 10;
    case ximu::PacketHeaders::CAL_INERTIAL_AND_MAGNETIC_DATA:
      return 20;
    }

  return 0;
}

}  // namespace ximu

