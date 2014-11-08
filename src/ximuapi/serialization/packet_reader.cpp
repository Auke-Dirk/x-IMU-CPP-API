/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include <vector>
#include "ximuapi/serialization/packet_reader.h"

namespace ximu {


size_t PacketReader::PacketSize(ximu::PacketHeaders header) {
  switch (header) {
    case ximu::PacketHeaders::QUATERNION_DATA: return 10;
    }

  return 0;
}

}  // namespace ximu

