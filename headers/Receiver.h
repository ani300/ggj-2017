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
	
	double activation_threshold;
	int history_length;

protected:
	std::vector<bool> activationHistory;
	int currentFrame = 0;
	int activeFramesCount = 0;
	
	std::vector<WaveGenerator*> const& generators;
	
	bool on = false;

	bool around(float value, float target);

	//Has been on in average during some time
	bool isOn();

	float precision = 1e-3;

	virtual bool isOnRightNow() = 0;

	virtual void updateCurrent(sf::Time dt) = 0;

};
