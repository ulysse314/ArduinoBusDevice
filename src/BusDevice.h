#ifndef BUSDEVICE_H
#define BUSDEVICE_H

#include <Arduino.h>

class BusDevice {
public:
  enum class Endianness {
    Little,
    Big,
  };

  BusDevice(Endianness endianness);
  ~BusDevice();

  // Returns -1 if error, otherwise returns the number of read byte.
  size_t read8FromRegister(uint8_t *value, uint8_t registerValue) __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of read byte.
  size_t read16FromRegister(uint16_t *value, uint8_t registerValue) __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of read byte.
  size_t readArray16FromRegister(uint16_t *values, size_t size, uint8_t registerValue) __attribute__((warn_unused_result));

  // Returns -1 if error, otherwise returns the number of written byte.
  size_t write8ToRegister(uint8_t value, uint8_t registerValue) __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of written byte.
  size_t write16ToRegister(uint16_t value, uint8_t registerValue) __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of written byte.
  size_t writeArray16ToRegister(uint16_t *values, size_t size, uint8_t registerValue) __attribute__((warn_unused_result));

  // Returns -1 if error, otherwise returns the number of read byte.
  size_t read8(uint8_t *value, bool endTransmission = true) __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of read byte.
  size_t read16(uint16_t *value, bool endTransmission = true) __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of written byte.
  size_t write8(uint8_t value, bool endTransmission = true) __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of written byte.
  size_t write16(uint16_t value, bool endTransmission = true) __attribute__((warn_unused_result));

  // Returns -1 if error, otherwise returns the number of read byte.
  virtual size_t readBuffer(uint8_t *values, size_t size, bool endTransmission = true) __attribute__((warn_unused_result)) = 0;
  // Returns -1 if error, otherwise returns the number of written byte.
  virtual size_t writeBuffer(const uint8_t *values, size_t size, bool endTransmission = true) __attribute__((warn_unused_result)) = 0;
  // Returns -1 if error, otherwise returns the number of read byte.
  virtual size_t readBufferFromRegister(uint8_t *value, size_t size, uint8_t registerValue) __attribute__((warn_unused_result));
  // Returns -1 if error, otherwise returns the number of written byte.
  virtual size_t writeBufferToRegister(const uint8_t *values, size_t size, uint8_t registerValue) = 0;

protected:
  Endianness _endianness;
};

#endif  // BUSDEVICE_H
