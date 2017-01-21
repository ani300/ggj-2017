#include "ReceiverAlwaysOn.h"
#include "WaveGenerator.h"

ReceiverAlwaysOn::ReceiverAlwaysOn(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators) : 
	Receiver(texture, generators)
{
	activationHistory = std::vector<bool>(history_length, false);
}

bool ReceiverAlwaysOn::isOnRightNow() {
	float totalInput = 0;
	for(auto g : generators) {
		if(g->isPlaced())
		{
			totalInput += g->amplitudeAt(getWorldPosition());
		}
	}

	return totalInput > 0;
}


void ReceiverAlwaysOn::updateCurrent(sf::Time dt) {
	on = isOn();
}
