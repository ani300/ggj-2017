#include "ScaleNode.h"

ScaleNode::ScaleNode(std::string const& vertex_file, std::string const& fragment_file, 
	sf::Color color1, sf::Color color2, sf::Color color3) :
	mOutRect(sf::Vector2f(60, 300)),
	mScaleRect(sf::Vector2f(50, 280)),
	mColor1(color1),
	mColor2(color2),
	mColor3(color3)
{
	Utils::centerOrigin(mOutRect);
	Utils::centerOrigin(mScaleRect);
	mShader.loadFromFile(vertex_file, fragment_file);
	mShader.setUniform("color1", sf::Glsl::Vec4(mColor1));
	mShader.setUniform("color2", sf::Glsl::Vec4(mColor2));
	mShader.setUniform("color3", sf::Glsl::Vec4(mColor3));
	mOutRect.setFillColor(sf::Color(1.0,1.0,1.0,1.0)); // Change to a nice drawing!!!
}

void ScaleNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mOutRect, states);
	states.shader = &mShader;
	target.draw(mScaleRect, states);
	//target.draw(mScaleRect, states);
}

void ScaleNode::updateCurrent(sf::Time /*dt*/) {
	mShader.setUniform("min_scale_y", 1080 - (getWorldPosition().y - 290/2));
	mShader.setUniform("max_scale_y", 1080 - (getWorldPosition().y + 290/2));
	//std::cout << getWorldPosition().y - 290/2 << " " << getWorldPosition().y + 290/2 << std::endl;
}
