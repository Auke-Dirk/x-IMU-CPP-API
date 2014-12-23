/*
  Copyright 2014 Auke-Dirk Pietersma
*/

#include "ximuapi/data/digital_port_bits.h"

namespace ximu {

// Constructors
DigitalPortBits::DigitalPortBits()
  :
  _data(0)
{}

DigitalPortBits::DigitalPortBits(unsigned char data)
  :
  _data(data)
{}

DigitalPortBits::DigitalPortBits(
  const DigitalPortBits& other) {
  _data = other.byte();
}

DigitalPortBits::DigitalPortBits(
    bool ax0, bool ax1, bool ax2, bool ax3,
    bool ax4, bool ax5, bool ax6, bool ax7) {
  set(ax0, 0);
  set(ax1, 1);
  set(ax2, 2);
  set(ax3, 3);
  set(ax4, 4);
  set(ax5, 5);
  set(ax6, 6);
  set(ax7, 7);
}

unsigned char DigitalPortBits::byte() const {
  return _data;
}

void DigitalPortBits::set(bool value, size_t portIndex) {
  if (value)
    _data |= (1 << portIndex);
  else
    _data &= ~(1 << portIndex);
}

bool DigitalPortBits::get(size_t portIndex) const {
  return _data & (1 << portIndex);
}

// ax 0
bool DigitalPortBits::ax0() const {
  return get(0);
}

void DigitalPortBits::ax0(bool active) {
  set(active, 0);
}

// ax 1
bool DigitalPortBits::ax1() const {
  return get(1);
}

void DigitalPortBits::ax1(bool active) {
  set(active, 1);
}

// ax 2
bool DigitalPortBits::ax2() const {
  return get(2);
}

void DigitalPortBits::ax2(bool active) {
  set(active, 2);
}


// ax 3
bool DigitalPortBits::ax3() const {
  return get(3);
}

void DigitalPortBits::ax3(bool active) {
  set(active, 3);
}


// ax 4
bool DigitalPortBits::ax4() const {
  return get(4);
}

void DigitalPortBits::ax4(bool active) {
  set(active, 4);
}

// ax 5
bool DigitalPortBits::ax5() const {
  return get(5);
}

void DigitalPortBits::ax5(bool active) {
  set(active, 5);
}

// ax 6
bool DigitalPortBits::ax6() const {
  return get(6);
}

void DigitalPortBits::ax6(bool active) {
  set(active, 6);
}

// ax 7
bool DigitalPortBits::ax7() const {
  return get(7);
}

void DigitalPortBits::ax7(bool active) {
  set(active, 7);
}

}  // namespace ximu
