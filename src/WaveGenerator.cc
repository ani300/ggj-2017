#include "WaveGenerator.h"
#include <cmath>


WaveGenerator::WaveGenerator(sf::Texture &texture):
	SpriteNode(texture),
	frequency(1.f),
	amplitude(1.f),
	angle(0.f)
	
{}

WaveGenerator::WaveGenerator(sf::Texture &texture, float amplitude, float frequency):
	SpriteNode(texture),
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

void WaveGenerator::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

}

float WaveGenerator::amplitudeAt(sf::Vector2f pos) const {
	float distance = sqrt(pos.x*pos.x + pos.y*pos.y);
	float ampTarget = 0;	

	ampTarget = amplitude * sin(waveNumber*distance - angle);

	return ampTarget;
}

bool WaveGenerator::isPlaced() const {
	return placed;
}
