#include "ChannelSystem.h"

ChannelSystem::ChannelSystem(unsigned char voices) {
	this -> channels = new Channel[voices];

	this -> channels -= 1;

	this -> size = 0;
}

ChannelSystem::~ChannelSystem() {

}

pair<unsigned char, Channel*> ChannelSystem::getChannels() {
	if (sye::MONO) {
		return make_pair(min((unsigned char) 1, size), channels);
	} else {
		return make_pair(size, channels);
	}
}

void ChannelSystem::addChannel(unsigned char pitch, void* oscillators, unsigned char numOscillators) {
	for (short i = size; i > 0; i--) {
		channels[i] = channels[i - 1];
	}

	channels[0].init(pitch, oscillators, numOscillators);

	size++;
}

void ChannelSystem::removeChannel(unsigned char pitch) {
	// Find channel, could be optimized with a lookup table
	for (unsigned char i = 0; i < size; i++) {
		if (channels[i].pitch == pitch) {
			//Move all in front forward
			for (unsigned char c = i; c < size - 1; c++) {
				channels[c] = channels[c + 1];
			}

			break;
		}
	}

	size--;
}

void ChannelSystem::modifyChannel(unsigned char pitch, unsigned char amount) {
	// TODO
}

void ChannelSystem::setPolyphony(unsigned char amount) {
	delete[] channels;

	channels = new Channel[amount];

	size = 0;
}
