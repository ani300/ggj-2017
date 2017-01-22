/*********************************ResultsScreen.cc***********************************/
#include "ResultsScreen.h"

ResultsScreen::ResultsScreen(StatesStack& stack, Context& context) : 
	State(stack, context) {
	for (std::size_t i = 0; i < LayerCount; ++i) {
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	Levels currentLevel = context.mGameData->currentLevel;
	int level = static_cast<int>(currentLevel);
	int nextLvl = level + 1;
	nextLevel = static_cast<Levels>(nextLvl);

	// Play the MUSIC
	if (getContext().mGameData->numReceivers == 3) {
		getContext().mMusic->play(0, Music::Game3TBase, false);
		getContext().mMusic->play(1, Music::Game3TMel1, false);
		getContext().mMusic->play(2, Music::Game3TMel2, false);
		getContext().mMusic->play(3, Music::Game3TMel3, false);
	}
	else {
		hasMusicFinale = true;
		getContext().mMusic->play(0, Music::Game4TBase, false);
		getContext().mMusic->play(1, Music::Game4THarm1, false);
		getContext().mMusic->play(2, Music::Game4THarm2, false);
		getContext().mMusic->play(3, Music::Game4TMel1, false);
		getContext().mMusic->play(4, Music::Game4TMel2, false);
	}

	// Prepara el fons de pantalla i la font
	sf::Font& font = getContext().mFonts->get(Fonts::Sansation);

	sf::Texture& winningTexture = getContext().mTextures->get(Textures::WinningBg);

	// // Add the background sprite to the scene
	std::unique_ptr<SpriteNode> winningSprite(new SpriteNode(winningTexture));
	//centrar la pantalla i escalar la imatge
	winningSprite->setPosition(sf::Vector2f(1920.0/2.f, 1080.0f/2.0f));
	mSceneLayers[Background]->attachChild(std::move(winningSprite));

	// // Prepara el text
	std::unique_ptr<TextNode> textNode(new TextNode(font, "STAGE CLEAR"));
	mText = textNode.get(); // Guarda una referència al TextNode
	mText->setColor(sf::Color::White);
	mText->setCharacterSize(120);
	mText->setPosition(sf::Vector2f(1920/2.f, 400));
	mText->setStyle(sf::Text::Bold);
	mText->centerText();
	mSceneLayers[Text]->attachChild(std::move(textNode));


	std::unique_ptr<TextNode> textnextNode(new TextNode(font, "Press any key to continue to the next level"));
	textnextNode->setColor(sf::Color::White);
	textnextNode->setCharacterSize(90);
	textnextNode->setPosition(sf::Vector2f(1920/2.f, 600));
	textnextNode->setStyle(sf::Text::Bold);
	textnextNode->centerText();
	mSceneLayers[Text]->attachChild(std::move(textnextNode));
}

void ResultsScreen::draw() {
	getContext().mRTexture->draw(mSceneGraph);
}

bool ResultsScreen::update(sf::Time dt) {
	if (hasMusicFinale) {
		mMusicTimer += dt;
	}
	if (mMusicTimer.asSeconds() > 16) {
		mMusicTimer = sf::Time();
		hasMusicFinale = false;
		getContext().mMusic->play(0, Music::Game4TOutro, false);
	}
	
	mSceneGraph.update(dt);
	return false;
}

bool ResultsScreen::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		getContext().mMusic->stop();
		requestStackPop();
		requestStackPop();
		requestStackPush(StateType::Game);
		getContext().mGameData->currentLevel = nextLevel;
		requestStackSetLevel(nextLevel);
	}

	return false;
}

