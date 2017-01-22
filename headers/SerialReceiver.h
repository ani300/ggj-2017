#pragma once

#include "WaveGenerator.h"
#include <vector>

class LinkedReceiver : public ReceiverAmplitude{
public:
	LinkedReceiver(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators);
	virtual ~LinkedReceiver() {}
	//Get the current state of the receiver (on/off)
	bool getState() override;

protected:
	LinkedReceiver* previous;


};