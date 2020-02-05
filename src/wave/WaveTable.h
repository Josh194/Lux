#pragma once

#include "WaveForm.h"

class WaveTable {
public:
	WaveTable(unsigned char size);
	~WaveTable();

	WaveForm *frames;
};
