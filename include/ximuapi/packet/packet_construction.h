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
#include "ximuapi/data/register_data.h"
#include "ximuapi/data/datetime_data.h"
#include "ximuapi/data/digital_io_data.h"

namespace ximu {

// <summary>
// Packet construction class. Contains static methods for packet
// construction.
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
  PacketEncoding::encodePacket(decoded.begin(), decoded.end(), dest);
}

// <summary>
// Constructs a read register packet.
// </summary>
template<typename OutputIterator>
static void constructReadRegisterPacket(const RegisterData &data,
                                        OutputIterator dest) {
  std::vector<unsigned char> decoded = {
    static_cast<unsigned char>(PacketHeaders::READ_REGISTER),
    static_cast<unsigned char>(static_cast<unsigned short>(
        data.address()) >> 8),
    static_cast<unsigned char>(data.address()),
    0 };

  decoded.back() = checksum(decoded.begin(), decoded.size() - 1);
  PacketEncoding::encodePacket(decoded.begin(), decoded.end(), dest);
}

// <summary>
// Constructs a write register packet.
// </summary>
template<typename OutputIterator>
static void constructWriteRegisterPacket(const RegisterData &data,
                                         OutputIterator dest) {
  std::vector<unsigned char> decoded = {
    static_cast<unsigned char>(PacketHeaders::WRITE_REGISTER),
    static_cast<unsigned char>(static_cast<unsigned short>(
        data.address()) >> 8),
    static_cast<unsigned char>(data.address()),
    static_cast<unsigned char>(data.value() >> 8),
    static_cast<unsigned char>(data.value()),
    0 };

  decoded.back() = checksum(decoded.begin(), decoded.size() - 1);
  PacketEncoding::encodePacket(decoded.begin(), decoded.end(), dest);
}

//  <summary>
//  Constructs a write date/time packet.
//  </summary>
template<typename OutputIterator>
static void constructWriteDateTimePacket(const DateTimeData& data,
                                         OutputIterator dest) {
  std::vector<unsigned char> decoded = {
    static_cast<unsigned char>(PacketHeaders::WRITE_DATETIME),
    static_cast<unsigned char>((((((data.year() - 2000) % 100) / 10) << 4)
      | (data.year() - 2000) % 10)),
    static_cast<unsigned char>(((((data.month() % 100) / 10) << 4)
      | (data.month() % 10))),
    static_cast<unsigned char>(((((data.day() % 100) / 10) << 4)	
      | (data.day() % 10))),
    static_cast<unsigned char>(((((data.hours() % 100) / 10) << 4)
      | (data.hours() % 10))),
    static_cast<unsigned char>(((((data.minutes() % 100) / 10) << 4)
      | (data.minutes() % 10))),
     static_cast<unsigned char>(((((data.seconds() % 100) / 10) << 4)
      | (data.seconds() % 10))),
      0
  };
  decoded.back() = checksum(decoded.begin(), decoded.size() - 1);
  PacketEncoding::encodePacket(decoded.begin(), decoded.end(), dest);
}

//  <summary>
//  Constructs a read date/time packet.
//  </summary>
template<typename OutputIterator>
static void constructReadDateTimePacket(OutputIterator dest) {
  std::vector<unsigned char> decoded = {
    static_cast<unsigned char>(PacketHeaders::READ_DATETIME),
    0 };

  decoded.back() = checksum(decoded.begin(), decoded.size() - 1);
  PacketEncoding::encodePacket(decoded.begin(), decoded.end(), dest);
}

// <summary
// Constructs an encoded digital I/O packet.
// </summary>
template<typename OutputIterator>
static void constructDigitalIOPacket(
  const DigitalIOData& diod,
  OutputIterator dest) {
  std::vector<unsigned char> decoded = {
    static_cast<unsigned char>(PacketHeaders::DIGITAL_IO_DATA),
    0x00, 
    diod.state().byte(),
    0
  };
  decoded.back() = checksum(decoded.begin(), decoded.size() - 1);
  PacketEncoding::encodePacket(decoded.begin(), decoded.end(), dest);
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
