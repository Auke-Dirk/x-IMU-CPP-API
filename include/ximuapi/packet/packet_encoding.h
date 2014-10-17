/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_PACKET_PACKET_ENCODING_H_
#define INCLUDE_XIMUAPI_PACKET_PACKET_ENCODING_H_

#include <vector>
#include <cmath>
#include <algorithm>

namespace ximu {

// <summary>
// Packet encoding class. Contains static methods for packet
// encoding and decoding.
// </summary>

class PacketEncoding{
 public:
  // <summary>
  // Right shifts the contents by 1 bit. The lsb of byte x becomes the msb of
  // byte x+1.
  // </summary>
  static void rightShiftBytes(const std::vector<unsigned char>& v);

    // <summary>
    // Encodes packet with consecutive right shifts so that
    // the msb of each encoded byte is clear. The msb of the
    // final byte is set to indicate the end of the packet.
    // </summary>
  template<typename InputIterator, typename OutputIterator>
    static void encodePacket(InputIterator src, size_t count,
                             OutputIterator dest){
      // calculate new message length
      float len = static_cast<float>(count) * 1.125f + 0.125f;
      unsigned encodedLength = std::ceil(len);

      std::vector<unsigned char> encodedPacket(encodedLength, 0);
      std::vector<unsigned char> shiftRegister(encodedLength, 0);

      // fill the shift register
      std::copy_n(src, count, shiftRegister.begin());

      for (unsigned idx = 0; idx != encodedLength; ++idx) {
        rightShiftBytes(shiftRegister);           // r-shift clear msb i
        encodedPacket[idx] = shiftRegister[idx];  // store encoded byte
        shiftRegister[idx] = 0;                   // clear byte from sr
      }
      // set msb of framing byte
      encodedPacket.back() |= 0x80;
      std::copy_n(encodedPacket.begin(), encodedLength, dest);
    }
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_PACKET_PACKET_ENCODING_H_
