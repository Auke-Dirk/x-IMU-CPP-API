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
// Constructs an encoded command packet
// </summary>
template<typename OutputIterator>
static void constructCommandPacket(CommandCodes commandCode,
                                     OutputIterator dest) {
  std::vector<unsigned char> decoded = {
    static_cast<unsigned char>(PacketHeaders::COMMAND),
    static_cast<unsigned char>(static_cast<unsigned short>(commandCode) >> 8),
    static_cast<unsigned char>(commandCode),
    0 };

  decoded.back() = checksum(decoded.begin(), decoded.size() - 1);
  
  PacketEncoding::encodePacket(decoded.begin(),decoded.end(), dest);
}

// <summary>
// Returns the checksum, the sum all of bytes.
// </summary>
template<typename InputIterator>
static unsigned char checksum(InputIterator begin, InputIterator end) {
  return std::accumulate(begin, end, (unsigned char)0);
}

template<typename InputIterator>
static unsigned char  checksum(InputIterator src, size_t length) {
  if (length < 0)
    return 0;
  return std::accumulate(src, src + length, (unsigned char)0);
}
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_PACKET_PACKET_CONSTRUCTION_H_
