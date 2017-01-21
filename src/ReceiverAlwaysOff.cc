#include "ReceiverAlwaysOff.h"

ReceiverAlwaysOff::ReceiverAlwaysOff(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators) : 
	Receiver(texture, generators)
{
	activationHistory = std::vector<bool>(history_length, false);
}


bool ReceiverAlwaysOff::isOnRightNow() {
	float totalInput = 0;
	for(WaveGenerator* g : generators) {
		if(g->isPlaced()) {
			totalInput += g->amplitudeAt(getWorldPosition());
		}
	}

	return totalInput < 0;
}

void ReceiverAlwaysOff::updateCurrent(sf::Time /*dt*/) {
	on = isOn();
}