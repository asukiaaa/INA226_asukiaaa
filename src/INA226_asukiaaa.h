#ifndef _INA226_ASUKIAAA_H_
#define _INA226_ASUKIAAA_H_
#include <Arduino.h>
#include <Wire.h>

#define INA226_ASUKIAAA_DEFAULT_CONFIG 0x4127

#define INA226_ASUKIAAA_ADDR_A0_GND_A1_GND B1000000
#define INA226_ASUKIAAA_ADDR_A0_VDD_A1_GND B1000001
#define INA226_ASUKIAAA_ADDR_A0_SDA_A1_GND B1000010
#define INA226_ASUKIAAA_ADDR_A0_SCL_A1_GND B1000011
#define INA226_ASUKIAAA_ADDR_A0_GND_A1_VDD B1000100
#define INA226_ASUKIAAA_ADDR_A0_VDD_A1_VDD B1000101
#define INA226_ASUKIAAA_ADDR_A0_SDA_A1_VDD B1000110
#define INA226_ASUKIAAA_ADDR_A0_SCL_A1_VDD B1000111
#define INA226_ASUKIAAA_ADDR_A0_GND_A1_SDA B1001000
#define INA226_ASUKIAAA_ADDR_A0_VDD_A1_SDA B1001001
#define INA226_ASUKIAAA_ADDR_A0_SDA_A1_SDA B1001010
#define INA226_ASUKIAAA_ADDR_A0_SCL_A1_SDA B1001011
#define INA226_ASUKIAAA_ADDR_A0_GND_A1_SCL B1001100
#define INA226_ASUKIAAA_ADDR_A0_VDD_A1_SCL B1001101
#define INA226_ASUKIAAA_ADDR_A0_SDA_A1_SCL B1001110
#define INA226_ASUKIAAA_ADDR_A0_SCL_A1_SCL B1001111

class INA226_asukiaaa {
 public:
  INA226_asukiaaa(int address, uint16_t calib, uint16_t config = INA226_ASUKIAAA_DEFAULT_CONFIG);
  void setWire(TwoWire* wire);
  static uint16_t calcCalibByResisterMilliOhm(uint16_t resisterMilliOhm); // MAX 5120 mOhm
  static uint16_t calcCalibByResisterMicroOhm(uint32_t resisterMicroOhm);

  int begin();

  int readMV(int16_t* volt);
  int readV(float* volt);
  int readMA(int16_t* current);
  int readA(float* current);
  int readMW(int16_t* watt);
  int readW(float* watt);

 private:
  int address;
  uint16_t config;
  uint16_t calib;
  int write(uint8_t reg, uint16_t val);
  int read(uint8_t reg, uint16_t* val);
  TwoWire* wire;
};

#endif
