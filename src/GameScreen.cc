/*********************************GameScreen.cc***********************************/
#include "GameScreen.h"
#include "AnimationNode.h"
#include "GridNode.h"
#include "Receiver.h"
#include "ReceiverAlwaysOn.h"
#include "ReceiverAlwaysOff.h"
#include "ReceiverAmplitude.h"
#include "WaveGenerator.h"
#include "WavePatternNode.h"
#include "ScaleNode.h"
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

	getContext().mMusic->stop();

	generator_name_map["StandardGenerator"] = GeneratorTypes::Standard;
	generator_name_map["FrequencyGenerator"] = GeneratorTypes::Frequency;
	generator_name_map["WavelengthGenerator"] = GeneratorTypes::Wavelength;
	generator_name_map["AmplitudeGenerator"] = GeneratorTypes::Amplitude;
	generator_name_map["EditableGenerator"] = GeneratorTypes::Editable;

	receiver_name_map["Threshold"] = ReceiverTypes::Threshold;
	receiver_name_map["AlwaysOn"] = ReceiverTypes::AlwaysOn;
	receiver_name_map["AlwaysOff"] = ReceiverTypes::AlwaysOff;

	level_files_map[Levels::Level1] = "res/levels/level1.lua";
	level_files_map[Levels::Level2] = "res/levels/level2.lua";

	mMusicConfigs[MusicState::Off]     = {0,0,0,0,0,0,0,0,0};
	mMusicConfigs[MusicState::Base3]   = {1,0,0,0,0,0,0,0,0}; 
	mMusicConfigs[MusicState::Base4]   = {0,1,0,0,0,0,0,0,0};
	mMusicConfigs[MusicState::T4On]    = {0,1,1,1,1,1,0,0,0};
	mMusicConfigs[MusicState::T2Harm]  = {0,1,1,1,0,0,0,0,0};
	mMusicConfigs[MusicState::T4Harm1] = {0,1,1,0,0,0,0,0,0}; 
	mMusicConfigs[MusicState::T4Harm2] = {0,1,1,1,0,0,0,0,0};
	mMusicConfigs[MusicState::T4Mel1]  = {0,1,1,1,1,0,0,0,0};
	mMusicConfigs[MusicState::T3Mel1]  = {1,0,0,0,0,0,1,0,0};
	mMusicConfigs[MusicState::T3Mel2]  = {1,0,0,0,0,0,1,1,0};
	mMusicConfigs[MusicState::T3On]    = {1,0,0,0,0,0,1,1,1};
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

	MusicState old_state = mMusicState;
	updateMusicState();

	if (old_state != mMusicState) {
		std::cout << "Music changed! " << static_cast<int>(mMusicState) << std::endl;
		// Update playing music accordingly
		auto is_playing = [this](int player) -> bool {
			return getContext().mMusic->getMusicPlayer(player).getStatus() == sf::SoundSource::Playing;
		};

		// Base3T
		if (mMusicConfigs[mMusicState][0] && !is_playing(0)) {
			getContext().mMusic->play(0, Music::Game3TBase);
		}
		else if (!mMusicConfigs[mMusicState][0] && !mMusicConfigs[mMusicState][0] && is_playing(0)) {
			getContext().mMusic->stop();
		}
		
		// Base4T
		if (mMusicConfigs[mMusicState][1] && !is_playing(0)) {
			getContext().mMusic->play(0, Music::Game4TBase);
		}
		else if (!mMusicConfigs[mMusicState][1] && !mMusicConfigs[mMusicState][0] && is_playing(0)) {
			getContext().mMusic->stop();
		}

		// Harm1-4T
		if (mMusicConfigs[mMusicState][2] && !is_playing(1)) {
			getContext().mMusic->play(1, Music::Game4THarm1);
			getContext().mMusic->getMusicPlayer(1).setPlayingOffset(getContext().mMusic->getMusicPlayer(0).getPlayingOffset());
		}
		else if (!mMusicConfigs[mMusicState][2] && is_playing(1)) {
			getContext().mMusic->getMusicPlayer(1).stop();
		}

		// Harm2-4T
		if (mMusicConfigs[mMusicState][3] && !is_playing(2)) {
			getContext().mMusic->play(2, Music::Game4THarm2);
			getContext().mMusic->getMusicPlayer(2).setPlayingOffset(getContext().mMusic->getMusicPlayer(0).getPlayingOffset());
		}
		else if (!mMusicConfigs[mMusicState][3] && is_playing(2)) {
			getContext().mMusic->getMusicPlayer(2).stop();
		}

		// Mel1-4T
		if (mMusicConfigs[mMusicState][4] && !is_playing(3)) {
			getContext().mMusic->play(3, Music::Game4TMel1);
			getContext().mMusic->getMusicPlayer(3).setPlayingOffset(getContext().mMusic->getMusicPlayer(0).getPlayingOffset());
		}
		else if (!mMusicConfigs[mMusicState][4] && is_playing(3)) {
			getContext().mMusic->getMusicPlayer(3).stop();
		}

		// Mel2-4T
		if (mMusicConfigs[mMusicState][5] && !is_playing(4)) {
			getContext().mMusic->play(4, Music::Game4TMel2);
			getContext().mMusic->getMusicPlayer(4).setPlayingOffset(getContext().mMusic->getMusicPlayer(0).getPlayingOffset());
		}
		else if (!mMusicConfigs[mMusicState][5] && is_playing(4)) {
			getContext().mMusic->getMusicPlayer(4).stop();
		}
		
		// Mel1-3T
		if (mMusicConfigs[mMusicState][6] && !is_playing(1)) {
			getContext().mMusic->play(1, Music::Game3TMel1);
			getContext().mMusic->getMusicPlayer(1).setPlayingOffset(getContext().mMusic->getMusicPlayer(0).getPlayingOffset());
		}
		else if (!mMusicConfigs[mMusicState][6] && is_playing(1)) {
			getContext().mMusic->getMusicPlayer(1).stop();
		}

		// Mel2-3T
		if (mMusicConfigs[mMusicState][7] && !is_playing(2)) {
			getContext().mMusic->play(2, Music::Game3TMel2);
			getContext().mMusic->getMusicPlayer(2).setPlayingOffset(getContext().mMusic->getMusicPlayer(0).getPlayingOffset());
		}
		else if (!mMusicConfigs[mMusicState][7] && is_playing(2)) {
			getContext().mMusic->getMusicPlayer(2).stop();
		}

		// Mel3-3T
		if (mMusicConfigs[mMusicState][8] && !is_playing(3)) {
			getContext().mMusic->play(3, Music::Game3TMel3);
			getContext().mMusic->getMusicPlayer(3).setPlayingOffset(getContext().mMusic->getMusicPlayer(0).getPlayingOffset());
		}
		else if (!mMusicConfigs[mMusicState][8] && is_playing(3)) {
			getContext().mMusic->getMusicPlayer(3).stop();
		}

	}

	mSceneGraph.update(dt);
	return true;
}


void GameScreen::handleRealtimeInput() {
	if (mSelectedGenerator != -1) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*getContext().mWindow);
		sf::Vector2i newPos = Utils::correctMouse(mousePos, getContext().mScale);
		generators[mSelectedGenerator]->setPosition(sf::Vector2f(newPos));
		if((mToolbox->getBounds()).contains(newPos)) {
			generators[mSelectedGenerator]->place(false);
		}
		else
		{
			generators[mSelectedGenerator]->place(true);
		}
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

void GameScreen::updateMusicState() {

	// Count if > 0 sources
	bool any_source = false;
	for (auto const* generator : generators) {
		if (generator->isPlaced()) {
			any_source = true;
		}
	}

	if (!any_source) {
		mMusicState = MusicState::Off;
	}
	else {
		// Count working receivers
		int num_working_receivers = 0;
		for(const auto& r: receivers) {
			if(r->getState()) {
				++num_working_receivers;
			}
		}

		if (receivers.size() == 1) {
			if (num_working_receivers == 1) {
				mMusicState = MusicState::T4On;
			}
			else {
				mMusicState = MusicState::Base4;
			}
		}
		else if (receivers.size() == 2) {
			if (num_working_receivers == 1) {
				mMusicState = MusicState::T2Harm;
			}
			else if (num_working_receivers == 2) {
				mMusicState = MusicState::T4On;
			}
			else {
				mMusicState = MusicState::Base4;
			}
		}
		else if (receivers.size() == 3) {
			if (num_working_receivers == 1) {
				mMusicState = MusicState::T3Mel1;
			}
			else if (num_working_receivers == 2) {
				mMusicState = MusicState::T3Mel2;
			}
			else if (num_working_receivers == 3) {
				mMusicState = MusicState::T3On;
			}
			else {
				mMusicState = MusicState::Base3;
			}
		}
		else if (receivers.size() == 4) {
			if (num_working_receivers == 1) {
				mMusicState = MusicState::T4Harm1;
			}
			else if (num_working_receivers == 2) {
				mMusicState = MusicState::T4Harm2;
			}
			else if (num_working_receivers == 3) {
				mMusicState = MusicState::T4Mel1;
			}
			else if (num_working_receivers == 4) {
				mMusicState = MusicState::T4On;
			}
			else {
				mMusicState = MusicState::Base4;
			}
		}
	}
}

sf::Vector2f GameScreen::snapGrid(sf::Vector2f pos, sf::Vector2i grid_size) {
	return snapGrid(pos, sf::Vector2f(grid_size.x, grid_size.y));
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
			sf::Vector2i mousePos = sf::Mouse::getPosition(*getContext().mWindow);
			sf::Vector2i newPos = Utils::correctMouse(mousePos, getContext().mScale);

			if (mSelectedGenerator >= 0) {
				if((mToolbox->getBounds()).contains(newPos)) {
					generators[mSelectedGenerator]->setPosition(toolboxOffset.x, toolboxOffset.y - toolboxSize.y/2 + toolboxMargin.y*(mSelectedGenerator+1));
				}
				else {
					generators[mSelectedGenerator]->setPosition(snapGrid(sf::Vector2f(newPos), sf::Vector2f(60, 60)));	
				}
			}
			mSelectedGenerator = -1;
		}
	}
	return true;
}

void GameScreen::setLevel(Levels level) {
	level = level;

	getContext().mGameData->currentLevel = level;

	lua.script_file(level_files_map[level]);
	rgb = lua["rgb"];
	time = lua["time"];

	sol::optional<int> grid_size_x = lua["grid"]["size"][1];
	sol::optional<int> grid_size_y = lua["grid"]["size"][2];
	sf::Vector2i grid_size = sf::Vector2i(grid_size_x.value_or(60), grid_size_y.value_or(60));


	sol::table rec = lua["receivers"];
	for(auto a: rec) {
		auto table = a.second.as<sol::table>();
		sol::optional<std::string> o_type = table["type"];
		std::string type = o_type.value_or("AlwaysOn");

		sol::optional<float> positionx = table["position"][1];
		sol::optional<float> positiony = table["position"][2];

		sf::Vector2f position = sf::Vector2f(positionx.value_or(0), positiony.value_or(0));
		position = snapGrid(position, grid_size);



		auto rec_type = receiver_name_map[type];

		switch(rec_type) {
			case ReceiverTypes::AlwaysOn:
				{
					auto receiver = std::make_unique<ReceiverAlwaysOn>(mContext.mTextures->get(Textures::ReceiverAlwaysOn), generators);
					receiver->setPosition(position);
					receivers.push_back(receiver.get());
					mSceneLayers[static_cast<int>(Layer::Nodes)]->attachChild(std::move(receiver));
				}
				break;
			case ReceiverTypes::AlwaysOff:
				{
					auto receiver = std::make_unique<ReceiverAlwaysOff>(mContext.mTextures->get(Textures::ReceiverAlwaysOn), generators);
					receiver->setPosition(position);
					receivers.push_back(receiver.get());
					mSceneLayers[static_cast<int>(Layer::Nodes)]->attachChild(std::move(receiver));
				}
				break;
			case ReceiverTypes::Threshold:
				{
					sol::optional<sol::function> maybe_threshold_fn = table["threshold_fn"];
					if(!maybe_threshold_fn) {
						std::cout << "Your function sucks" << std::endl;	
					} 
					sol::function threshold_fn = maybe_threshold_fn.value();

					auto receiver = std::make_unique<ReceiverAmplitude>(mContext.mTextures->get(Textures::ReceiverAlwaysOn), generators, std::move(threshold_fn));
					receiver->setPosition(position);
					receivers.push_back(receiver.get());
					mSceneLayers[static_cast<int>(Layer::Nodes)]->attachChild(std::move(receiver));
				}
				break;
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

	//Dynamic toolbox dimensions based on generators size
	sf::Texture& toolboxTexture = getContext().mTextures->get(Textures::ToolboxBackground);

	std::unique_ptr<SpriteNode> toolbox(new SpriteNode(toolboxTexture));
	mToolbox = toolbox.get();
	mToolbox->setPosition(toolboxOffset.x, toolboxOffset.y);
	toolboxSize.y = (generator_index + 1)*toolboxMargin.y;
	mToolbox->setSize(sf::Vector2u(toolboxSize.x, toolboxSize.y));
	mSceneLayers[static_cast<int>(Layer::UI)]->attachChild(std::move(toolbox));

	for(int i = 0; i < generator_index; i++)
	{
		generators[i]->setPosition(sf::Vector2f(toolboxOffset.x, toolboxOffset.y - toolboxSize.y/2 + toolboxMargin.y*(i+1)));
	}


	auto pos_color = lua["colors"]["positive_amp"];
	auto zero = lua["colors"]["zero"];
	auto neg_color = lua["colors"]["negative_amp"];
	auto g_color = lua["grid"]["color"];

	sf::Color color1(neg_color["r"],neg_color["g"],neg_color["b"],neg_color["a"]);
	sf::Color color2(zero["r"],zero["g"],zero["b"],zero["a"]);
	sf::Color color3(pos_color["r"],pos_color["g"],pos_color["b"],pos_color["a"]);
	sf::Color grid_color(g_color["r"],g_color["g"],g_color["b"],g_color["a"]);

	auto wave_pattern = std::make_unique<WavePatternNode>("res/shaders/sine_waves.frag", generators, color1, color2, color3);
	mSceneLayers[static_cast<int>(Layer::WavePattern)]->attachChild(std::move(wave_pattern));

	auto grid = std::make_unique<GridNode>(grid_size, grid_color);	
	mSceneLayers[static_cast<int>(Layer::Grid)]->attachChild(std::move(grid));

	auto color_scale = std::make_unique<ScaleNode>("res/shaders/scale.vert", "res/shaders/scale.frag", color1, color2, color3);
	ScaleNode* scale_node = color_scale.get();
	mSceneLayers[static_cast<int>(Layer::UI)]->attachChild(std::move(color_scale));
	scale_node->setPosition(sf::Vector2f(1850, 890));
}
