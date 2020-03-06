#pragma once

#include "../wave/WaveTable.h"
#include "../channel/Channel.h"

class Oscillator {
public:
	Oscillator();
	~Oscillator();

	void sample(float* out, Channel* channel, unsigned char index, unsigned char detuneIndex);

	WaveTable* wavetable;

	unsigned char unison;
	unsigned char detune;
};
