#pragma once

#include "AnimationNode.h"
#include "WaveGenerator.h"
#include <vector>

class WaveGenerator;
class Receiver: public AnimationNode {
	public:
		Receiver(sf::Texture& texture, std::vector<WaveGenerator*>* generators);
		//Get the current state of the receiver (on/off)
		bool getState();

	protected:
		std::vector<bool> activationHistory;
		int currentFrame;
		
		std::vector<WaveGenerator*>* generators;
		
		bool on;

		//Has been on in average during some time
		virtual bool isOn();

		virtual bool isOnRightNow();

		virtual void updateCurrent(sf::Time dt) override;
};
