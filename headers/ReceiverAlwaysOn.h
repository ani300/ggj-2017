#pragma once

#include "Receiver.h"
/*
 * Receiver always on
 * This receiver is on when has been above 0 during the last 60 frames
 */
class ReceiverAlwaysOn : public Receiver {
public:
	ReceiverAlwaysOn(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators);
	//Check if the received value reached the target
	
private:
	const int HISTORY_LENGTH = 60;
	const float ACTIVATION_THRESHOLD = 45/HISTORY_LENGTH;

	void updateCurrent(sf::Time dt) override;

	virtual bool isOn() override;
	virtual bool isOnRightNow() override;
};
