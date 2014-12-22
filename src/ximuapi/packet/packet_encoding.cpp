/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include <vector>
#include "ximuapi/packet/packet_encoding.h"

namespace ximu {

unsigned PacketEncoding::decodedPacketSize(unsigned encodedPacketSize) {
  float len = (static_cast<float>(encodedPacketSize) - 0.125f)  / 1.125f;
  return  std::floor(len);
}

unsigned PacketEncoding::encodedPacketSize(unsigned decodedPacketSize) {
  float len = static_cast<float>(decodedPacketSize) * 1.125f + 0.125f;
  return std::ceil(len);
}

void PacketEncoding::rightShiftBytes(std::vector<unsigned char>& v) {
  size_t size = v.size();
  v[size - 1] >>= 1;

  for (int idx = size - 2; idx >= 0; --idx) {
    if ((v[idx] & 0x01) == 0x01)
      v[idx + 1] |= 0x80;
    v[idx] >>= 1;
  }
}

void PacketEncoding::leftShiftBytes(std::vector<unsigned char>& v) {
  v.front() <<= 1;

  for (auto byteIt = v.begin() + 1; byteIt != v.end(); ++byteIt) {
    if ((*byteIt & 0x80) == 0x80)
      *(byteIt - 1) |= 0x01;
    *byteIt <<= 1;
  }
}

}  // namespace ximu
