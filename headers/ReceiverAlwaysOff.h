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
	
	const int HISTORY_LENGTH = 60;
	//Frames needed to consider activated
	const float ACTIVATION_THRESHOLD = 45/HISTORY_LENGTH;

	bool isOn();
	bool isOnRightNow();
    void updateCurrent(sf::Time dt) override;
};