#include "WavePatternNode.h"
#include "WaveGenerator.h"

WavePatternNode::WavePatternNode(const std::string& shader_file, const std::vector<WaveGenerator*>& generator_list) :
	mGeneratorList(generator_list),
	mRect(sf::Vector2f(1920, 1080))
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

	mShader.setUniform("color_min", sf::Glsl::Vec4(sf::Color(0,0,128,255)));
	mShader.setUniform("color_max", sf::Glsl::Vec4(sf::Color(0,190,255,255)));

	mElapsedTime += dt;
	//mShader.setUniform("time", mElapsedTime.asSeconds());
}

