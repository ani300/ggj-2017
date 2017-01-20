#pragma once

#include "SpriteNode.h"
#include <SFML/Graphics.hpp>


class WaveGenerator : public SpriteNode {
	WaveGenerator(sf::Texture &texture);
	WaveGenerator(sf::Texture &texture, float amplitude, float frequency);
	~WaveGenerator();

	virtual void updateCurrent(sf::Time dt) override; 
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

	float amplitudeAt(sf::Vector2f pos) const;

	void setAngle(float angle);

	bool isPlaced() const;

protected:
	float frequency;
	float linearSpeed;
	float amplitude;
	float angle;

	float waveNumber;

	bool placed;
};

