#ifndef _INA226_ASUKIAAA_H_
#define _INA226_ASUKIAAA_H_
#include <Arduino.h>
#include <Wire.h>

#define INA226_ASUKIAAA_DEFAULT_CONFIG 0x4127

class INA226_asukiaaa {
 public:
  INA226_asukiaaa(int address, uint16_t calib, uint16_t config = INA226_ASUKIAAA_DEFAULT_CONFIG);
  // calib is used to calculate current value.
  // define your calib by referencing shunt resister.
  // calib = 5120 / R(mOhm)
  // Ex: 0.002 Ohm -> 2 mOhm -> calib = 5120 / 2 = 2560
  void setWire(TwoWire* wire);
  static uint16_t calcCalibByResisterMilliOhm(uint16_t resisterMilliOhm); // MAX 5120 mOhm

  int begin();

  int readMV(int16_t* volt);
  int readMA(int16_t* current);
  int readMW(int16_t* watt);

 private:
  int address;
  uint16_t config;
  uint16_t calib;
  int write(uint8_t reg, uint16_t val);
  int read(uint8_t reg, uint16_t* val);
  TwoWire* wire;
};

#endif
