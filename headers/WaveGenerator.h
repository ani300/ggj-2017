#pragma once

#include "SpriteNode.h"
#include <SFML/Graphics.hpp>


class WaveGenerator : public SpriteNode {
	WaveGenerator(sf::Texture &texture);
	WaveGenerator(sf::Texture &texture, float amplitude, float frequency);
	~WaveGenerator();

	virtual void updateCurrent(sf::Time dt) override; 
	virtual void drawCurrent() const override;

	float amplitudeAt(sf::Vector2f pos);	

	void setAngle(float angle);

protected:
	float frequency;
	float linearSpeed;
	float amplitude;
	float angle;

	float waveNumber;
};
