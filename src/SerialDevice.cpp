#include "SerialDevice.h"

SerialDevice::SerialDevice(Stream *stream, BusDevice::Endianness endianness) :
    BusDevice(endianness),
    _stream(stream) {
}

SerialDevice::~SerialDevice() {
}

size_t SerialDevice::readBuffer(uint8_t *values, size_t size, bool endTransmission) {
  if (!values || !_stream) {
    return -1;
  }
  size_t readCounter = 0;
  while (_stream->available() > 0) {
    values[readCounter] = _stream->read();
    ++readCounter;
  }
  return readCounter;
}

size_t SerialDevice::writeBuffer(const uint8_t *values, size_t size, bool endTransmission) {
  if (!values || !_stream) {
    return -1;
  }
  return _stream->write(values, size);
}
