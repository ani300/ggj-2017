#include "WaveGenerator.h"
#include <cmath>



WaveGenerator::WaveGenerator(sf::Texture const& texture, std::string const& file) :
	AnimationNode(texture, file),
	frequency(1.f),
	amplitude(1.f),
	angle(0.f)
{}

WaveGenerator::WaveGenerator(sf::Texture const& texture, std::string const& file, float amplitude, float frequency) :
	AnimationNode(texture, file),
	frequency(frequency),
	amplitude(amplitude),
	angle(0.f)
{}

WaveGenerator::~WaveGenerator() {

}

void WaveGenerator::setAngle(float angle) {
	angle = angle;
}

void WaveGenerator::updateCurrent(sf::Time dt) {
	
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
