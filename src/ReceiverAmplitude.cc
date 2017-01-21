#include "ReceiverAmplitude.h"

ReceiverAmplitude::ReceiverAmplitude(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators, float t) : 
	Receiver(texture, generators)
{
	target = t;
	activationHistory = std::vector<bool>(HISTORY_LENGTH, false);
	currentFrame = 0;
}

bool ReceiverAmplitude::isOn() {
	int count = 0;
	//Set current frame
	activationHistory[currentFrame] = isOnRightNow();
	//Check last 60 frames
	for(int i = (currentFrame+1)%60; i != currentFrame; i = (i + 1)%60) {
		count += activationHistory[i];
	}

	currentFrame = (currentFrame + 1) % 60;

	return count/HISTORY_LENGTH > ACTIVATION_THRESHOLD;
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


void ReceiverAmplitude::updateCurrent(sf::Time dt) {
	// TODO: Animate on/off
	on = isOn();
}