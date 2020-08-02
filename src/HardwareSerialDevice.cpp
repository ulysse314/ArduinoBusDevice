#include "HardwareSerialDevice.h"

HardwareSerialDevice::HardwareSerialDevice(HardwareSerial *serial) :
    _serial(serial) {
}

HardwareSerialDevice::~HardwareSerialDevice() {
}

size_t HardwareSerialDevice::readBuffer(uint8_t *values, size_t size, bool endTransmission = true) {
  if (!values) {
    return -1;
  }
  size_t readCounter = 0;
  while (_stream->available() > 0) {
    values[readCounter] = _stream->read();
    ++readCounter;
  }
  return readCounter;
}

size_t HardwareSerialDevice::writeBuffer(uint8_t *values, size_t size, bool endTransmission = true) {
  if (!values) {
    return -1;
  }
  size_t writeCounter = 0;
  while (_stream->availableForWrite() > 0) {
    _stream->write(values[writeCounter]);
    ++writeCounter;
  }
  return writeCounter;
}
