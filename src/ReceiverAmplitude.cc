#include "ReceiverAmplitude.h"

ReceiverAmplitude::ReceiverAmplitude(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators, sol::function f) : 
	Receiver(texture, generators),
	threshold_fn(f)
{
	activationHistory = std::vector<bool>(history_length, false);	
}


bool ReceiverAmplitude::isOnRightNow() {
	float totalInput = 0;
	for(WaveGenerator* g : generators) {
		if(g->isPlaced()) {
			totalInput += g->amplitudeAt(getWorldPosition());
		}
	}
	
	std::cout << "Lua fun: " << totalInput << " " << (bool)threshold_fn(totalInput) << std::endl;
	return threshold_fn.call<bool>(totalInput); 
}


void ReceiverAmplitude::updateCurrent(sf::Time /*dt*/) {
	// TODO: Animate on/off
	on = isOn();
}
