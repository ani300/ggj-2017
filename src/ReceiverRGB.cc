#include "ReceiverRGB.h"
#include "WaveGenerator.h"

ReceiverRGB::ReceiverRGB(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators, sf::Color objective) : 
	Receiver(texture, generators),
	mObjective(objective)
{
	history_length = 120;
	activation_threshold = 1./history_length;

	activationHistory = std::vector<bool>(history_length, false);	
}


bool ReceiverRGB::isOnRightNow() {
	sf::Color totalInput;
	for(WaveGenerator* g : generators) {
		if(g->isPlaced()) {
			totalInput += static_cast<ColorGenerator*>(g)->colorAt(getWorldPosition());
		}
	}
	
	std::cout << int(totalInput.r) << " " << int(totalInput.g) << " " << int(totalInput.b) << std::endl;
	std::cout << int(mObjective.r) << " " << int(mObjective.g) << " " << int(mObjective.b) << std::endl;
	int sub = (totalInput.r + totalInput.g + totalInput.b) - (mObjective.r + mObjective.g + mObjective.b);
	std::cout << sub << std::endl;
	return abs(sub) < 15;
}


void ReceiverRGB::updateCurrent(sf::Time /*dt*/) {
	on = isOn();
	if(on)
		this->setScale(sf::Vector2f(1.6,1.6));
	else	
		this->setScale(sf::Vector2f(1,1));
}
