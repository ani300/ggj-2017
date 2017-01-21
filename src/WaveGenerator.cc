#include "WaveGenerator.h"
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
}

float WaveGenerator::amplitudeAt(sf::Vector2f pos) const {
	sf::Vector2f genPos = getWorldPosition();
	float dx = abs(genPos.x - pos.x);
	float dy = abs(genPos.y - pos.y);
	float distance = sqrt(dx*dx + dy*dy);
	float ampTarget = 0;

	ampTarget = amplitude * sin(waveNumber*distance - angle);

	return ampTarget;
}

bool WaveGenerator::isPlaced() const {
	return true;
}

void WaveGenerator::place(bool p) {
	placed = p;
}
