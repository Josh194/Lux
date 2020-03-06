#pragma once

#include <math.h>

namespace fnc {

void fillSine(float *out, unsigned short size) {
	for (unsigned short i = 0; i < size; i++) {
		out[i] = sin((2 * M_PI * i) / size);
	}
}

void fillSawtooth(float *out, unsigned short size) {
	for (unsigned short i = 0; i < size; i++) {
		out[i] = (2 * (((i + (size / 2)) % size) - (size / 2))) / (double) size;
	}
}

void fillSquare(float *out, unsigned short size) {
	for (unsigned short i = 0; i < size; i++) {
		if (i >= size / 2) {
			out[i] = 1.0f;
		} else {
			out[i] = -1.0f;
		}
	}
}

void fillTest(float *out, unsigned short size) {
	for (unsigned short i = 0; i < size; i++) {
		double sum = 0.0;

		for (unsigned short s = 1; s < 25; s++) {
			sum += (2 * sin((s * M_PI * i) / (size / 2))) / s;
		}

		sum /= 2 * M_PI;

		out[i] = sum;
	}
}

};

