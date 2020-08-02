#ifndef HARDWARESERIALDEVICE_H
#define HARDWARESERIALDEVICE_H

#include "SerialDevice.h"

#include <Arduino.h>

class HardwareSerialDevice : public BusDevice {
public:
  SerialDevice(HardwareSerial *serial);
  ~SerialDevice();

  size_t readBuffer(uint8_t *values, size_t size, bool endTransmission = true) override;
  size_t writeBuffer(uint8_t *values, size_t size, bool endTransmission = true) override;

protected:
  HardwareSerial *_serial;
};

#endif  // HARDWARESERIALDEVICE_H
