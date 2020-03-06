#pragma once

#include "../util/ConversionUtils.h"

using namespace cnv;

struct Channel {
	Channel();
	~Channel();

	//Should NOT be needed
	void init(unsigned char pitch, void* oscillators, unsigned char numOscillators);

	unsigned char pitch;
	float frequency;

	float** stepSize;

	float** wavePosition;

private:
	unsigned char oscillators;
};
