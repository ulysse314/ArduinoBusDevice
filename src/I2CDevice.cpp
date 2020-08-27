#include "I2CDevice.h"

#define PRINT_DATA 0

#if PRINT_DATA
namespace {

void printOneByte(uint8_t byte) {
  if (byte < 0x10) {
    Serial.print("0");
  }
  Serial.print(byte, HEX);
}

}  // namespace
#endif  // PRINT_DATA

I2CDevice::I2CDevice(uint8_t address, TwoWire *wire, BusDevice::Endianness endianness) :
    BusDevice(endianness),
    _address(address),
    _wire(wire) {
}

I2CDevice::~I2CDevice() {
}

size_t I2CDevice::readBuffer(uint8_t *values, size_t size, bool endTransmission) {
  if (!values || !_wire) {
#if PRINT_DATA
    Serial.println("No data or no wire to read");
#endif
    return -1;
  }
  uint8_t readCount = _wire->requestFrom(_address, size, endTransmission);
#if PRINT_DATA
  Serial.print("Read from 0x");
  printOneByte(_address);
  Serial.print(", ");
  Serial.print(size);
  Serial.print(" data to read, ");
  Serial.print(readCount);
  Serial.print(", end: ");
  Serial.print(endTransmission ? "true" : "false");
  Serial.print(", received: ");
#endif
  for (uint8_t ii = 0; ii < readCount; ++ii) {
    values[ii] = _wire->read();
#if PRINT_DATA
    printOneByte(values[ii]);
#endif
  }
#if PRINT_DATA
  Serial.println(" ");
#endif
  return readCount;
}

size_t I2CDevice::writeBuffer(const uint8_t *values, size_t size, bool endTransmission) {
  if (!values || !_wire) {
#if PRINT_DATA
    Serial.println("No data or no wire to write");
#endif
    return -1;
  }
  _wire->beginTransmission(_address);
  size_t writeCount = _wire->write(values, size);
#if PRINT_DATA
  Serial.print("Write to 0x");
  printOneByte(_address);
  Serial.print(", ");
  Serial.print(size);
  Serial.print(" data to write, ");
  Serial.print(writeCount);
  Serial.print(", end: ");
  Serial.print(endTransmission ? "true" : "false");
#endif
  bool noError (_wire->endTransmission(endTransmission) == 0);
#if PRINT_DATA
  Serial.print(", no error: ");
  Serial.print(noError ? "true" : "false");
  Serial.print(", sent: ");
  for (size_t ii = 0; ii < size; ++ii) {
    printOneByte(values[ii]);
  }
  Serial.println(" ");
#endif
  return noError ? writeCount : -1;
}

size_t I2CDevice::writeBufferToRegister(const uint8_t *values, size_t size, uint8_t registerValue) {
  if (!values || !_wire) {
#if PRINT_DATA
    Serial.println("No data or no wire to write");
#endif
    return -1;
  }
  _wire->beginTransmission(_address);
  if (_wire->write(registerValue) != sizeof(registerValue)) {
    _wire->endTransmission();
    return -1;
  }
  size_t writeCount = _wire->write(values, size);
#if PRINT_DATA
  Serial.print("Write to 0x");
  printOneByte(_address);
  Serial.print(", to register: 0x");
  Serial.print(registerValue, HEX);
  Serial.print(", size: ");
  Serial.print(size);
  Serial.print(", written: ");
  Serial.print(writeCount);
#endif
  bool noError = (_wire->endTransmission() == 0);
#if PRINT_DATA
  Serial.print(", no error: ");
  Serial.print(noError ? "true" : "false");
  Serial.print(", sent: ");
  for (size_t ii = 0; ii < size; ++ii) {
    printOneByte(values[ii]);
  }
  Serial.println(" ");
#endif
  return noError ? writeCount : -1;
}
