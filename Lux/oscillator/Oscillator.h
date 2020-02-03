#pragma once

class Oscillator {
public:
	Oscillator();
	~Oscillator();

	void sample(float* out, float step);

	WaveTable wavetable;
};
