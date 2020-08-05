#include "I2CDevice.h"

I2CDevice::I2CDevice(uint8_t address, TwoWire *wire, BusDevice::Endianness endianness) :
    BusDevice(endianness),
    _address(address),
    _wire(wire) {
}

I2CDevice::~I2CDevice() {
}

size_t I2CDevice::readBuffer(uint8_t *values, size_t size, bool endTransmission) {
  if (!values || !_wire) {
    return -1;
  }
  uint8_t read = _wire->requestFrom(_address, size, endTransmission);
  for (uint8_t ii = 0; ii < read; ++ii) {
    values[ii] = _wire->read();
  }
  return read;
}

size_t I2CDevice::writeBuffer(const uint8_t *values, size_t size, bool endTransmission) {
  if (!values || !_wire) {
    return -1;
  }
  _wire->beginTransmission(_address);
  size_t written = _wire->write(values, size);
  return (_wire->endTransmission(endTransmission) == 0) ? written : -1;
}
