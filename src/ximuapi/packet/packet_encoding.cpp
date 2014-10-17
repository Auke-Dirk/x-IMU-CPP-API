/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include "../../../include/ximuapi/packet/packet_encoding.h"

#include <vector>

namespace ximu {

void PacketEncoding::rightShiftBytes(const std::vector<unsigned char>& v) {
  size_t size = v.size();
  v[size - 1] >>= 1;

  for (int idx = size - 2; idx >= 0; --idx) {
    if ((v[idx] & 0x01) == 0x01)
      v[idx + 1] |= 0x80;
    v[idx] >>= 1;
  }
}

}  // namespace ximu
