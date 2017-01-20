#include "ReceiverAlwaysOn.h"



const int HISTORY_LENGTH = 60;

//Frames needed to consider activated
const float ACTIVATION_THRESHOLD = 45/HISTORY_LENGTH;

ReceiverAlwaysOn::ReceiverAlwaysOn(const sf::Texture& texture, const &vector<WaveGenerator> generators) : 
	Receiver(texture, generators){

	activationHistory = new vector<bool>(HISTORY_LENGTH, false);
	currentFrame = 0;
}

bool ReceiverAlwaysOn::isOn(){
	int count = 0;
	//Set current frame
	activationHistory[currentFrame] = isOnRightNow();
	//Check last 60 frames
	for(int i = (currentFrame+1)%60 ; i != currentFrame; i = (i+1)%60)
	{
		count += activationHistory[i];
	}

	currentFrame = (currentFrame + 1) % 60;

	return count/HISTORY_LENGTH > ACTIVATION_THRESHOLD;
}

bool ReceiverAlwaysOn::isOnRightNow(){
	float totalInput = 0;
	for(WaveGenerator g : generators)
	{
		if(g.isPlaced())
		{
			totalInput += g.amplitudeAt( getWorldPosition() );
		}
	}

	return totalInput > 0;
}

void ReceiverAlwaysOn::drawCurrent(sf::RenderTarget& target, sf::RenderStates states){
	//TODO: animate on/off
	if(on)
	{
		target.draw(mSprite, states);
	}
	else
	{
		target.draw(mSprite, states);
	}
}

void ReceiverAlwaysOn::updateCurrent(sf::Time dt){
	on = isOn();
}