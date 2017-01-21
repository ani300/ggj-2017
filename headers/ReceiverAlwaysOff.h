#pragma once

#include "Receiver.h"
/*
* Receiver always off
* This receiver is on when has been blow 0 during the last 60 frames
*/
class ReceiverAlwaysOff: public Receiver {
public:
	ReceiverAlwaysOff(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators);
	
private:
	
	int history_length = 60;
	int activation_threshold = 45/history_length;

	bool isOnRightNow();
    void updateCurrent(sf::Time dt) override;
};