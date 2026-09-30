#pragma once
#include <Arduino.h>
class ESP32Board {
public:
  void begin() {}
  virtual void onBeforeTransmit() {}
  virtual void onAfterTransmit() {}
  virtual uint16_t getBattMilliVolts() { return 0; }
  virtual const char* getManufacturerName() const { return ""; }
  virtual void powerOff() {}
  virtual void sleep(uint32_t) { ++mock_sleeps; }
};
