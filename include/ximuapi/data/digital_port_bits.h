/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_DIGITAL_PORT_BITS_H_
#define INCLUDE_XIMUAPI_DATA_DIGITAL_PORT_BITS_H_
#include <string>

namespace ximu {
// <summary>
// Port Data class
// </summary>
class DigitalPortBits {
 private:
  unsigned char _data;

 public:
  // <summary>
  // Constrcutors
  // </summary>
  DigitalPortBits();
  explicit DigitalPortBits(unsigned char data);
  DigitalPortBits(bool ax0, bool ax1, bool ax2, bool ax3,
                  bool ax4, bool ax5, bool ax6, bool ax7);
  DigitalPortBits(const DigitalPortBits& other);
  // <summary>
  // returns the port bits as a byte
  // </summary>
  unsigned char byte() const;

  // <summary>
  // Enable/Disable the port where lsb equals index 0
  // </summary>
  void set(bool active, size_t portIndex);

  // <summary>
  // Gets the state of the specific port
  // </summary>
  bool get(size_t portIndex) const;

  // <summary>
  // Get/Set the AX0 channel. lsb of 8-bit port
  // </summary>
  bool ax0() const;
  void ax0(bool active);

  // <summary>
  // Get/Set the AX1 channel. lsb of 8-bit port
  // </summary>
  bool ax1() const;
  void ax1(bool active);

  // <summary>
  // Get/Set the AX2 channel. lsb of 8-bit port
  // </summary>
  bool ax2() const;
  void ax2(bool active);

  // <summary>
  // Get/Set the AX3 channel. lsb of 8-bit port
  // </summary>
  bool ax3() const;
  void ax3(bool active);

  // <summary>
  // Get/Set the AX4 channel. lsb of 8-bit port
  // </summary>
  bool ax4() const;
  void ax4(bool active);

  // <summary>
  // Get/Set the AX6 channel. lsb of 8-bit port
  // </summary>
  bool ax5() const;
  void ax5(bool active);

  // <summary>
  // Get/Set the AX6 channel. lsb of 8-bit port
  // </summary>
  bool ax6() const;
  void ax6(bool active);

  // <summary>
  // Get/Set the AX7 channel. lsb of 8-bit port
  // </summary>
  bool ax7() const;
  void ax7(bool active);
};

// quality test
inline bool operator==(const DigitalPortBits& lhs,
                       const DigitalPortBits& rhs) {
  return lhs.byte() == rhs.byte();
}
  // test for inequality
inline bool operator!=(const DigitalPortBits& lhs,
                       const DigitalPortBits & rhs) {
  return lhs.byte() != rhs.byte();
}

}  // namespace ximu

#endif  // INCLUDE_XIMUAPI_DATA_DIGITAL_PORT_BITS_H_
