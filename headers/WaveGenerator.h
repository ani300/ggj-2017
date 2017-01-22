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

	void place(bool p);

protected:
	float frequency;
	float wavelength;
	float amplitude;
	float angle;

	float waveNumber;

	virtual float waveFunction(float distance) const;

	bool placed;
};


class StandardGenerator : public WaveGenerator {
public:
	StandardGenerator(sf::Texture const& texture, std::string const& file);
	StandardGenerator(sf::Texture const& texture, std::string const& file, float amplitude, float frequency, float wavelength);
	~StandardGenerator();
	
protected:
	virtual float waveFunction(float distance) const override;
	
};

class OffsetGenerator : public WaveGenerator {
public:
	OffsetGenerator(sf::Texture const& texture, std::string const& file);
	OffsetGenerator(sf::Texture const& texture, std::string const& file, float ampliture, float frequency, float wavelength);
	~OffsetGenerator();

	void setOffset(float offset);

	bool allowOffsetEditor() { return true; }
	bool allowFrequencyEditor() { return false; }
	bool allowWavelengthEditor() { return false; }
	bool allowAmplitudeEditor() { return false; }

protected:
	virtual float waveFunction(float distance) const override;

	float offset;
};

class WavelengthGenerator : public WaveGenerator {

};

class FrequencyGenerator : public WaveGenerator {

};

class EditableGenertaor : public WaveGenerator {

};

class ColorGenerator : public WaveGenerator {
public:
	enum class EmitterColor {
		Red,
		Green,
		Blue
	};

	ColorGenerator(sf::Texture const& texture, std::string const& file);
	ColorGenerator(sf::Texture const& texture, std::string const& file, EmitterColor emitter_color);
	~ColorGenerator() {};

	sf::Color colorAt(sf::Vector2f pos) const;

	void setGeneratorColor(EmitterColor color);
	sf::Color getGeneratorColor();

protected:
	virtual float waveFunction(float distance) const override;

	EmitterColor color_emit;
};
