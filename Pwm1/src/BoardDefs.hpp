#include <stdint.h>

#ifndef BOARDDEFS_HPP_
#define BOARDDEFS_HPP_

// Output sequence for Godef Hardware
const uint16_t order_pairs[8] = {4, 5, 6, 7, 8, 9, 10, 11}; 

namespace audio_tactile {
     // Number of PWM samples for each channel per buffer.
     constexpr int kNumPwmValues = 8;
}

#endif
