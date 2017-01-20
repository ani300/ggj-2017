#pragma once

#include "SpriteNode.h"

class Receiver: public SpriteNode{
	public:
		Receiver(const sf::Texture& texture);
		//Check if the received value reached the target
		virtual bool is_on();
	private:
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent(sf::Time dt) override;
