#pragma once

#include "../../src/wave/WaveForm.h"

class WaveTable {
public:
	WaveTable(unsigned char size);
	~WaveTable();

	WaveForm *frames;
};
