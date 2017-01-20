#pragma once

#include "SpriteNode.h"
#include "WaveGenerator.h"
#include <vector>

class Receiver: public SpriteNode{
	public:
		Receiver(const sf::Texture& texture, std::vector<WaveGenerator>* generators);
		//Get the current state of the receiver (on/off)
		bool getState();
	private:
		std::vector<bool> activationHistory;
		int currentFrame;
		std::vector<WaveGenerator>* generators;
		bool on;
		//Has been on in average during some time
		virtual bool isOn();

		virtual bool isOnRightNow();
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt) override;
