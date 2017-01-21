#include "Receiver.h"


Receiver::Receiver(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators) : 
	AnimationNode(texture, "res/animations/Receiver.anim"),
	generators(generators)
{
}

bool Receiver::getState(){
	return on;
}

bool Receiver::isOn() {
	//Check last frame and update active frame count
	if(activationHistory[currentFrame]) {
		activeFramesCount--;
	}

	//Set current frame
	activationHistory[currentFrame] = isOnRightNow();
	
	if(activationHistory[currentFrame]) {
		activeFramesCount++;	
	}
	
	currentFrame = (currentFrame + 1) % history_length;

	return activeFramesCount/history_length < activation_threshold;
}