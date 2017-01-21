#include "WaveGenerator.h"
#include <cmath>
#include <stdlib.h>


WaveGenerator::WaveGenerator(sf::Texture const& texture, std::string const& file) :
	AnimationNode(texture, file),
	frequency(0.5f),
	wavelength(60.f),
	amplitude(1.f),
	angle(0.f)
{}

WaveGenerator::WaveGenerator(sf::Texture const& texture, std::string const& file, float amplitude, float frequency, float wavelength) :
	AnimationNode(texture, file),
	frequency(frequency),
	wavelength(wavelength),
	amplitude(amplitude),
	angle(0.f)
{}

WaveGenerator::~WaveGenerator() {

}

void WaveGenerator::setAngle(float angle) {
	angle = angle;
}

void WaveGenerator::updateCurrent(sf::Time dt) {
	this->move(sf::Vector2f(rand() % 3 - 1, rand() % 3 - 1));
}

float WaveGenerator::amplitudeAt(sf::Vector2f pos) const {
	float distance = sqrt(pos.x*pos.x + pos.y*pos.y);
	float ampTarget = 0;

	ampTarget = amplitude * sin(waveNumber*distance - angle);

	return ampTarget;
}

bool WaveGenerator::isPlaced() const {
	return true;
}
