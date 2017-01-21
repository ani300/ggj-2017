#pragma once

#include "AnimationNode.h"
#include "WaveGenerator.h"
#include <vector>

class Receiver: public AnimationNode {
public:
	Receiver(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators);
	virtual ~Receiver() {}
	//Get the current state of the receiver (on/off)
	bool getState();

protected:
	std::vector<bool> activationHistory;
	int currentFrame;
	
	std::vector<WaveGenerator*> const& generators;
	
	bool on = false;

	//Has been on in average during some time
	virtual bool isOn() = 0;

	virtual bool isOnRightNow() = 0;

	virtual void updateCurrent(sf::Time dt) = 0;
};
