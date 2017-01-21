#pragma once

#include "Receiver.h"
#include "sol/sol.h"
/*
* Receiver amplitude
* This receiver is on when a target amplitude has been reached in 
* the last ACTIVATION_THRESHOLD frames
*/
class ReceiverAmplitude: public Receiver {
public:
	ReceiverAmplitude(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators, sol::function f);

private:
	int history_length = 60;
	int activation_threshold = 10/history_length;

	float target = 2;

	bool isOnRightNow();
	void updateCurrent(sf::Time dt) override;

	sol::function threshold_fn;
};
