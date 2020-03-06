#include "Oscillator.h"

#include "../Environment.h"

using namespace aue;

Oscillator::Oscillator() {
	this -> wavetable = new WaveTable(1);

	this -> unison = 1;
	this -> detune = 1;
}

Oscillator::~Oscillator() {
	delete wavetable;
}

void Oscillator::sample(float* out, Channel* channel, unsigned char index, unsigned char detuneIndex) {
	float location;

	for (unsigned short i = 0; i < SUB_BUFFER_SIZE; i++) {
		//Could be slightly optimized at the cost of accuracy by using an int instead of float
		location = fmod((i * channel -> stepSize[index][detuneIndex]) + channel -> wavePosition[index][detuneIndex], 2048.0f);

		out[i] = (wavetable -> frames)[0].samples[(unsigned short) location];
	}


	//Requires Stereo
//	for (unsigned short i = 0; i < SUB_BUFFER_SIZE; i++) {
//		//Could be slightly optimized at the cost of accuracy by using an int instead of float
//		location = fmod((i * channel -> stepSize[index][detuneIndex]) + channel -> wavePosition[index][detuneIndex], 2048.0f);
//
//		if (detuneIndex % 2 == 0) {
//			if (i % 2 == 0) {
//				out[i] = (wavetable -> frames)[0].samples[(unsigned short) location];
//			}
//		} else {
//			if (i % 2 != 0) {
//				out[i] = (wavetable -> frames)[0].samples[(unsigned short) location];
//			}
//		}
//	}

	channel -> wavePosition[index][detuneIndex] = fmod((SUB_BUFFER_SIZE * channel -> stepSize[index][detuneIndex]) + channel -> wavePosition[index][detuneIndex], 2048.0f);
}
