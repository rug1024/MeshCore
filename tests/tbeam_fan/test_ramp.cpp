#include <cassert>
#include "../../variants/lilygo_tbeam_1w/TBeam1WRadio.h"
int main() {
  Module mod;
  TBeam1WRadio radio(&mod);
  CustomSX1262* driver = &radio; // Exercise virtual dispatch used by RadioLibWrapper.
  for (int power = -9; power <= 22; ++power) {
    assert(driver->setOutputPower(power) == 0);
    assert(radio.power == power);
    assert(radio.ramp == 0x06);
  }
  int calls = radio.ramp_calls;
  assert(driver->setOutputPower(30) == -13);
  assert(radio.ramp_calls == calls);
  assert(radio.power == 22 && radio.ramp == 0x06);
  radio.ramp_result = -2;
  assert(driver->setOutputPower(20) == -2);
}
