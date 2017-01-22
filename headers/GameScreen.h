/********************************GameScreen.h***************************************/
#pragma once

#include <unordered_map>

#include "Utils.h"
#include "State.h"
#include "SceneNode.h"
#include "TextNode.h"
#include "SpriteNode.h"
#include "InvisibleNode.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "WaveGenerator.h"
#include "Animator.h"
#include "sol/sol.h"

class WaveGenerator;
class Receiver;
class GameScreen: public State {

public:
	const float HOVER_TIME = 1.f;
	//Constructor with name of the image it wants to display
	GameScreen(StatesStack& stack, Context& context);


	void draw();
	bool update(sf::Time dt);
	bool handleEvent(const sf::Event& event);
	void setLevel(Levels level);

private:
	sol::state lua;

	void click(mouseButtons mouseButton, sf::Vector2f mouseClick);

	enum class Layer {
		Background,
		WavePattern,
		Grid,
		UI,
		Nodes,
		Text,
		Count
	};
	
	enum class GeneratorTypes {
		Standard,
		Wavelength,
		Frequency,
		Amplitude,
		Editable,
		Color,
		Count
	};

	enum class ReceiverTypes {
		Threshold,
		AlwaysOn,
		AlwaysOff,
		RGB,
		Count
	};

	enum class MusicState {
		Off,
		Base3,
		Base4,
		T4On,
		T2Harm,
		T4Harm1,
		T4Harm2,
		T4Mel1,
		T3Mel1,
		T3Mel2,
		T3On
	};

	bool isLevelCompleted();

	void handleRealtimeInput(sf::Time dt);

	void updateMusicState();
	void updateMusicPlayback();

	void changePlayingMusic();


	void tutorialFirstMessage();
	void tutorialFirstMessageOff();
	void showMessage(std::string title, std::string msg, sf::Vector2f pos, sf::Vector2f size);
	
	float secondsToHover = HOVER_TIME;
	//Scene child below the mouse
	int mouseOver = -1;
	bool hovering = false;
	sf::Vector2f oldPos = sf::Vector2f(0.f, 0.f);
	sf::Vector2i mousePos;
	sf::Vector2i newPos;
	sf::Vector2f newfpos;
	//Index is scenegraph children
	void handleOnHover(int index);
	void handleHoverOut(int index);

	//ANIMATIONS
	Animator animator;
	TextNode* tutorialTitle;
	TextNode* tutorialBody;
	float textOpacity = 1.f;
	float textLeft = -10.f;
	float timer = 5.f;
	bool firstMove = true;

	sf::Vector2f snapGrid(sf::Vector2f pos, sf::Vector2f grid_size);
	sf::Vector2f snapGrid(sf::Vector2f pos, sf::Vector2i grid_size);

	sf::Vector2f toolboxOffset = sf::Vector2f(100.f, 350.f);
	sf::Vector2f toolboxMargin = sf::Vector2f(0.f, 120.f);
	//Height is calculated based on generators number
	sf::Vector2f toolboxSize = sf::Vector2f(150.f, 600.f);
	SpriteNode* mToolbox;

	MusicState mMusicState = MusicState::Off;
	std::unordered_map<MusicState, std::vector<bool>> mMusicConfigs;
	std::array<Music::ID, 5> mMusicToPlay;
	sf::Time mMusicTimer;

	SceneNode mSceneGraph;
	std::array<SceneNode*, static_cast<std::size_t>(Layer::Count)> mSceneLayers;
	SpriteNode* mCursor;

	std::vector<WaveGenerator*> generators;
	std::vector<Receiver*> receivers;

	std::unordered_map<std::string, GeneratorTypes> generator_name_map;
	std::unordered_map<std::string, ReceiverTypes> receiver_name_map;
	std::unordered_map<Levels, std::string> level_files_map;
	std::unordered_map<std::string, ColorGenerator::EmitterColor> color_name_map;

	sf::Time mLevelCompletedSecond;

	TextNode* mText;

	int mSelectedGenerator;

	Levels level;

	bool rgb;
	bool time;
};

