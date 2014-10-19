#include <iostream>
#include <vector>

/*
  Copyright 2014 Auke-Dirk Pietersma
*/


#include "ximuapi/packet/packet_encoding.h"

// Example/Test the encoding and decoding of data packets
int main(int argc, char* argv[]) {
  // Assume that we have the following (decoded)data packet
  std::vector<unsigned char> decoded {2, 4, 8, 16, 32, 64, 128};
  // this corresponds to:
  std::vector<unsigned char> encoded {1, 1, 1, 1, 1, 1, 1, 128};
  // x-imu encoded packet --yes the decoded packet numbers where chosen to
  // illustrate the single bit shift

  // the ximu decoding and encoding has an effect on the packet size
  // to get the encoded size you pass the size of a decoded packet to
  // encodedPacketSize, and ofcourse visa versa
  unsigned es = ximu::PacketEncoding::encodedPacketSize(decoded.size());
  unsigned ds = ximu::PacketEncoding::decodedPacketSize(encoded.size());

  // perform test
  if (es != encoded.size())
    return 1;

  if (ds != decoded.size())
    return 1;

  // Test the packet encoding
  // make an output container
  std::vector<unsigned char> encTest;
  // call the encoder
  ximu::PacketEncoding::encodePacket(
      decoded.begin(), decoded.size(), back_inserter(encTest));

  // perform test
  if (encTest != encoded)
    return 1;

  // passing our encTest back into the decoder we should get the original data
  std::vector<unsigned char> decTest;
  ximu::PacketEncoding::decodePacket(
      encTest.begin(), encTest.size(), back_inserter(decTest));

  // perform test
  if (decTest != decoded)
    return 1;


  // test on invalid input
  ximu::PacketEncoding::decodePacket(
      encTest.begin(), 0 , back_inserter(decTest));

  ximu::PacketEncoding::encodePacket(
      decoded.begin(), 0, back_inserter(encTest));

  
  return 0;
}
