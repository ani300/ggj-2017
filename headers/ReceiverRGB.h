#pragma once

#include "Receiver.h"
/*
* Receiver amplitude
* This receiver is on when a target amplitude has been reached in 
* the last ACTIVATION_THRESHOLD frames
*/
class ColorGenerator;

class ReceiverRGB: public Receiver {
public:
	ReceiverRGB(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators, sf::Color objective);

private:
	bool isOnRightNow();
	void updateCurrent(sf::Time dt) override;

	sf::Color mObjective;
};
