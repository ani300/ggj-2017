/*********************************GameScreen.cc***********************************/
#include "GameScreen.h"
#include "AnimationNode.h"
#include "Receiver.h"
#include "ReceiverAlwaysOn.h"
#include "WaveGenerator.h"
#include "WavePatternNode.h"

GameScreen::GameScreen(StatesStack& stack, Context& context)
	: State(stack, context)
{
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layer::Count); ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }
	// TODO: read level data from files
	std::vector<sf::Vector2f> receivers_positions = std::vector<sf::Vector2f>(3);
	int num_generators;

	// HARDCODED DATA FOR NOW
	num_generators = 3;
	receivers_positions[0] = sf::Vector2f(40, 40);
	receivers_positions[1] = sf::Vector2f(200, 400);
	receivers_positions[2] = sf::Vector2f(400, 200);

	for(int i = 0; i < num_generators; ++i) {
		auto generator = std::make_unique<WaveGenerator>(context.mTextures->get(Textures::WaveGenerator), 
					"res/anim/generator.anim");
		generators.push_back(generator.get());
		mSceneLayers[static_cast<int>(Layer::Nodes)]->attachChild(std::move(generator));
	}
	generators[0]->setPosition(sf::Vector2f(200,200));
	generators[0]->setSize(sf::Vector2u(90, 90));
	generators[0]->setAnimation("Generator");
	generators[1]->setPosition(sf::Vector2f(750,979));
	generators[1]->setSize(sf::Vector2u(90, 90));
	generators[1]->setAnimation("Generator");
	generators[2]->setPosition(sf::Vector2f(1200,200));
	generators[2]->setSize(sf::Vector2u(90, 90));
	generators[2]->setAnimation("Generator");

	for(auto v: receivers_positions) {
		auto receiver = std::make_unique<ReceiverAlwaysOn>(context.mTextures->get(Textures::ReceiverAlwaysOn), generators);
		receivers.push_back(receiver.get());
		mSceneLayers[static_cast<int>(Layer::Nodes)]->attachChild(std::move(receiver));
	}

	auto wave_pattern = std::make_unique<WavePatternNode>("res/shaders/sine_waves.frag", generators);
	mSceneLayers[static_cast<int>(Layer::WavePattern)]->attachChild(std::move(wave_pattern));	
}

void GameScreen::draw() {
	getContext().mRTexture->draw(mSceneGraph);
}

bool GameScreen::isLevelCompleted(){
	for(const auto&  r: receivers){
		if(not r->getState()) {
			return false;
		}
	}

	return true;
}

bool GameScreen::update(sf::Time dt) {
	mSceneGraph.update(dt);
	if(isLevelCompleted()) {
		requestStackPush(StateType::Result);
	}

	return true;
}

bool GameScreen::handleEvent(const sf::Event& event) {
	return true;
}
