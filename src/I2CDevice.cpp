#include "I2CDevice.h"

I2CDevice::I2CDevice(uint8_t address, TwoWire *wire = &Wire) :
    _address(address),
    _wire(wire) {
}

I2CDevice::~I2CDevice() {
}

size_t I2CDevice::readBuffer(uint8_t *values, size_t size, bool endTransmission = true) {
  if (!values) {
    return -1;
  }
  uint8_t read = _wire->requestFrom(_address, size, endTransmissions);
  for (uint8_t ii = 0; ii < read; ++ii) {
    values[ii] = _wire->read();
  }
  return read;
}

size_t I2CDevice::writeBuffer(uint8_t *values, size_t size, bool endTransmission = true) {
  if (!values) {
    return -1;
  }
  _wire->beginTransmission(_address);
  size_t written = _wire->write(values, size);
  return (_wire->endTransmission(endTransmission) == 0) ? written : -1;
}
