#include <INA226_asukiaaa.h>

INA226_asukiaaa voltCurrMeter(INA226_ASUKIAAA_ADDR_A0_GND_A1_GND, INA226_asukiaaa::calcCalibByResisterMilliOhm(2));

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
}
