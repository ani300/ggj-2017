#include "Receiver.h"


Receiver::Receiver(sf::Texture& texture, std::vector<WaveGenerator*> *generators) : 
	AnimationNode(texture),
	generators(generators)
{
}

bool Receiver::getState(){
	return on;
}
