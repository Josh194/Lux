#include "../../src/oscillator/Oscillator.h"

Oscillator::Oscillator() {
	wavetable = new WaveTable(1);
}

Oscillator::~Oscillator() {
	delete wavetable;
}

void Oscillator::sample(float *out, float step) {

}
