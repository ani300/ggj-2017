#pragma once

#include "Receiver.h"
/*
 * Receiver always on
 * This receiver is on when has been above 0 during the last 60 frames
 */
class ReceiverAlwaysOn : public Receiver {
public:
	ReceiverAlwaysOn(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators);
	
	
private:
	int history_length = 60;
	int activation_threshold = 45/history_length;

	void updateCurrent(sf::Time dt) override;

	virtual bool isOnRightNow() override;
};
