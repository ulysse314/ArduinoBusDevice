#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include "BusDevice.h"

#include <Wire.h>

class I2CDevice : public BusDevice {

public:
  I2CDevice(uint8_t address, TwoWire *wire = &Wire, BusDevice::Endianness endianness = BusDevice::Endianness::Little);
  ~I2CDevice();

  size_t readBuffer(uint8_t *values, size_t size, bool endTransmission = true) override __attribute__((warn_unused_result));
  size_t writeBuffer(const uint8_t *values, size_t size, bool endTransmission = true) override __attribute__((warn_unused_result));
  size_t writeBufferToRegister(const uint8_t *values, size_t size, uint8_t registerValue) __attribute__((warn_unused_result));

  TwoWire *getWire() { return _wire; };

protected:
  uint8_t _address;
  TwoWire *_wire;
};

#endif  // I2CDEVICE_H
