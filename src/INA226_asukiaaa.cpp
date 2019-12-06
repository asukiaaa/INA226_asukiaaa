#include "INA226_asukiaaa.h"

#define INA226_ASUKIAAA_LSB_BUS   1.25
#define INA226_ASUKIAAA_LSB_POWER 25

#define INA226_ASUKIAAA_REGISTER_CONFIG  0x00
#define INA226_ASUKIAAA_REGISTER_SHUNTV  0x01
#define INA226_ASUKIAAA_REGISTER_BUSV    0x02
#define INA226_ASUKIAAA_REGISTER_POWER   0x03
#define INA226_ASUKIAAA_REGISTER_CURRENT 0x04
#define INA226_ASUKIAAA_REGISTER_CALIB   0x05
#define INA226_ASUKIAAA_REGISTER_MASK    0x06
#define INA226_ASUKIAAA_REGISTER_ALERTL  0x07
#define INA226_ASUKIAAA_REGISTER_DIE_ID  0xff

INA226_asukiaaa::INA226_asukiaaa(int address, uint16_t calib, uint16_t config) {
  this->address = address;
  this->calib = calib;
  this->config = config;
  wire = nullptr;
}

void INA226_asukiaaa::setWire(TwoWire* wire) {
  this->wire = wire;
}

uint16_t INA226_asukiaaa::calcCalibByResisterMilliOhm(uint16_t resisterMilliOhm) {
  return calcCalibByResisterMicroOhm((uint32_t) resisterMilliOhm * 1000);
}

uint16_t INA226_asukiaaa::calcCalibByResisterMicroOhm(uint32_t resisterMilliOhm) {
  return (uint32_t) 5120 * 1000 / resisterMilliOhm;
}

int INA226_asukiaaa::begin() {
  if (wire == nullptr) {
    wire = &Wire;
    wire->begin();
    delay(10);
  }
  int result = write(INA226_ASUKIAAA_REGISTER_CONFIG, config);
  if (result != 0) return result;
  return write(INA226_ASUKIAAA_REGISTER_CALIB, calib);
}

int INA226_asukiaaa::readMV(int16_t* volt) {
  uint16_t busVoltage;
  int result = read(INA226_ASUKIAAA_REGISTER_BUSV, (uint16_t*) &busVoltage);
  if (result != 0) return result;
  *volt = busVoltage * INA226_ASUKIAAA_LSB_BUS;
  return 0;
}

int INA226_asukiaaa::readV(float* volt) {
  int16_t mv;
  int result = readMV(&mv);
  if (result != 0) return result;
  *volt = (float) mv / 1000;
  return 0;
}

int INA226_asukiaaa::readMA(int16_t* current) {
  return read(INA226_ASUKIAAA_REGISTER_CURRENT, (uint16_t*) current);
}

int INA226_asukiaaa::readA(float* current) {
  int16_t ma;
  int result = readMA(&ma);
  if (result != 0) return result;
  *current = (float) ma / 1000;
  return 0;
}

int INA226_asukiaaa::readMW(int16_t* watt) {
  uint16_t powerVoltage;
  int result = read(INA226_ASUKIAAA_REGISTER_POWER, (uint16_t*) &powerVoltage);
  if (result != 0) return result;
  *watt = powerVoltage * INA226_ASUKIAAA_LSB_POWER;
  return 0;
}

int INA226_asukiaaa::readW(float* watt) {
  int16_t mw;
  int result = readMW(&mw);
  if (result != 0) return result;
  *watt = (float) mw / 1000;
  return 0;
}

int INA226_asukiaaa::write(uint8_t reg, uint16_t val) {
  wire->beginTransmission(address);
  wire->write(reg);
  wire->write(val >> 8);
  wire->write(val & 0xff);
  return wire->endTransmission();
}

int INA226_asukiaaa::read(uint8_t reg, uint16_t* val) {
  uint16_t ret = 0;
  // request the registor
  wire->beginTransmission(address);
  wire->write(reg);
  int result = wire->endTransmission();
  if (result != 0) return result;

  // read
  wire->requestFrom(address, 2);

  while (wire->available()) {
    ret = (ret << 8) | wire->read();
  }

  *val = ret;
  return 0;
}
