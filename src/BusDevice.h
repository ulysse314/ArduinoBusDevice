#ifndef BUSDEVICE_H
#define BUSDEVICE_H

class BusDevice {
public:
  BusDevice();
  ~BusDevice();

  // Returns -1 if error, otherwise returns the number of byte read.
  size_t read8FromRegister(uint8_t *value, uint8_t registerValue) __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of byte read.
  size_t read16FromRegister(uint16_t *value, uint8_t registerValue) __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of byte written.
  size_t write8FromRegister(uint8_t value, uint8_t registerValue) __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of byte written.
  size_t write16FromRegister(uint16_t value, uint8_t registerValue) __attribute__((warn_unused_result));

  // Returns -1 if error, otherwise returns the number of byte read.
  virtual size_t readBuffer(uint8_t *values, size_t size, bool endTransmission = true) = 0 __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of byte written.
  virtual size_t writeBuffer(uint8_t *values, size_t size, bool endTransmission = true) = 0 __attribute__((warn_unused_result))s;
};

#endif  // BUSDEVICE_H
