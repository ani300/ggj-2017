#pragma once

#include "SpriteNode.h"
#include <SFML/Graphics.hpp>


class WaveGenerator : public SpriteNode {
	WaveGenerator();
	WaveGenerator(float amplitude, float frequency);
	~WaveGenerator();

	virtual updateCurrent(sf::Time dt) override; 
	virtual drawCurrent() override;

	float amplitudeAt(sf::Vector2f pos);	

	void setAngle(float angle);

protected:
	float frequency;
	float linearSpeed;
	float amplitude;
	float angle;

	float waveNumber;
};

