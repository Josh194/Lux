#include "Synth.h"

using namespace sye;

Synth::Synth() {
	this->oscillators = new Oscillator[3];

	this->channelSystem = new ChannelSystem(VOICES);

	//Creates an array aligned to a 32 byte boundry to allow for avx loads
	this->sampled = (float*) aligned_alloc(32, SUB_BUFFER_SIZE * sizeof(float));

	this->accumulator = new __m256 [breaks];
}

Synth::~Synth() {
	//delete buffer; // Is this required?

	// TODO: Clean up

	//delete oscillators;
	delete channelSystem;

	free(sampled);

	delete accumulator;
}

void Synth::sample(float *buffer) {
	pair<unsigned char, Channel*> channels = channelSystem->getChannels();

#pragma GCC unroll breaks
	for (unsigned char i = 0; i < breaks; i++) {
		accumulator[i] = _mm256_setzero_ps();
	}

	for (unsigned char c = 0; c < channels.first; c++) {
		for (unsigned char o = 0; o < 3; o++) {
			for (unsigned char d = 0; d < oscillators[o].unison; d++) {
				oscillators[o].sample(sampled, channels.second + c, o, d);

	#pragma GCC unroll breaks
				for (unsigned char i = 0; i < breaks; i++) {
					//Could maybe be slightly optimized by pre allocating space for the __m256
					__m256 tmp = _mm256_load_ps(sampled + (i * 8));

					//Adds first one to list of 0's
					accumulator[i] = _mm256_add_ps(accumulator[i], tmp);
				}
			}
		}
	}

#pragma GCC unroll breaks
	for (unsigned char i = 0; i < breaks; i++) {
		//Assumes pointer is aligned, which portaudio seems to do
		_mm256_store_ps(buffer + (i * 8), accumulator[i]);
	}
}
