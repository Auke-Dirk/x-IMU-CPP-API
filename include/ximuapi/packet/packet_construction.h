/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_PACKET_PACKET_CONSTRUCTION_H_
#define INCLUDE_XIMUAPI_PACKET_PACKET_CONSTRUCTION_H_

#include <vector>
#include <cmath>
#include <numeric>

#include "ximuapi/enumerations.h"
#include "ximuapi/packet/packet_encoding.h"


namespace ximu {

// <summary>
// Packet construction class. Contains static methods for packet
// construction and deconstruction.
// </summary>

class PacketConstruction {
public:
// <summary>
// Constructs an encoded command packet.
// </summary>
template<typename OutputIterator>
static void constructCommandPacket(CommandCodes commandCode,
                                     OutputIterator dest) {
  std::vector<unsigned char> decoded = {
(unsigned char)PacketHeaders::COMMAND,
      (unsigned char)((ushort)commandCode >> 8),
      (unsigned char)commandCode,
    0 };

  decoded.back() = checksum(decoded.begin(), decoded.size() - 1);
}

// <summary>
// Returns the checksum, the sum all of bytes.
// </summary>
template<typename InputIterator>
static unsigned char  checksum(InputIterator src, size_t length) {
  if (length < 0)
    return 0;
  return std::accumulate(src, src + length, (unsigned char)0);
}
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_PACKET_PACKET_CONSTRUCTION_H_
