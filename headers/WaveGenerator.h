#pragma once

#include "AnimationNode.h"
#include <SFML/Graphics.hpp>


class WaveGenerator : public AnimationNode {
public:
	WaveGenerator(sf::Texture const& texture, std::string const& file);
	WaveGenerator(sf::Texture const& texture, std::string const& file, float amplitude, float frequency, float wavelength);
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


class StandardGenerator : public WaveGenerator {

};

class OffsetGenerator : public WaveGenerator {

};

class WavelengthGenerator : public WaveGenerator {

};

class FrequencyGenerator : public WaveGenerator {

};

class EditableGenertaor : public WaveGenerator {

};
