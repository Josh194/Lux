#include "WaveTable.h"

WaveTable::WaveTable(unsigned char size) {
	frames = new WaveForm[size];
}

WaveTable::~WaveTable() {
	delete[] frames;
}