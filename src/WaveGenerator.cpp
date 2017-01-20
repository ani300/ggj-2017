#include "WaveGenerator.h"
#include <cmath>


WaveGenerator::WaveGenerator():
	frequency(1.f),
	amplitude(1.f)
	angle(0.f)
{}

WaveGenerator::WaveGenerator(float amplitude, float frequency)
	frequency(frequency),
	amplitude(amplitude),
	angle(0.f)
{}

WaveGenerator::~WaveGenerator() {

}

void WaveGenerator::setAngle(float angle) {
	angle = angle;
}

virtual WaveGenerator::updateCurrent(sf::Time dt) {
	
}

virtual WaveGenerator::drawCurrent() {

}

float WaveGenerator::amplitudeAt(sf::Vector2f pos) {
	float distance = sqrt(pos.x*pos.x + pos.y*pos.y);
	float ampTarget = 0;	

	ampTarget = amplitude * sin(waveNumber*distance - angle)

	return ampTarget;
}
