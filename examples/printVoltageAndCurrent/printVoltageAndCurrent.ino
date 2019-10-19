#include <INA226_asukiaaa.h>

const uint16_t calib = INA226_asukiaaa::calcCalibByResisterMilliOhm(2); // Max 5120 milli ohm
// const uint16_t calib = INA226_asukiaaa::calcCalibByResisterMicroOhm(2000);
INA226_asukiaaa voltCurrMeter(INA226_ASUKIAAA_ADDR_A0_GND_A1_GND, calib);

void setup() {
  Serial.begin(115200);
  if (voltCurrMeter.begin() != 0) {
    Serial.println("Failed to begin INA226");
  }
}

void loop() {
  int16_t ma, mv;
  if (voltCurrMeter.readMV(&mv) == 0) {
    Serial.println(String(mv) + "mV");
  } else {
    Serial.println("Cannot read voltage.");
  }
  if (voltCurrMeter.readMA(&ma) == 0) {
    Serial.println(String(ma) + "mA");
  } else {
    Serial.println("Cannot read current.");
  }
  delay(1000);
}
