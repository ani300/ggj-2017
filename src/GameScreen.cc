/*********************************GameScreen.cc***********************************/
#include "GameScreen.h"
#include "AnimationNode.h"
#include "GridNode.h"
#include "Receiver.h"
#include "ReceiverAlwaysOn.h"
#include "ReceiverAlwaysOff.h"
#include "WaveGenerator.h"
#include "WavePatternNode.h"
#include "sol/sol.h"

GameScreen::GameScreen(StatesStack& stack, Context& context) :
	State(stack, context),
	mSelectedGenerator(-1)
{
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layer::Count); ++i) {
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	auto wave_pattern = std::make_unique<WavePatternNode>("res/shaders/sine_waves.frag", generators);
	mSceneLayers[static_cast<int>(Layer::WavePattern)]->attachChild(std::move(wave_pattern));

	auto grid = std::make_unique<GridNode>(sf::Vector2i(60,60), sf::Color(255,0,0,128));	
	mSceneLayers[static_cast<int>(Layer::Grid)]->attachChild(std::move(grid));

	generator_name_map["StandardGenerator"] = GeneratorTypes::Standard;
	generator_name_map["FrequencyGenerator"] = GeneratorTypes::Frequency;
	generator_name_map["WavelengthGenerator"] = GeneratorTypes::Wavelength;
	generator_name_map["AmplitudeGenerator"] = GeneratorTypes::Amplitude;
	generator_name_map["EditableGenerator"] = GeneratorTypes::Editable;


	receiver_name_map["Threshold"] = ReceiverTypes::Threshold;
	receiver_name_map["AlwaysOn"] = ReceiverTypes::AlwaysOn;
	receiver_name_map["AlwaysOff"] = ReceiverTypes::AlwaysOff;
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
		generators[mSelectedGenerator]->setPosition(sf::Vector2f(newPos));
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
			for (std::size_t i = 0; i < generators.size(); ++i) {
				sf::IntRect generator_bounds = generators[i]->getBounds();
				if (generator_bounds.contains(newPos)) {
					mSelectedGenerator = i;
				}
			}
		}
	}
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (mSelectedGenerator >= 0) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(*getContext().mWindow);
				sf::Vector2i newPos = Utils::correctMouse(mousePos, getContext().mScale);
				generators[mSelectedGenerator]->setPosition(snapGrid(sf::Vector2f(newPos), sf::Vector2f(60, 60)));	
			}
			mSelectedGenerator = -1;
		}
	}
	return true;
}

void GameScreen::setLevel(Levels level) {
	level = level;

	sol::state lua;	

	lua.script_file("res/levels/level1.lua");
	rgb = lua["rgb"];
	time = lua["time"];

	sol::table rec = lua["receivers"];
	for(auto a: rec) {
		auto table = a.second.as<sol::table>();
		sol::optional<std::string> o_type = table["type"];
		std::string type = o_type.value_or("AlwaysOn");

		sol::optional<float> positionx = table["position"][1];
		sol::optional<float> positiony = table["position"][2];

		sf::Vector2f position = sf::Vector2f(positionx.value_or(0), positiony.value_or(0));

		sol::optional<int> threshold = table["threshold"];
		if(threshold)
			std::cout << threshold.value() << std::endl;

		sol::optional<std::string> comparator = table["comparator"];
		if(comparator)
			std::cout << comparator.value() << std::endl;

		sol::optional<bool> absolute = table["absolute"];
		if(absolute)
			std::cout << absolute.value() << std::endl;


		auto rec_type = receiver_name_map[type];

		switch(rec_type) {
			case ReceiverTypes::AlwaysOn:
				{
				auto receiver = std::make_unique<ReceiverAlwaysOff>(mContext.mTextures->get(Textures::ReceiverAlwaysOn), generators);
				receiver->setPosition(position);
				receivers.push_back(receiver.get());
				mSceneLayers[static_cast<int>(Layer::Nodes)]->attachChild(std::move(receiver));
				}
				break;
			case ReceiverTypes::AlwaysOff:
			case ReceiverTypes::Threshold:
			case ReceiverTypes::Count:
				break;
		}
	}

	sol::table gen = lua["generators"];
	int generator_index = 0;
	for(auto a: gen) {
		auto key = a.first.as<std::string>();
		auto value = a.second.as<int>();

		auto genType = generator_name_map[key];	

		for(int i = 0; i < value; ++i) {
			switch(genType) {
				case GeneratorTypes::Standard:
					{
					std::unique_ptr<WaveGenerator> generator = std::make_unique<WaveGenerator>(mContext.mTextures->get(Textures::WaveGenerator), "res/anim/generator.anim");
					generators.push_back(generator.get());
					generator->setPosition(sf::Vector2f(100, 200 + 120*generator_index));
					generator->setSize(sf::Vector2u(90,90));
					generator->setAnimation("Generator");
					mSceneLayers[static_cast<int>(Layer::Nodes)]->attachChild(std::move(generator));
					}
					break;
				case GeneratorTypes::Wavelength:
				case GeneratorTypes::Frequency:
				case GeneratorTypes::Amplitude:
				case GeneratorTypes::Editable:
				case GeneratorTypes::Count:
					break;
			}
			generator_index++;
		}

	}
}
