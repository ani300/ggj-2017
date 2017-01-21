/*********************************GameScreen.cc***********************************/
#include "GameScreen.h"
#include "AnimationNode.h"
#include "GridNode.h"
#include "Receiver.h"
#include "ReceiverAlwaysOn.h"
#include "ReceiverAlwaysOff.h"
#include "WaveGenerator.h"
#include "WavePatternNode.h"

GameScreen::GameScreen(StatesStack& stack, Context& context) :
	State(stack, context),
	mSelectedGenerator(-1)
{
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layer::Count); ++i) {
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}
	// TODO: read level data from files
	std::vector<sf::Vector2f> receivers_positions = std::vector<sf::Vector2f>(1);
	int num_generators;

	// HARDCODED DATA FOR NOW
	num_generators = 3;
	receivers_positions[0] = sf::Vector2f(400, 200);

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
		auto receiver = std::make_unique<ReceiverAlwaysOff>(context.mTextures->get(Textures::ReceiverAlwaysOn), generators);
		receivers.push_back(receiver.get());
		receivers.back()->setPosition(v);
		mSceneLayers[static_cast<int>(Layer::Nodes)]->attachChild(std::move(receiver));
	}

	auto wave_pattern = std::make_unique<WavePatternNode>("res/shaders/sine_waves.frag", generators);
	mSceneLayers[static_cast<int>(Layer::WavePattern)]->attachChild(std::move(wave_pattern));

	auto grid = std::make_unique<GridNode>(sf::Vector2i(60,60), sf::Color(255,0,0,128));	
	mSceneLayers[static_cast<int>(Layer::Grid)]->attachChild(std::move(grid));
}

void GameScreen::draw() {
	getContext().mRTexture->draw(mSceneGraph);
}

bool GameScreen::isLevelCompleted() {
	for(const auto& r: receivers) {
		if(!r->getState()) {
			return false;
		}
	}
	return true;
}

bool GameScreen::update(sf::Time dt) {
	handleRealtimeInput();
	if(isLevelCompleted()) {
		requestStackPush(StateType::Result);
	}
	mSceneGraph.update(dt);
	return true;
}

void GameScreen::handleRealtimeInput() {
	if (mSelectedGenerator != -1) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*getContext().mWindow);
		sf::Vector2i newPos = Utils::correctMouse(mousePos, getContext().mScale);
		generators[mSelectedGenerator]->setPosition(snapGrid(sf::Vector2f(newPos), sf::Vector2f(60, 60)));
	}
}

sf::Vector2f GameScreen::snapGrid(sf::Vector2f pos, sf::Vector2f grid_size) {
	int x_free = int(pos.x)%int(grid_size.x);
	int y_free = int(pos.y)%int(grid_size.y);
	int x_base = pos.x - x_free;
	int y_base = pos.y - y_free;
	if (x_free < grid_size.x/2) {
		if (y_free < grid_size.y/2) {
			return sf::Vector2f(x_base, y_base);
		}
		else {
			return sf::Vector2f(x_base, y_base + grid_size.y);
		}
	}
	else {
		if (y_free < grid_size.y/2) {
			return sf::Vector2f(x_base + grid_size.x, y_base);
		}
		else {
			return sf::Vector2f(x_base + grid_size.x, y_base + grid_size.y);
		}
	}
}

bool GameScreen::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			// Check if clicking on a generator
			sf::Vector2i mousePos = sf::Mouse::getPosition(*getContext().mWindow);
			sf::Vector2i newPos = Utils::correctMouse(mousePos, getContext().mScale);
			for (int i = 0; i < generators.size(); ++i) {
				sf::IntRect generator_bounds = generators[i]->getBounds();
				if (generator_bounds.contains(newPos)) {
					mSelectedGenerator = i;
				}
			}
		}
	}
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			mSelectedGenerator = -1;
		}
	}
	return true;
}
