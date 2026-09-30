#include <cassert>
#include <cstdint>
#include <limits>
#include "../../variants/lilygo_tbeam_1w/TBeam1WBoard.cpp"

uint32_t mock_now = 0;
int mock_pins[64] = {};
int mock_sleeps = 0;
int mock_delays = 0;

int main() {
  TBeam1WBoard b;
  b.begin();
  assert(!b.isFanEnabled());
  b.onBeforeTransmit();
  assert(b.isFanEnabled());
  mock_now = 10000; // Long transmissions must not time out the fan.
  b.updateFan();
  assert(b.isFanEnabled());
  b.onAfterTransmit();
  mock_now = 14999;
  b.updateFan();
  assert(b.isFanEnabled());
  b.sleep(30);
  assert(mock_sleeps == 0);
  mock_now = 15000;
  b.updateFan();
  assert(!b.isFanEnabled());
  b.sleep(30);
  assert(mock_sleeps == 1);

  b.onBeforeTransmit();
  b.onAfterTransmit();
  mock_now += 4000;
  b.onBeforeTransmit();
  mock_now += 6000;
  b.updateFan();
  assert(b.isFanEnabled());
  b.onAfterTransmit();
  mock_now += 4999;
  b.updateFan();
  assert(b.isFanEnabled());
  ++mock_now;
  b.updateFan();
  assert(!b.isFanEnabled());

  // Unsigned elapsed time must work across the millis() rollover.
  mock_now = std::numeric_limits<uint32_t>::max() - 1000;
  b.onBeforeTransmit();
  b.onAfterTransmit();
  mock_now += 4999;
  b.updateFan();
  assert(b.isFanEnabled());
  ++mock_now;
  b.updateFan();
  assert(!b.isFanEnabled());

  // A failed radio start also calls onAfterTransmit().
  b.onBeforeTransmit();
  b.onAfterTransmit();
  mock_now += 5000;
  b.updateFan();
  assert(!b.isFanEnabled());

  b.onBeforeTransmit();
  b.powerOff();
  assert(!b.isFanEnabled());
}
