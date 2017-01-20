#ifndef RECEIVER_H
#define RECEIVER_H

#include "SpriteNode.h"

class Receiver: public SpriteNode{
	public:
		Receiver(const sf::Texture& texture, float target);
		//Updates input values (sum of input waves)
		void update_input_value();
		//Check if the received value reached the target
		bool is_on();
	private:
		//Sum of current input values
		float input;
		//Target at which the receiver "turns on"
		float target;

};

#endif //RECEIVER_H