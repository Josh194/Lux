#include "Channel.h"

#include "../oscillator/Oscillator.h"

Channel::Channel() {
	this -> pitch = 0;
	this -> frequency = 0.0f;

	this -> stepSize = nullptr;

	this -> wavePosition = nullptr;

	this -> oscillators = 0;
}

Channel::~Channel() {
	//std::cout << "destroyed" << std::endl;
	for(unsigned char i = 0; i < oscillators; i++) {
		delete stepSize[i];
		delete wavePosition[i];
	}

	delete[] stepSize;
	delete[] wavePosition;
}

void Channel::init(unsigned char pitch, void* oscillators, unsigned char numOscillators) {
	this -> pitch = pitch;
	this -> frequency = cnv::frequency(pitch);

	this -> stepSize = new float*[numOscillators];

	this -> wavePosition = new float*[numOscillators];

	for (unsigned char i = 0; i < numOscillators; i++) {
		//Could probbly be simplified
		stepSize[i] = new float[((Oscillator*) oscillators)[i].unison];
		wavePosition[i] = new float[((Oscillator*) oscillators)[i].unison];

		stepSize[i][0] = cnv::stepSize(frequency);
		wavePosition[i][0] = 0.0f;

		//Unison mode
//		short start = (((Oscillator*) oscillators)[i].unison - 1) / -2;
//
//		for (short c = start; c < (((Oscillator*) oscillators)[i].unison + 1) / 2; c++) {
//			//float ratio = ((((float) c) / start) + 1) / 2.0f;
//			float ratio = ((((float) c) / (8 * start)) + 1) / 2.0f;
//
//			stepSize[i][c - start] = cnv::stepSize(cnv::frequency(pitch - 1) * ratio + cnv::frequency(pitch + 1) * (1 - ratio));
//			wavePosition[i][c - start] = 0.0f;
//		}
	}

	this -> oscillators = numOscillators;
}
