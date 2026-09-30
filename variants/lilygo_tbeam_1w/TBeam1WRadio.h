#pragma once

#include <helpers/radiolib/CustomSX1262.h>

// LilyGO recommends >800 us PA stabilization for the T-Beam 1W.
// 1700 us is the next supported SX1262 ramp setting above 800 us.
class TBeam1WRadio : public CustomSX1262 {
public:
  TBeam1WRadio(Module* mod) : CustomSX1262(mod) {}

  int16_t setOutputPower(int8_t power) override {
    int16_t status = CustomSX1262::setOutputPower(power);
    if (status != RADIOLIB_ERR_NONE) return status;
    // RadioLib resets the ramp to 200 us whenever it changes output power.
    // Preserve its optimized PA settings and reapply only the ramp time.
    return setPaRampTime(RADIOLIB_SX126X_PA_RAMP_1700U);
  }
};
