#pragma once
#include <cstdint>
constexpr int16_t RADIOLIB_ERR_NONE = 0;
constexpr uint8_t RADIOLIB_SX126X_PA_RAMP_1700U = 0x06;
class Module {};
class CustomSX1262 {
public:
  int8_t power = 0;
  uint8_t ramp = 0x04;
  int ramp_calls = 0;
  int16_t ramp_result = 0;
  CustomSX1262(Module*) {}
  virtual int16_t setOutputPower(int8_t requested) {
    if (requested < -9 || requested > 22) return -13;
    power = requested;
    ramp = 0x04;
    return 0;
  }
  int16_t setPaRampTime(uint8_t value) {
    ++ramp_calls;
    if (ramp_result != 0) return ramp_result;
    ramp = value;
    return 0;
  }
};
