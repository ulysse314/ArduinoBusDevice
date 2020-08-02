#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include "BusDevice.h"

#include <Wire.h>

class I2CDevice : public BusDevice {
public:
  I2CDevice(uint8_t address, TwoWire *wire = &Wire);
  ~I2CDevice();

  size_t readBuffer(uint8_t *values, size_t size, bool endTransmission = true) override;
  size_t writeBuffer(uint8_t *values, size_t size, bool endTransmission = true) override;

protected:
  uint8_t _address;
  TwoWire *_wire;

};

#endif  // I2CDEVICE_H
