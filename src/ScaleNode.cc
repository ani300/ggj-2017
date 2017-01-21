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
	mShader.loadFromFile(vertex_file, sf::Shader::Vertex);
	mShader.loadFromFile(fragment_file, sf::Shader::Fragment);
	mShader.setUniform("min_scale_y", -280/2);
	mShader.setUniform("max_scale_y", +280/2);
	mShader.setUniform("color1", sf::Glsl::Vec4(mColor1));
	mShader.setUniform("color2", sf::Glsl::Vec4(mColor2));
	mShader.setUniform("color3", sf::Glsl::Vec4(mColor3));
	mOutRect.setFillColor(sf::Color(1.0,1.0,1.0,1.0)); // Change to a nice drawing!!!
}

void ScaleNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mOutRect, states);
	target.draw(mScaleRect, &mShader);
	//target.draw(mScaleRect, states);
}

void ScaleNode::updateCurrent(sf::Time /*dt*/) {
	mShader.setUniform("globalCoords", sf::Glsl::Vec2(getWorldPosition()));
}
