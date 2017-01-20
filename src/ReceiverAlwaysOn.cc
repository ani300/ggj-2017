#include "ReceiverAlwaysOn.h"
#include "WaveGenerator.h"




ReceiverAlwaysOn::ReceiverAlwaysOn(std::vector<WaveGenerator*> *generators, sf::Texture& texture) : 
	Receiver(texture, generators){

	activationHistory = std::vector<bool>(HISTORY_LENGTH, false);
	currentFrame = 0;
}

bool ReceiverAlwaysOn::isOn(){
	int count = 0;
	//Set current frame
	activationHistory[currentFrame] = isOnRightNow();
	//Check last 60 frames
	for(int i = (currentFrame+1)%60; i != currentFrame; i = (i+1)%60)
	{
		count += activationHistory[i];
	}

	currentFrame = (currentFrame + 1) % 60;

	return count/HISTORY_LENGTH < ACTIVATION_THRESHOLD;
}

bool ReceiverAlwaysOn::isOnRightNow(){
	float totalInput = 0;
	for(auto g: *generators)
	{
		if(g->isPlaced())
		{
			totalInput += g->amplitudeAt( getWorldPosition() );
		}
	}

	return totalInput > 0;
}


void ReceiverAlwaysOn::updateCurrent(sf::Time dt){
	on = isOn();
}
