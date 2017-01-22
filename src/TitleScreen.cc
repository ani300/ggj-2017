/*********************************TitleScreen.cc***********************************/
#include "TitleScreen.h"
#include "WavePatternNode.h"

TitleScreen::TitleScreen(StatesStack& stack, Context& context)
: State(stack, context) {
	for (std::size_t i = 0; i < static_cast<std::size_t>(Layer::Count); ++i) {
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	animator = Animator();
	GInterpolation* inter = new Interpolation<float>(fader, 0.f, 2.f);

    animator.interpolate(*inter);

	// Prepara el fons de pantalla i la font
	//sf::Font& font = getContext().mFonts->get(Fonts::Sansation);
	//sf::Texture& backTexture = getContext().mTextures->get(Textures::Title);
	sf::Texture& startTexture = getContext().mTextures->get(Textures::Start);
	sf::Texture& helpTexture = getContext().mTextures->get(Textures::Help);
	sf::Texture& exitTexture = getContext().mTextures->get(Textures::Exit);
	sf::Texture& logoTexture = getContext().mTextures->get(Textures::Logo);


	
	auto generator = std::make_unique<WaveGenerator>(context.mTextures->get(Textures::WaveGenerator),
					"res/anim/generator.anim");
	generators.push_back(generator.get());
	mSceneLayers[static_cast<int>(Layer::Background)]->attachChild(std::move(generator));


	generators[0]->setPosition(640.f, 360.f);
	generators[0]->setSize(sf::Vector2u(90, 90));
	generators[0]->setAnimation("Generator");
	generators[0]->place(true);

	auto wave_pattern = std::make_unique<WavePatternNode>("res/shaders/sine_waves.frag", generators, 
		sf::Color(0,255,255,255), sf::Color(0,0,0,255), sf::Color(0,255,255,255));
	mSceneLayers[static_cast<int>(Layer::Background)]->attachChild(std::move(wave_pattern));

	std::unique_ptr<SpriteNode> logo(new SpriteNode(logoTexture));
	mLogo = logo.get();
	mLogo->setPosition(640.f, 360.f);
	mLogo->setSize(sf::Vector2u(551.f, 260.f));
	mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(logo));

	std::unique_ptr<AnimationNode> button1(new AnimationNode(startTexture, "res/anim/start.anim"));
	mButtonPlay = button1.get();
	mButtonPlay->setPosition(1600.f, 650.f);
	mButtonPlay->setSize(sf::Vector2u(147.f, 70.f));
	mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(button1));

	std::unique_ptr<AnimationNode> button2(new AnimationNode(helpTexture, "res/anim/help.anim"));
	mButtonHelp = button2.get();
	mButtonHelp->setPosition(1600.f, 750.f);
	mButtonHelp->setSize(sf::Vector2u(118.f, 70.f));
	mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(button2));

	std::unique_ptr<AnimationNode> button3(new AnimationNode(exitTexture, "res/anim/exit.anim"));
	mButtonExit = button3.get();
	mButtonExit->setPosition(1600.f, 850.f);
	mButtonExit->setSize(sf::Vector2u(110.f, 70.f));
	mSceneLayers[static_cast<int>(Layer::Text)]->attachChild(std::move(button3));

	context.mMusic->play(0, Music::MenuTheme);

}

void TitleScreen::draw() {
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(1920, 1080));
	rectangle.setFillColor(sf::Color(0,0,0,fader));
	rectangle.setPosition(0, 0);
	

	getContext().mRTexture->draw(mSceneGraph);
	getContext().mRTexture->draw(rectangle);
}

bool TitleScreen::update(sf::Time dt) {
	animator.update(dt);
	mSceneGraph.update(dt);

	return true;
}

bool TitleScreen::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::EventType::MouseButtonPressed 
		&& event.mouseButton.button == sf::Mouse::Button::Left) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*getContext().mWindow);
		sf::Vector2i newPos = Utils::correctMouse(mousePos, getContext().mScale);
		sf::IntRect newGameBounds = mButtonPlay->getBounds();
		sf::IntRect helpBounds = mButtonHelp->getBounds();
		sf::IntRect exitBounds = mButtonExit->getBounds();
		if (newGameBounds.contains(newPos)) {
			GInterpolation* inter = new Interpolation<float>(fader, 255.f, 2.f, [this](){
				getContext().mMusic->stop();
				requestStackPop();
				requestStackPush(StateType::Game);
				getContext().mGameData->currentLevel = Levels::Level1;
				requestStackSetLevel(Levels::Level1);
				
			});
			animator.interpolate(*inter);
		}
		else if (helpBounds.contains(newPos)) {
			requestStackPop();
			requestStackPush(StateType::Help);
		}
		else if (exitBounds.contains(newPos)) {
			GInterpolation* inter = new Interpolation<float>(fader, 255.f, 2.f, [this](){
				requestStackPop();
			});
			animator.interpolate(*inter);
		}
		else {
			std::cout << "kek" << std::endl;
		} 
	}
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Return) {
			requestStackPop();
			requestStackPush(StateType::Game);
			getContext().mGameData->currentLevel = Levels::Level1;
			requestStackSetLevel(Levels::Level1);
		}
	}
	return true;
}
