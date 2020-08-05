#include "BusDevice.h"

namespace {

inline bool inverseBufferWithEndianness(BusDevice::Endianness endianness) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  return endianness == BusDevice::Endianness::Big;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  return endianness == BusDevice::Endianness::Little;
#else
  #error No endianness defined
  return false;
#endif
}

inline uint16_t inversUInt16IfNeeded(uint16_t value, BusDevice::Endianness endianness) {
  if (!inverseBufferWithEndianness(endianness)) {
    return value;
  }
  return ((uint16_t)((value & 0xFF) << 8)) | (uint16_t)((value & 0xFF00) >> 8);
}

void inverseUInt16ArrayIfNeeded(uint16_t *array, size_t size, BusDevice::Endianness endianness) {
  if (inverseBufferWithEndianness(endianness)) {
    for (size_t ii = 0; ii < size; ++ii) {
      array[ii] = inversUInt16IfNeeded(array[ii], endianness);
    }
  }
}

}  // namespace

BusDevice::BusDevice(Endianness endianness) :
    _endianness(endianness) {
}

BusDevice::~BusDevice() {
}

size_t BusDevice::read8FromRegister(uint8_t *value, uint8_t registerValue) {
  if (!value) {
    return 0;
  }
  if (writeBuffer(&registerValue, sizeof(registerValue), false) != sizeof(registerValue)) {
    return -1;
  }
  return readBuffer(value, sizeof(*value));
}

size_t BusDevice::read16FromRegister(uint16_t *value, uint8_t registerValue) {
  return readArray16FromRegister(value, 1, registerValue);
}

size_t BusDevice::readArray16FromRegister(uint16_t *values, size_t size, uint8_t registerValue) {
  if (!values) {
    return 0;
  }
  if (writeBuffer(&registerValue, sizeof(registerValue), false) != sizeof(registerValue)) {
    return -1;
  }
  size_t bufferSize = size * sizeof(*values);
  size_t readCount = readBuffer((uint8_t *)values, bufferSize);
  inverseUInt16ArrayIfNeeded(values, bufferSize, _endianness);
  return readCount;
}

size_t BusDevice::readBufferFromRegister(uint8_t *value, size_t size, uint8_t registerValue) {
  if (!value) {
    return 0;
  }
  if (writeBuffer(&registerValue, sizeof(registerValue), false) != sizeof(registerValue)) {
    return -1;
  }
  return readBuffer(value, size);
}

size_t BusDevice::write8ToRegister(uint8_t value, uint8_t registerValue) {
  if (!value) {
    return 0;
  }
  if (writeBuffer(&registerValue, sizeof(registerValue), false) != sizeof(registerValue)) {
    return -1;
  }
  return writeBuffer(&value, sizeof(value));
}

size_t BusDevice::write16ToRegister(uint16_t value, uint8_t registerValue) {
  return writeArray16ToRegister(&value, 1, registerValue);
}

size_t BusDevice::writeArray16ToRegister(uint16_t *values, size_t size, uint8_t registerValue) {
  if (!values) {
    return 0;
  }
  if (writeBuffer(&registerValue, sizeof(registerValue), false) != sizeof(registerValue)) {
    return -1;
  }
  size_t bufferSize = size * sizeof(*values);
  uint16_t *buffer = (uint16_t *)malloc(bufferSize);
  memcpy(buffer, values, bufferSize);
  inverseUInt16ArrayIfNeeded(buffer, size, _endianness);
  size_t writeCount = writeBuffer((uint8_t *)buffer, bufferSize);
  free(buffer);
  return writeCount;
}

size_t BusDevice::read8(uint8_t *value, bool endTransmission) {
  return readBuffer(value, sizeof(*value), endTransmission);
}

size_t BusDevice::read16(uint16_t *value, bool endTransmission) {
  if (!value) {
    return 0;
  }
  size_t readCount = readBuffer((uint8_t *)&value, sizeof(value), endTransmission);
  *value = inversUInt16IfNeeded(*value, _endianness);
  return readCount;
}

size_t BusDevice::write8(uint8_t value, bool endTransmission) {
  return writeBuffer(&value, sizeof(value), endTransmission);
}

size_t BusDevice::write16(uint16_t value, bool endTransmission) {
  __typeof__(value) endianValue = inversUInt16IfNeeded(value, _endianness);
  return writeBuffer((uint8_t *)&endianValue, sizeof(endianValue), endTransmission);
}
