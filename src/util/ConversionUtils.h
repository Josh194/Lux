#pragma once

#include <math.h>

#include "../Environment.h"

using namespace aue;

namespace cnv {

//Should be in an anonymous namespace
extern float *MIDI;

//Shouldn't be inline
inline void init() {
	for (int i = 0; i < 127; i++) {
		MIDI[i] = (float) ((440.0 * pow(2.0, (i - 9) / 12.0)) / 32.0);
	}
}

inline float stepSize(float frequency) {
	return (2048.0f * frequency) / SAMPLE_RATE;
}

inline float frequency(unsigned char pitch) {
	return MIDI[pitch];
}

}

