#include "ReceiverAlwaysOff.h"

ReceiverAlwaysOff::ReceiverAlwaysOff(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators) : 
	Receiver(texture, generators)
{
	activationHistory = std::vector<bool>(history_length, false);
	precision = 1e-14;
}


bool ReceiverAlwaysOff::isOnRightNow() {
	float totalInput = 0;
	bool anyActive = false;
	for(auto g : generators) {
		if(g->isPlaced()) {
			anyActive = true;
			totalInput += g->amplitudeAt(getWorldPosition());
		}
		std::cout << totalInput << std::endl;
	}
	
	if(anyActive) {
		return around(totalInput, 0);
	} else {
		return false;
	}
}

void ReceiverAlwaysOff::updateCurrent(sf::Time /*dt*/) {
	on = isOn();
}
