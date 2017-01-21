#pragma once

#include "Receiver.h"
/*
* Receiver amplitude
* This receiver is on when a target amplitude has been reached in 
* the last ACTIVATION_THRESHOLD frames
*/
class ReceiverAmplitude: public Receiver {
public:
	ReceiverAmplitude(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators, float t);

private:
	const int HISTORY_LENGTH = 60;

	//Successive frames needed to consider activated
    const float ACTIVATION_THRESHOLD = 10./HISTORY_LENGTH;

	float target;

	bool isOn();
	bool isOnRightNow();
	void updateCurrent(sf::Time dt) override;
};