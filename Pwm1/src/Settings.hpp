
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <stdint.h>

struct Settings {
    const uint32_t default_channels = 1;  /* Number of channels silence is played
					     on when stream is not playing */
    constexpr static uint32_t samplerate = 46875;

    uint32_t freq_square = 0;     // freq in hz of signal/square, set by
    uint32_t freq_signal = 0;     // update_frequencies

    uint32_t samples_square = 0;  // number of samples/square per signal
    uint32_t samples_signal = 0;  // period, set by update_frequencies

    uint32_t volume = 278;        // hardware dependant
} g_settings;


#endif

