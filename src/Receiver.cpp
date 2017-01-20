#include "Receiver.h"


Receiver::Receiver(const sf::Texture& texture) : 
	SpriteNode(texture){
}


bool Receiver::getState(){
	return on;
}