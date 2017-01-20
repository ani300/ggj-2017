#include "Receiver.h"


Receiver::Receiver(sf::Texture& texture, std::vector<WaveGenerator*> *generators) : 
	AnimationNode(texture, "res/animations/Receiver.anim"),
	generators(generators)
{
}

bool Receiver::getState(){
	return on;
}
