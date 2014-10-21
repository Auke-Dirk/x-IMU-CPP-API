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
  // Calculates the size needed to decode a packet.
  // </summary>
  static unsigned decodedPacketSize(unsigned encodedPacketSize);

  // <summary>
  // Calculates the size needed to encode a packet.
  // </summary>
  static unsigned encodedPacketSize(unsigned decodedPacketSize);

  // <summary>
  // Left shifts the contents by 1 bit. The msb of byte
  // x becomes the lsb of byte x-1.
  // </summary>
  static void leftShiftBytes(std::vector<unsigned char>& v);

  // <summary>
  // Right shifts the contents by 1 bit. The lsb of byte x becomes the msb of
  // byte x+1.
  // </summary>
  static void rightShiftBytes(std::vector<unsigned char>& v);

  // <summary>
  // Encodes packet with consecutive right shifts so that
  // the msb of each encoded byte is clear. The msb of the
  // final byte is set to indicate the end of the packet.
  // </summary>
  template<typename InputIterator,typename OutputIterator>
  static void encodePacket(InputIterator begin, InputIterator end,
                           OutputIterator dest) {
    encodePacket(begin, std::distance(begin,end), dest);
  }
  // overload
  template<typename InputIterator, typename OutputIterator>
  static void encodePacket(InputIterator src, size_t count,
                           OutputIterator dest) {
    // need at least one byte to encode 
    if (count < 1)
      return;

    // calculate new message length
    unsigned encodedLength = encodedPacketSize(count);
    std::vector<unsigned char> encodedPacket(encodedLength, 0);
    std::vector<unsigned char> shiftRegister(encodedLength, 0);
    
    // fill the shift register
    std::copy_n(src, count, shiftRegister.begin());

    // shift
    for (unsigned idx = 0; idx != encodedLength; ++idx) {
      rightShiftBytes(shiftRegister);           // r-shift clear msb i
      encodedPacket[idx] = shiftRegister[idx];  // store encoded byte
      shiftRegister[idx] = 0;                   // clear byte from sr
    }
    // set msb of framing byte
    encodedPacket.back() |= 0x80;
    std::copy_n(encodedPacket.begin(), encodedLength, dest);
  }

  // <summary>
  // Decodes a packet with consecutive left shifts so that the msb of
  //  each encoded byte is removed.
  // </summary>
  template<typename InputIterator,typename OutputIterator>
  static void decodePacket(InputIterator begin, InputIterator end,
                           OutputIterator dest) {
    decodePacket(begin, std::distance(begin,end), dest);
  }
  // overload
  template<typename InputIterator, typename OutputIterator>
  static void decodePacket(InputIterator src, size_t count,
                             OutputIterator dest) {
    // need at least one byte to decode to a one byte packet
    if (count < 2)
      return;

    // calculate new message length
    unsigned decodedLength = decodedPacketSize(count);

    std::vector<unsigned char> shiftRegister(count, 0);

    // shift do,while
    auto byteIt = src + count;
    do {
      --byteIt;
      shiftRegister[byteIt - src] = *byteIt;
      leftShiftBytes(shiftRegister);
    } while (byteIt != src);

    std::copy_n(shiftRegister.begin(), decodedLength, dest);
  }
};

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_PACKET_PACKET_ENCODING_H_
