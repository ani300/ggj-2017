/*********************************GameScreen.cc***********************************/
#include "GameScreen.h"
#include "AnimationNode.h"
#include "Receiver.h"
#include "WaveGenerator.h"

GameScreen::GameScreen(int level_number, StatesStack& stack, Context& context)
	: State(stack, context)
{
	// TODO: read level data from files
	std::vector<sf::Vector2f> receivers_positions = std::vector<sf::Vector2f>(3);
	int num_generators;

	// HARDCODED DATA FOR NOW
	num_generators = 3;
	receivers_positions[0] = sf::Vector2f(40, 40);
	receivers_positions[1] = sf::Vector2f(200, 400);
	receivers_positions[2] = sf::Vector2f(400, 200);

	for(int i = 0; i < num_generators; ++i) {
		WaveGenerator *generator = new WaveGenerator();
		generators.push_back(generator);
	}

	for(auto v: receivers_positions) {
		Receiver *receiver = new AlwaysOnReceiver(&generators);
	}
}

void GameScreen::draw() {
	getContext().mRTexture->draw(mSceneGraph);
}

bool GameScreen::update(sf::Time dt) {
	return true;
}

bool GameScreen::handleEvent(const sf::Event& event) {
	return true;
}
