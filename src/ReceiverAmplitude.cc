#include "ReceiverAmplitude.h"

ReceiverAmplitude::ReceiverAmplitude(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators, float t) : 
	Receiver(texture, generators)
{
	target = t;
	activationHistory = std::vector<bool>(history_length, false);	
}


bool ReceiverAmplitude::isOnRightNow() {
	float totalInput = 0;
	for(WaveGenerator* g : generators) {
		if(g->isPlaced()) {
			totalInput += g->amplitudeAt(getWorldPosition());
		}
	}

	return totalInput > target;
}


void ReceiverAmplitude::updateCurrent(sf::Time /*dt*/) {
	// TODO: Animate on/off
	on = isOn();
}