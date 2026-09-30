#pragma once
#include <cstdint>
constexpr int HIGH=1, LOW=0, OUTPUT=1;
extern uint32_t mock_now;
extern int mock_pins[64], mock_sleeps, mock_delays;
inline uint32_t millis() { return mock_now; }
inline void pinMode(int, int) {}
inline void digitalWrite(int pin, int value) { mock_pins[pin]=value; }
inline int digitalRead(int pin) { return mock_pins[pin]; }
inline void delay(unsigned long) { ++mock_delays; }
inline void analogReadResolution(int) {}
inline int analogRead(int) { return 0; }
