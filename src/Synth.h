#pragma once

#include <immintrin.h>

#include "oscillator/Oscillator.h"

#include "channel/ChannelSystem.h"

#include "Environment.h"

using namespace aue;

class Synth {
public:
	Synth();
	~Synth();

	void sample(float* buffer);

	ChannelSystem* channelSystem;

	Oscillator* oscillators;

private:
	constexpr static unsigned short breaks = SUB_BUFFER_SIZE / 8;

	float* sampled;

	__m256* accumulator;
};
