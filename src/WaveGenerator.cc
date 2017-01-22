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

void WaveGenerator::onHover(){
	std::cout << "On hover" << std::endl;
}

void WaveGenerator::onHoverOut(){
	std::cout << "On hover out" << std::endl;
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


ColorGenerator::ColorGenerator(sf::Texture const& texture, std::string const& file) 
	: WaveGenerator(texture, file),
	color_emit(EmitterColor::Red)
{
}

ColorGenerator::ColorGenerator(sf::Texture const& texture, std::string const& file, EmitterColor color)
	: WaveGenerator(texture, file),
	color_emit(color)
{
}

std::array<int, 4> ColorGenerator::colorAt(sf::Vector2f pos) const {
	sf::Vector2f genPos = getWorldPosition();
	float distance = Utils::distance(genPos, pos);

	float colorValue = waveFunction(distance);
	colorValue = colorValue*255;

	std::array<int, 4> color_val = {0,0,0,255};

	switch(color_emit) {
	case EmitterColor::Red:
		color_val[0] = colorValue;
		break;
	case EmitterColor::Green:
		color_val[1] = colorValue;
		break;
	case EmitterColor::Blue:
		color_val[2] = colorValue;
		break;
	}

	return color_val;
}

float ColorGenerator::waveFunction(float distance) const {
	return 1.f/2.f*sin(2*M_PI/wavelength*distance + angle);
}

void ColorGenerator::setGeneratorColor(EmitterColor color) {
	color_emit = color;
}

sf::Color ColorGenerator::getGeneratorColor() {
	switch(color_emit) {
	case EmitterColor::Red:
		return sf::Color::Red;

	case EmitterColor::Green:
		return sf::Color::Green;

	case EmitterColor::Blue:
		return sf::Color::Blue;
	}

	return sf::Color::White;
}
