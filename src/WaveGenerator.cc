#include "WaveGenerator.h"
#include <cmath>


WaveGenerator::WaveGenerator(sf::Texture &texture):
	frequency(1.f),
	amplitude(1.f),
	angle(0.f),
	SpriteNode(texture)
	
{}

WaveGenerator::WaveGenerator(sf::Texture &texture, float amplitude, float frequency)
	frequency(frequency),
	amplitude(amplitude),
	angle(0.f),
	SpriteNode(texture)
{}

WaveGenerator::~WaveGenerator() {

}

void WaveGenerator::setAngle(float angle) {
	angle = angle;
}

void WaveGenerator::updateCurrent(sf::Time dt) {
	
}

void WaveGenerator::drawCurrent() const {

}

float WaveGenerator::amplitudeAt(sf::Vector2f pos) {
	float distance = sqrt(pos.x*pos.x + pos.y*pos.y);
	float ampTarget = 0;	

	ampTarget = amplitude * sin(waveNumber*distance - angle);

	return ampTarget;
}
