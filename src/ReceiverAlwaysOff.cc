#include "ReceiverAlwaysOff.h"

ReceiverAlwaysOff::ReceiverAlwaysOff(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators) : 
	Receiver(texture, generators)
{
	activationHistory = std::vector<bool>(HISTORY_LENGTH, false);
	currentFrame = 0;
}

bool ReceiverAlwaysOff::isOn() {
	int count = 0;
	//Set current frame
	activationHistory[currentFrame] = isOnRightNow();
	//Check last 60 frames
	for(int i = (currentFrame+1)%60 ; i != currentFrame; i = (i+1)%60) {
		count += activationHistory[i];
	}

	currentFrame = (currentFrame + 1) % 60;

	return count/HISTORY_LENGTH > ACTIVATION_THRESHOLD;
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

void ReceiverAlwaysOff::updateCurrent(sf::Time dt) {
	on = isOn();
}