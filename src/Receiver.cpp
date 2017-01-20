#include "Receiver.h"
#include "WaveGenerator.h"

#include <vector>

Receiver::Receiver(const sf::Texture& texture, float target) : 
	SpriteNode(texture){
		this.target = target;
}

void Receiver::update_input_value(const &std::vector<WaveGenerator> generators){
	for(WaveGenerator g : generators)
	{
		this.input += g.amplitudeAt( this.getWorldPosition() );
	}
}

bool Receiver::is_on(){
	return this.input >= this.target;
}