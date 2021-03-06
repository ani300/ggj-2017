/*********************************GameScreen.cc***********************************/
#include "GameScreen.h"
#include "AnimationNode.h"
#include "GridNode.h"
#include "Receiver.h"
#include "ReceiverAlwaysOn.h"
#include "ReceiverAlwaysOff.h"
#include "ReceiverAmplitude.h"
#include "ReceiverRGB.h"
#include "WaveGenerator.h"
#include "WavePatternNode.h"
#include "ScaleNode.h"
#include "Utils.h"
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
	animator = Animator();
	showMessage1("", "");
	showMessage2("", "");
	showMessage3("", "");
	generator_name_map["StandardGenerators"] = GeneratorTypes::Standard;
	generator_name_map["FrequencyGenerators"] = GeneratorTypes::Frequency;
	generator_name_map["WavelengthGenerators"] = GeneratorTypes::Wavelength;
	generator_name_map["AmplitudeGenerators"] = GeneratorTypes::Amplitude;
	generator_name_map["EditableGenerators"] = GeneratorTypes::Editable;
	generator_name_map["ColorGenerators"] = GeneratorTypes::Color;

	receiver_name_map["Threshold"] = ReceiverTypes::Threshold;
	receiver_name_map["AlwaysOn"] = ReceiverTypes::AlwaysOn;
	receiver_name_map["AlwaysOff"] = ReceiverTypes::AlwaysOff;
	receiver_name_map["RGB"] = ReceiverTypes::RGB;

	color_name_map["Red"] = ColorGenerator::EmitterColor::Red;
	color_name_map["Blue"] = ColorGenerator::EmitterColor::Blue;
	color_name_map["Green"] = ColorGenerator::EmitterColor::Green;

	level_files_map[Levels::Level1] = "res/levels/level1.lua";
	level_files_map[Levels::Level2] = "res/levels/level2.lua";
	level_files_map[Levels::Level3] = "res/levels/level3.lua";
	level_files_map[Levels::Level4] = "res/levels/level4.lua";
	level_files_map[Levels::Level5] = "res/levels/level5.lua";

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

	for (std::size_t i = 0; i < mMusicToPlay.size(); ++i) {
		mMusicToPlay[i] = Music::None;
	}

	if(getContext().mGameData->currentLevel == Levels::Level1)
	{
		tutorialFirstMessage();
	}

	if(getContext().mGameData->currentLevel == Levels::Level2)
	{
		showMessage1("1", "To win activate all receivers");
		showMessage2("2", "These two receivers need amplitudes bigger than one");
		//Show text
		GInterpolation* step2a_1 = new Interpolation<float>(textOpacity1, 255.f, 1.f);
		GInterpolation* step2b_1 = new Interpolation<sf::Vector2f>(textPos1, sf::Vector2f(500.f,320.f), 3.f);
		GInterpolation* step2a_2 = new Interpolation<float>(textOpacity2, 255.f, 1.f);
		GInterpolation* step2b_2 = new Interpolation<sf::Vector2f>(textPos2, sf::Vector2f(500.f,620.f), 3.f);
		//Just wait
		GInterpolation* step1 = new Interpolation<float>(timer, 0.f, 1.f, [this, step2a_1, step2b_1, step2a_2, step2b_2](){
			animator.interpolate(*step2a_1);
			animator.interpolate(*step2b_1);
			animator.interpolate(*step2a_2);
			animator.interpolate(*step2b_2);
		});
		animator.interpolate(*step1);
	}
	if(getContext().mGameData->currentLevel == Levels::Level3)
	{
		showMessage1("", "This receiver always wants to be at amplitude 0 (black)");
		//Show text
		GInterpolation* step2a_1 = new Interpolation<float>(textOpacity1, 255.f, 1.f);
		GInterpolation* step2b_1 = new Interpolation<sf::Vector2f>(textPos1, sf::Vector2f(400.f,500.f), 3.f);
		GInterpolation* step2a_2 = new Interpolation<float>(textOpacity2, 255.f, 1.f);
		GInterpolation* step2b_2 = new Interpolation<sf::Vector2f>(textPos2, sf::Vector2f(470.f,650.f), 3.f);
		//Just wait
		GInterpolation* step1 = new Interpolation<float>(timer, 0.f, 1.f, [this, step2a_1, step2b_1, step2a_2, step2b_2](){
			animator.interpolate(*step2a_1);
			animator.interpolate(*step2b_1);
			animator.interpolate(*step2a_2);
			animator.interpolate(*step2b_2);
		});
		animator.interpolate(*step1);
	}
	if(getContext().mGameData->currentLevel == Levels::Level4)
	{
		showMessage1("1", "These are RGB generators. \n They make different colors.\n We have Red, Green and Blue generators");
		showMessage2("2", "And this is an RGB receiver, obviously.\n It receives the same color it looks like");
		//Show text
		GInterpolation* step2a_1 = new Interpolation<float>(textOpacity1, 255.f, 1.f);
		GInterpolation* step2b_1 = new Interpolation<sf::Vector2f>(textPos1, sf::Vector2f(200.f,50.f), 3.f);
		GInterpolation* step2a_2 = new Interpolation<float>(textOpacity2, 255.f, 1.f);
		GInterpolation* step2b_2 = new Interpolation<sf::Vector2f>(textPos2, sf::Vector2f(450.f,550.f), 3.f);
		//Just wait
		GInterpolation* step1 = new Interpolation<float>(timer, 0.f, 1.f, [this, step2a_1, step2b_1, step2a_2, step2b_2](){
			animator.interpolate(*step2a_1);
			animator.interpolate(*step2b_1);
			animator.interpolate(*step2a_2);
			animator.interpolate(*step2b_2);
		});
		animator.interpolate(*step1);
	}
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

void GameScreen::tutorialFirstMessage(){

	showMessage1("1", "This is a wave generator");
	showMessage2("2", "This is a threshold receiver. \n If in the last 2 seconds it senses a wave with a \n certain amplitude it will trigger");
	//Show text
	GInterpolation* step2a_1 = new Interpolation<float>(textOpacity1, 255.f, 1.f);
	GInterpolation* step2b_1 = new Interpolation<sf::Vector2f>(textPos1, sf::Vector2f(30.f,65.f), 3.f);
	GInterpolation* step2a_2 = new Interpolation<float>(textOpacity2, 255.f, 1.f);
	GInterpolation* step2b_2 = new Interpolation<sf::Vector2f>(textPos2, sf::Vector2f(500.f,500.f), 3.f);
	//Just wait
	GInterpolation* step1 = new Interpolation<float>(timer, 0.f, 1.f, [this, step2a_1, step2b_1, step2a_2, step2b_2](){
		animator.interpolate(*step2a_1);
		animator.interpolate(*step2b_1);
		animator.interpolate(*step2a_2);
		animator.interpolate(*step2b_2);
	});
	animator.interpolate(*step1);

}


void GameScreen::tutorialMessageOff(){
	if(firstMove)
	{
		firstMove = false;
	    GInterpolation* step4a = new Interpolation<float>(textOpacity1, 1.f, 1.f, [this](){
    		tutorialTitle1->setPosition(1920.f, 1080.f);
    		tutorialBody1->setPosition(1920.f, 1080.f);
    	});
    	GInterpolation* step4b = new Interpolation<sf::Vector2f>(textPos1, sf::Vector2f(1000.f,1000.f), 1.f);

    	GInterpolation* step4a_2 = new Interpolation<float>(textOpacity2, 1.f, 1.f, [this](){
    		tutorialTitle2->setPosition(1920.f, 1080.f);
    		tutorialBody2->setPosition(1920.f, 1080.f);
    	});
    	GInterpolation* step4b_2 = new Interpolation<sf::Vector2f>(textPos2, sf::Vector2f(1000.f,1000.f), 1.f);
    	animator.interpolate(*step4a);
    	animator.interpolate(*step4b);
		animator.interpolate(*step4a_2);
    	animator.interpolate(*step4b_2);
	}
}

bool GameScreen::update(sf::Time dt) {
	animator.update(dt);
	//Update text tutorial
	tutorialTitle1->setColor(sf::Color(textOpacity1,textOpacity1,textOpacity1,textOpacity1));
    tutorialTitle1->setPosition(textPos1.x, textPos1.y);

    tutorialBody1->setColor(sf::Color(textOpacity1,textOpacity1,textOpacity1,textOpacity1));
    tutorialBody1->setPosition(textPos1.x, textPos1.y + 70.f);

    tutorialTitle2->setColor(sf::Color(textOpacity2,textOpacity2,textOpacity2,textOpacity2));
    tutorialTitle2->setPosition(textPos2.x, textPos2.y);

    tutorialBody2->setColor(sf::Color(textOpacity2,textOpacity2,textOpacity2,textOpacity2));
    tutorialBody2->setPosition(textPos2.x, textPos2.y + 70.f);

    
    ///----tutorial

	handleRealtimeInput(dt);

	if(isLevelCompleted()) {
		for (std::size_t i = 1; i < 5; ++i) {
			getContext().mMusic->getMusicPlayer(i).stop();
		}
		mLevelCompletedSecond += dt;
	}

	if (mLevelCompletedSecond.asSeconds() >= 4) {
		requestStackPush(StateType::Result);
	}

	MusicState old_state = mMusicState;
	updateMusicState();
	mMusicTimer += dt;
	if (receivers.size() == 3) {
		if (mMusicTimer.asSeconds() > 9) {
			mMusicTimer -= sf::seconds(9);
		}
	}
	else {
		if (mMusicTimer.asSeconds() > 16) {
			mMusicTimer -= sf::seconds(16);
		}
	}

	if (old_state != mMusicState) {
		updateMusicPlayback();
	}

	mSceneGraph.update(dt);
	return true;
}

void GameScreen::showMessage1(std::string title, std::string msg) {
	/*sf::Texture& messageBg = getContext().mTextures->get(Textures::ToolboxBackground);
	std::unique_ptr<SpriteNode> message(new SpriteNode(messageBg));
    SpriteNode* mMsgbg = message.get();
    mMsgbg->setPosition(pos.x, pos.y);
    mMsgbg->setSize(sf::Vector2u(size.x, size.y));
    mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(message));*/


    sf::Font& font = getContext().mFonts->get(Fonts::Sansation);
    std::unique_ptr<TextNode> titlem(new TextNode(font, title));
    tutorialTitle1 = titlem.get();
    tutorialTitle1->setCharacterSize(50);
    tutorialTitle1->setStyle(sf::Text::Bold);
    tutorialTitle1->setColor(sf::Color(textOpacity1,textOpacity1,textOpacity1,textOpacity1));
    tutorialTitle1->setPosition(textPos1.x, textPos1.y);
    //mTitle->setSize(sf::Vector2u(size.x, 80));
    //tutorialTitle->centerText();
    mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(titlem));

    std::unique_ptr<TextNode> msgm(new TextNode(font, msg));
    tutorialBody1 = msgm.get();
    tutorialBody1->setCharacterSize(40);
    tutorialBody1->setColor(sf::Color(textOpacity1,textOpacity1,textOpacity1,textOpacity1));
    tutorialBody1->setStyle(sf::Text::Regular);
    //margin-top:20.f
    tutorialBody1->setPosition(textPos1.x, textPos1.y+70.f);
    //mMsg->setSize(sf::Vector2u(size.x, 80));
    mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(msgm));
}

void GameScreen::showMessage2(std::string title, std::string msg) {
	/*sf::Texture& messageBg = getContext().mTextures->get(Textures::ToolboxBackground);
	std::unique_ptr<SpriteNode> message(new SpriteNode(messageBg));
    SpriteNode* mMsgbg = message.get();
    mMsgbg->setPosition(pos.x, pos.y);
    mMsgbg->setSize(sf::Vector2u(size.x, size.y));
    mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(message));*/


    sf::Font& font = getContext().mFonts->get(Fonts::Sansation);
    std::unique_ptr<TextNode> titlem(new TextNode(font, title));
    tutorialTitle2 = titlem.get();
    tutorialTitle2->setCharacterSize(50);
    tutorialTitle2->setStyle(sf::Text::Bold);
    tutorialTitle2->setColor(sf::Color(textOpacity2,textOpacity2,textOpacity2,textOpacity2));
    tutorialTitle2->setPosition(textPos2.x, textPos2.y);
    //mTitle->setSize(sf::Vector2u(size.x, 80));
    //tutorialTitle->centerText();
    mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(titlem));

    std::unique_ptr<TextNode> msgm(new TextNode(font, msg));
    tutorialBody2 = msgm.get();
    tutorialBody2->setCharacterSize(40);
    tutorialBody2->setColor(sf::Color(textOpacity2,textOpacity2,textOpacity2,textOpacity2));
    tutorialBody2->setStyle(sf::Text::Regular);
    //margin-top:20.f
    tutorialBody2->setPosition(textPos2.x, textPos2.y+70.f);
    //mMsg->setSize(sf::Vector2u(size.x, 80));
    mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(msgm));
}
void GameScreen::showMessage3(std::string title, std::string msg) {
	/*sf::Texture& messageBg = getContext().mTextures->get(Textures::ToolboxBackground);
	std::unique_ptr<SpriteNode> message(new SpriteNode(messageBg));
    SpriteNode* mMsgbg = message.get();
    mMsgbg->setPosition(pos.x, pos.y);
    mMsgbg->setSize(sf::Vector2u(size.x, size.y));
    mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(message));*/


    sf::Font& font = getContext().mFonts->get(Fonts::Sansation);
    std::unique_ptr<TextNode> titlem(new TextNode(font, title));
    tutorialTitle3 = titlem.get();
    tutorialTitle3->setCharacterSize(50);
    tutorialTitle3->setStyle(sf::Text::Bold);
    tutorialTitle3->setColor(sf::Color(textOpacity3,textOpacity3,textOpacity3,textOpacity3));
    tutorialTitle3->setPosition(textPos2.x, textPos2.y);
    //mTitle->setSize(sf::Vector2u(size.x, 80));
    //tutorialTitle->centerText();
    mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(titlem));

    std::unique_ptr<TextNode> msgm(new TextNode(font, msg));
    tutorialBody3 = msgm.get();
    tutorialBody3->setCharacterSize(40);
    tutorialBody3->setColor(sf::Color(textOpacity3,textOpacity3,textOpacity3,textOpacity3));
    tutorialBody3->setStyle(sf::Text::Regular);
    //margin-top:20.f
    tutorialBody3->setPosition(textPos2.x, textPos2.y+70.f);
    //mMsg->setSize(sf::Vector2u(size.x, 80));
    mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(msgm));
}


void GameScreen::handleRealtimeInput(sf::Time dt) {
	mousePos = sf::Mouse::getPosition(*getContext().mWindow);
	newPos = Utils::correctMouse(mousePos, getContext().mScale);
	oldPos = newfpos;
	newfpos = sf::Vector2f(newPos.x, newPos.y);

	std::vector<SceneNode*> children;
	mSceneGraph.getAllChildren(children);
	if(mSelectedGenerator == -1)
	{
		//Quieto
		if(Utils::distance(oldPos, newfpos) < 0.01) {
			for (std::size_t i = 0; i < children.size(); ++i) {
				if(SpriteNode *child = dynamic_cast<SpriteNode*>(children[i])) {
					sf::IntRect bounds = child->getBounds();
					if (bounds.contains(newPos)) {
						mouseOver = i;
					}
				  
				}
			}
		}
		//Movimiento
		else {
			if(hovering)
			{
				children[mouseOver]->onHoverOut();
				mouseOver = -1;
			}
			if(mouseOver != -1)
				children[mouseOver]->onMouseOut();
			
			hovering = false;
			secondsToHover = HOVER_TIME;
		}
		if(mouseOver != -1) {
			secondsToHover -= dt.asSeconds();
			children[mouseOver]->onMouseOver();
			if(secondsToHover <= 0 and not hovering)
			{
				hovering = true;
				children[mouseOver]->onHover();
			}

		}
	}
	else
	{
		generators[mSelectedGenerator]->setPosition(sf::Vector2f(newPos));
		if((mToolbox->getBounds()).contains(newPos)) {
			generators[mSelectedGenerator]->place(false);
		}
		else
		{
			tutorialMessageOff();
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

void GameScreen::updateMusicPlayback() {
	// Update playing music accordingly
	auto is_playing = [this](int player) -> bool {
		return getContext().mMusic->getMusicPlayer(player).getStatus() == sf::SoundSource::Playing;
	};

	// Base3T
	if (mMusicConfigs[mMusicState][0] && !is_playing(0)) {
		mMusicToPlay[0] = Music::Game3TBase;
	}
	else if (!mMusicConfigs[mMusicState][0] && !mMusicConfigs[mMusicState][1] && is_playing(0)) {
		mMusicToPlay[0] = Music::None;
	}

	// Base4T
	if (mMusicConfigs[mMusicState][1] && !is_playing(0)) {
		mMusicToPlay[0] = Music::Game4TBase;
	}
	else if (!mMusicConfigs[mMusicState][1] && !mMusicConfigs[mMusicState][0] && is_playing(0)) {
		mMusicToPlay[0] = Music::None;
	}

	// Harm1-4T
	if (mMusicConfigs[mMusicState][2] && !is_playing(1)) {
		mMusicToPlay[1] = Music::Game4THarm1;
	}
	else if (!mMusicConfigs[mMusicState][2] && !mMusicConfigs[mMusicState][6] && is_playing(1)) {
		mMusicToPlay[1] = Music::None;
	}

	// Harm2-4T
	if (mMusicConfigs[mMusicState][3] && !is_playing(2)) {
		mMusicToPlay[2] = Music::Game4THarm2;
	}
	else if (!mMusicConfigs[mMusicState][3] && !mMusicConfigs[mMusicState][7] && is_playing(2)) {
		mMusicToPlay[2] = Music::None;
	}

	// Mel1-4T
	if (mMusicConfigs[mMusicState][4] && !is_playing(3)) {
		mMusicToPlay[3] = Music::Game4TMel1;
	}
	else if (!mMusicConfigs[mMusicState][4] && !mMusicConfigs[mMusicState][8] && is_playing(3)) {
		mMusicToPlay[3] = Music::None;
	}

	// Mel2-4T
	if (mMusicConfigs[mMusicState][5] && !is_playing(4)) {
		mMusicToPlay[4] = Music::Game4TMel2;
	}
	else if (!mMusicConfigs[mMusicState][5] && is_playing(4)) {
		mMusicToPlay[4] = Music::None;
	}

	// Mel1-3T
	if (mMusicConfigs[mMusicState][6] && !is_playing(1)) {
		mMusicToPlay[1] = Music::Game3TMel1;
	}
	else if (!mMusicConfigs[mMusicState][6] && !mMusicConfigs[mMusicState][2] && is_playing(1)) {
		mMusicToPlay[1] = Music::None;
	}

	// Mel2-3T
	if (mMusicConfigs[mMusicState][7] && !is_playing(2)) {
		mMusicToPlay[2] = Music::Game3TMel2;
	}
	else if (!mMusicConfigs[mMusicState][7] && !mMusicConfigs[mMusicState][3] && is_playing(2)) {
		mMusicToPlay[2] = Music::None;
	}

	// Mel3-3T
	if (mMusicConfigs[mMusicState][8] && !is_playing(3)) {
		mMusicToPlay[3] = Music::Game3TMel3;

	}
	else if (!mMusicConfigs[mMusicState][8] && !mMusicConfigs[mMusicState][4] && is_playing(3)) {
		mMusicToPlay[3] = Music::None;
	}
	// Play teh musik
	getContext().mMusic->setPaused(true);
	for (std::size_t i = 0; i < mMusicToPlay.size(); ++i) {
		if (mMusicToPlay[i] != Music::None) {
			getContext().mMusic->play(i, mMusicToPlay[i]);
			getContext().mMusic->getMusicPlayer(i).setPlayingOffset(mMusicTimer);
		}
		else {
			getContext().mMusic->getMusicPlayer(i).stop();
		}
	}
}

sf::Vector2f GameScreen::snapGrid(sf::Vector2f pos, sf::Vector2i grid_size) {
	return snapGrid(pos, sf::Vector2f(grid_size.x, grid_size.y));
}

bool GameScreen::handleEvent(const sf::Event& event) {
	
	if (event.type == sf::Event::MouseButtonPressed) {
		std::vector<SceneNode*> children;
		mSceneGraph.getAllChildren(children);
		if(hovering)
		{
			children[mouseOver]->onHoverOut();
			mouseOver = -1;
		}
		if(mouseOver != -1)
			children[mouseOver]->onMouseOut();
		
		hovering = false;
		secondsToHover = HOVER_TIME;
		if (event.mouseButton.button == sf::Mouse::Left) {
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
					receiver->setSize(sf::Vector2u(60,60));
					receiver->setAnimation("Off");
					receivers.push_back(receiver.get());
					mSceneLayers[static_cast<int>(Layer::Nodes)]->attachChild(std::move(receiver));
				}
				break;
			case ReceiverTypes::AlwaysOff:
				{
					auto receiver = std::make_unique<ReceiverAlwaysOff>(mContext.mTextures->get(Textures::ReceiverAlwaysOff), generators);
					receiver->setPosition(position);
					receiver->setSize(sf::Vector2u(60,60));
					receiver->setAnimation("Off");
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
					receiver->setSize(sf::Vector2u(60,60));
					receiver->setAnimation("Off");
					receivers.push_back(receiver.get());
					mSceneLayers[static_cast<int>(Layer::Nodes)]->attachChild(std::move(receiver));
				}
				break;
			case ReceiverTypes::RGB:
				{
					sf::Color receiver_color;

					receiver_color.r = table["color"]["r"];
					receiver_color.g = table["color"]["g"];
					receiver_color.b = table["color"]["b"];
					receiver_color.a = table["color"]["a"];

					auto receiver = std::make_unique<ReceiverRGB>(mContext.mTextures->get(Textures::ReceiverAlwaysOff), generators, receiver_color);
					receiver->setPosition(position);
					receiver->setSize(sf::Vector2u(60,60));
					receiver->setAnimation("Off");
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
						generator->setSize(sf::Vector2u(100,100));
						generator->setAnimation("Generator");
						mSceneLayers[static_cast<int>(Layer::Nodes)]->attachChild(std::move(generator));
					}
					break;
				case GeneratorTypes::Color:
					{
						auto gc = lua["generator_colors"][i+1];
						ColorGenerator::EmitterColor c = color_name_map[gc];
						std::unique_ptr<ColorGenerator> generator = std::make_unique<ColorGenerator>(mContext.mTextures->get(Textures::ColorGenerator), "res/anim/generator.anim", c);
						generators.push_back(generator.get());
						generator->setSize(sf::Vector2u(100,100));
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


	if(!rgb) {
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

		auto color_scale = std::make_unique<ScaleNode>("res/shaders/scale.vert", "res/shaders/scale.frag", mContext.mTextures->get(Textures::ScaleBorder), color1, color2, color3);
		ScaleNode* scale_node = color_scale.get();
		mSceneLayers[static_cast<int>(Layer::UI)]->attachChild(std::move(color_scale));
		scale_node->setPosition(sf::Vector2f(1850, 890));
	}
	else {
		auto wave_pattern = std::make_unique<WavePatternNode>("res/shaders/rgb_waves.frag", generators);
		mSceneLayers[static_cast<int>(Layer::WavePattern)]->attachChild(std::move(wave_pattern));
	}

	getContext().mGameData->numReceivers = receivers.size();
}
