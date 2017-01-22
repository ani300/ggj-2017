#include "WaveGenerator.h"
#include "Utils.h"
#include <cmath>
#include <stdlib.h>


WaveGenerator::WaveGenerator(sf::Texture const& texture, std::string const& file) :
	AnimationNode(texture, file),
	frequency(0.5f),
	wavelength(90.f),
	amplitude(1.f),
	angle(0.f),
	placed(false)
{}

WaveGenerator::WaveGenerator(sf::Texture const& texture, std::string const& file, float amplitude, float frequency, float wavelength) :
	AnimationNode(texture, file),
	frequency(frequency),
	wavelength(wavelength),
	amplitude(amplitude),
	angle(0.f),
	placed(false)
{}

WaveGenerator::~WaveGenerator() {

}

void WaveGenerator::setAngle(float angle) {
	angle = angle;
}

void WaveGenerator::updateCurrent(sf::Time dt) {
	AnimationNode::updateCurrent(dt);
	angle += frequency*2*M_PI*dt.asSeconds();
}

float WaveGenerator::amplitudeAt(sf::Vector2f pos) const {
	sf::Vector2f genPos = getWorldPosition();
	float distance = Utils::distance(genPos, pos);

	return waveFunction(distance);
}

float WaveGenerator::waveFunction(float distance) const {
	return amplitude*sin(2*M_PI/wavelength*distance + angle);
}

bool WaveGenerator::isPlaced() const {
	return placed;
}

void WaveGenerator::place(bool p) {
	placed = p;
}




float StandardGenerator::waveFunction(float distance) const {
	return amplitude*sin(2*M_PI/wavelength*distance + angle);
}

float OffsetGenerator::waveFunction(float distance) const {
	return amplitude*sin(2*M_PI/wavelength*distance + angle) + offset;
}

