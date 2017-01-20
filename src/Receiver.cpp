#include "Receiver.h"
#include "WaveGenerator.h"

#include <vector>

Receiver::Receiver(const sf::Texture& texture) : 
	SpriteNode(texture){
}

void Receiver::update_input_value(const &std::vector<WaveGenerator> generators){
	
	for(WaveGenerator g : generators)
	{
		input += g.amplitudeAt( getWorldPosition() );
	}
}

