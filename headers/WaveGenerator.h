#pragma once

#include "AnimationNode.h"
#include <SFML/Graphics.hpp>


class WaveGenerator : public AnimationNode {
public:
	WaveGenerator(sf::Texture &texture, const std::string& file);
	WaveGenerator(sf::Texture &texture, const std::string& file, float amplitude, float frequency);
	~WaveGenerator();

	virtual void updateCurrent(sf::Time dt) override;

	float amplitudeAt(sf::Vector2f pos) const;

	float getFrequency() { return frequency; }
	float getWavelength() { return wavelength; }
	float getAmplitude() { return amplitude; }
	float getAngle() { return angle; }

	void setAngle(float angle);

	bool isPlaced() const;

protected:
	float frequency;
	float wavelength;
	float amplitude;
	float angle;

	float waveNumber;

	bool placed;
};
