#include "ReceiverAmplitude.h"

ReceiverAmplitude::ReceiverAmplitude(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators, sol::function f) : 
	Receiver(texture, generators),
	threshold_fn(f)
{
	history_length = 120;
	activation_threshold = 1./history_length;

	activationHistory = std::vector<bool>(history_length, false);	
}


bool ReceiverAmplitude::isOnRightNow() {
	float totalInput = 0;
	for(WaveGenerator* g : generators) {
		if(g->isPlaced()) {
			totalInput += g->amplitudeAt(getWorldPosition());
		}
	}

//	std::cout << "TF: " << totalInput << " " << (bool)threshold_fn(totalInput) << std::endl;
	return threshold_fn(totalInput); 
}


void ReceiverAmplitude::updateCurrent(sf::Time /*dt*/) {
	on = isOn();
	if(on)
		this->setScale(sf::Vector2f(1.6,1.6));
	else	
		this->setScale(sf::Vector2f(1,1));
}
