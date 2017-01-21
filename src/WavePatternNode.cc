#include "WavePatternNode.h"
#include "WaveGenerator.h"

WavePatternNode::WavePatternNode(const std::string& shader_file, const std::vector<WaveGenerator*>& generator_list,
	sf::Color color1, sf::Color color2, sf::Color color3) :
	mGeneratorList(generator_list),
	mRect(sf::Vector2f(1920, 1080)),
	mColor1(color1),
	mColor2(color2),
	mColor3(color3)
{
	mShader.loadFromFile(shader_file, sf::Shader::Fragment);
}

void WavePatternNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates /*states*/) const {
	target.draw(mRect, &mShader);
}

void WavePatternNode::updateCurrent(sf::Time dt) {
	for (std::size_t i = 0; i < mGeneratorList.size(); ++i) {
		std::string num = std::to_string(i+1);
		if (mGeneratorList[i]->isPlaced()) {
			mShader.setUniform("source_pos" + num, sf::Glsl::Vec2(mGeneratorList[i]->getWorldPosition()));
			mShader.setUniform("amplitude" + num, mGeneratorList[i]->getAmplitude());
			mShader.setUniform("frequency" + num, mGeneratorList[i]->getFrequency());
			mShader.setUniform("wavelength" + num, mGeneratorList[i]->getWavelength());
		}
		else {
			mShader.setUniform("amplitude" + num, 0.0f);
		}
	}

	mShader.setUniform("color1", sf::Glsl::Vec4(mColor1));
	mShader.setUniform("color2", sf::Glsl::Vec4(mColor2));
	mShader.setUniform("color3", sf::Glsl::Vec4(mColor3));

	mElapsedTime += dt;
	mShader.setUniform("time", mElapsedTime.asSeconds());
}

