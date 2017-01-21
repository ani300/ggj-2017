#include "Receiver.h"


Receiver::Receiver(sf::Texture const& texture, std::vector<WaveGenerator*> const& generators) : 
	AnimationNode(texture, "res/animations/Receiver.anim"),
	generators(generators)
{
}

bool Receiver::getState(){
	return on;
}
