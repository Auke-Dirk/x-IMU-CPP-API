/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#ifndef INCLUDE_XIMUAPI_DATA_REGISTER_DATA_H_
#define INCLUDE_XIMUAPI_DATA_REGISTER_DATA_H_

#include "ximuapi/enumerations.h"

namespace ximu {

// Register Data class
class RegisterData {
 public:
// Constructors
  RegisterData();
  explicit RegisterData(reg::RegisterAddresses address);
  RegisterData(reg::RegisterAddresses address, float value);
  RegisterData(reg::RegisterAddresses address, unsigned short value);
  RegisterData(unsigned short address, unsigned short value);

  // <summary>
  // Gets or sets the register address.
  // </summary>
  reg::RegisterAddresses address();
  void address(reg::RegisterAddresses address);

  // <summary>
  // Gets or sets 16-bit register value.
  // </summary>
  unsigned short value();
  void value(unsigned short value);

  // <summary>
  // Converts 16-bit register value to float using fixed-point
  // precision defined in ximu::Qvals.
  // </summary>
  float floatValue();

  // <summary>
  // Sets 16-bit register value from float interpreted using fixed-point
  // precision defined in ximu::Qvals
  /// </summary>
  void floatValue(float value);

 private:
  // the register
  reg::RegisterAddresses _address;

  // the register's valuea
  unsigned short _value;

  // <summary>
  // Returns ximu::Qvals associated with register address.
  // </summary>
  Qvals LookupQval();
};

};  // namespace ximu

#endif  // INCLUDE_XIMUAPI_DATA_REGISTER_DATA_H_
