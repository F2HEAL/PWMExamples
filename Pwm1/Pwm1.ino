// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Adafruit_TinyUSB.h"
#include "src/PwmTactor.hpp"
#include "src/Settings.hpp"
#include "src/SampleCache.hpp"

using namespace audio_tactile;

// Global variables
SampleCache samplecache;

struct Status {
    uint32_t counter_square = 0;  // signal samples have been played
    uint32_t counter_signal = 0;  // square samples have been played 
    uint32_t volume = 0;
}g_status;


void setup() 
{
    update_frequencies(20, 40);
    
    PwmTactor.OnSequenceEnd(OnPwmSequenceEnd);
    PwmTactor.Initialize();
}

void update_frequencies(uint32_t freq_square, uint32_t freq_signal) 
{
    g_settings.freq_square = freq_square;
    g_settings.samples_square = g_settings.samplerate / freq_square;
    
    g_settings.freq_signal = freq_signal;
    g_settings.samples_signal = g_settings.samplerate / freq_signal;

    samplecache.InitSampleCache(freq_signal);
    
    g_status.counter_square = g_status.counter_signal = 0;
}


void OnPwmSequenceEnd() 
{
    //Is square wave active?
    if(g_status.counter_square < g_settings.samples_square / 2)
    {
	//square is active, play sine wave
	uint16_t* cp = PwmTactor.GetChannelPointer(0); // working on
						       // channel 0

	// provide the kNumPwmValues (8) samples for this channel
	// get_sample returns a uint16_t with values between 0 and 2 * volume
	for(uint32_t i = 0; i < kNumPwmValues; i++)
	    cp[i] = samplecache.get_sample(g_status.counter_signal + i, g_settings.volume);
    } else {
	//square is inactive, play silence for this channel.
	// as get_sample returns a uint16_t with values between 0 and
	// 2 * volume, we silence a channel by settings all samples
	// equal to volume
	PwmTactor.SilenceChannel(0, g_settings.volume);
    }

    //advance the square counter
    g_status.counter_square += kNumPwmValues;
    while(g_status.counter_square  > g_settings.samples_square)
	g_status.counter_square -= g_settings.samples_square;
    
    //advance the sine counter
    g_status.counter_signal += kNumPwmValues;
    while(g_status.counter_signal > g_settings.samples_signal)
	g_status.counter_signal -= g_settings.samples_signal;
    
}

void loop() 
{
    // show some status output for debugging, not needed for normal operation
    while(true) {
	Serial.print("counter_square = ");
	Serial.println(g_status.counter_square);	
	Serial.print("counter_signal = ");
	Serial.println(g_status.counter_signal);
	delay(100);
    }
}

    

    
    


