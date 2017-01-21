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
	int currentFrame = 0;
	int activeFramesCount = 0;
	
	std::vector<WaveGenerator*> const& generators;
	
	bool on = false;
	int history_length = 60;
	double activation_threshold = 45./history_length;

	//Has been on in average during some time
	bool isOn();


	virtual bool isOnRightNow() = 0;

	virtual void updateCurrent(sf::Time dt) = 0;
};
