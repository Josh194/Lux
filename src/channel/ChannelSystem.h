#pragma once

#include <iostream>

#include "Channel.h"

using namespace std;

class ChannelSystem {
public:
	ChannelSystem(unsigned char voices);
	~ChannelSystem();

	pair<unsigned char, Channel*> getChannels();

	void addChannel(unsigned char pitch, void* oscillators, unsigned char numOscillators);
	void removeChannel(unsigned char pitch);

	void modifyChannel(unsigned char pitch, unsigned char amount);

	void setPolyphony(unsigned char amount);

private:
	Channel* channels;

	unsigned char size;
};

