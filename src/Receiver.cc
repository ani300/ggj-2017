#include "Receiver.h"


Receiver::Receiver(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators) : 
	AnimationNode(texture, "res/anim/receiver.anim"),
	generators(generators)
{
	history_length = 60;
	activation_threshold = 45./history_length;
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

//	std::cout << "ActiveFrames: " << activeFramesCount << std::endl;

//	std::cout << "Ratio: " << static_cast<double>(activeFramesCount)/static_cast<double>(history_length) << " " << activation_threshold << std::endl;
	return static_cast<double>(activeFramesCount)/static_cast<double>(history_length) > activation_threshold;
}

bool Receiver::around(float value, float target) {
	float max_range, min_range;

	max_range = target + precision;
	min_range = target - precision;

	return value < max_range && value > min_range;
}
