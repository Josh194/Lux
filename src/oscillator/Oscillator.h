#pragma once

#include "../wave/WaveTable.h"

class Oscillator {
public:
	Oscillator();
	~Oscillator();

	void sample(float *out, float step);

	WaveTable* wavetable;
};
