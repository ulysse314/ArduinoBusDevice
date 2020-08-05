#ifndef SERIALDEVICE_H
#define SERIALDEVICE_H

#include "BusDevice.h"

#include <Arduino.h>

class SerialDevice : public BusDevice {
public:
  SerialDevice(Stream *stream, BusDevice::Endianness endianness = BusDevice::Endianness::Little);
  ~SerialDevice();

  virtual size_t readBuffer(uint8_t *values, size_t size, bool endTransmission = true) override __attribute__((warn_unused_result));
  size_t writeBuffer(const uint8_t *values, size_t size, bool endTransmission = true) override __attribute__((warn_unused_result));

protected:
  Stream *_stream;
};

#endif  // SERIALDEVICE_H
