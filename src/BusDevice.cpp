#include "BusDevice.h"

BusDevice::BusDevice() {
}

BusDevice::~BusDevice() {
}

size_t BusDevice::read8FromRegister(uint8_t *value, uint8_t registerValue) {
  if (!writeBuffer(&registerValue, sizeof(registerValue), false)) {
    return -1;
  }
  return readBuffer(value, sizeof(value));
}

size_t BusDevice::read16FromRegister(uint16_t *value, uint8_t registerValue) {
  if (!writeBuffer(&registerValue, sizeof(registerValue), false)) {
    return -1;
  }
  return readBuffer(value, sizeof(value));
}

size_t BusDevice::write8FromRegister(uint8_t value, uint8_t registerValue) {
  if (!writeBuffer(&registerValue, sizeof(registerValue), false)) {
    return -1;
  }
  return writeBuffer(value, sizeof(value));
}

size_t I2CDevice::write16FromRegister(uint16_t value, uint8_t registerValue) {
  if (!writeBuffer(&registerValue, sizeof(registerValue), false)) {
    return -1;
  }
  return writeBuffer(value, sizeof(value));
}
