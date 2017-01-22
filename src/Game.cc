#include "Game.h"

#include "Utils.h"
#include "State.h"
#include "StateIdentifiers.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

//Constructor

Game::Game() :
  mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), L"Waves Trigger Nodes"
    , sf::Style::None/*sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize*/)
, mWindowSize(mWindow.getSize().x, mWindow.getSize().y)
, mScale(float(mWindow.getSize().x)/1920.0, 9.0/16.0*float(mWindow.getSize().x)/1920.0)
, mRenderTexture()
, mFonts()
, mTextures()
, mMusic()
, mSound()
, mGameData()
, mStatesStack(State::Context(mRenderTexture, mTextures, mFonts, mScale, mWindow, mMusic, mSound, mGameData))
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
{
    bool renderCreated = mRenderTexture.create(1920, 1080);
    (void)renderCreated;
    assert(renderCreated);
    mRenderTexture.setSmooth(true);

    mWindowSize = mWindow.getSize();
    mScale = sf::Vector2f(float(mWindow.getSize().x)/1920.0, float(mWindow.getSize().x)/1920.0);
    mStatesStack.setContext(State::Context(mRenderTexture, mTextures, mFonts, mScale, mWindow, mMusic, mSound, mGameData));

    mWindow.setKeyRepeatEnabled(false);
    // Carrega recursos comuns
    mFonts.load(Fonts::Sansation, "res/media/Sansation.ttf");
    
    mTextures.load(Textures::ReceiverAlwaysOn, "res/pictures/prueba_n1_50.png");
    mTextures.load(Textures::WaveGenerator, "res/pictures/spritesheet_recep2_anim.png");
    mTextures.load(Textures::Logo, "res/pictures/logo.png");
    mTextures.load(Textures::Start, "res/pictures/prueba_startbutton1.png");
    mTextures.load(Textures::Help, "res/pictures/prueba_helpbutton1.png");
    mTextures.load(Textures::Exit, "res/pictures/prueba_exitbutton1.png");
    mTextures.load(Textures::ToolboxBackground, "res/pictures/toolbox_bg.png");
    

    // mStatisticsText.setFont(mFonts.get(Fonts::Sansation));
    // mStatisticsText.setPosition(5.f, 5.f);
    // mStatisticsText.setCharacterSize(10u);
    // mStatisticsText.setFillColor(sf::Color::Black);

    mWindow.setVerticalSyncEnabled(true);

    registerStates();
    mStatesStack.pushState(StateType::Title);
    
    //Interpolation<float> inter = Interpolation<float>(test, 10.f, 1.f);
    //GInterpolation* inter = new Interpolation<float>(test, 10.f, 1.f);
    //GInterpolation* inter = new Interpolation<sf::Vector2f>(test, sf::Vector2f(10.f, 10.f), 0.5f, [](){
    //  std::cout << "Callback!" << std::endl;
    //});
    //animator.interpolate((*inter));
}


int Game::play() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
//std::cout << clock.getElapsedTime().asSeconds() << " initialBucle time" << std::endl;
            processInput();
//std::cout << clock.getElapsedTime().asSeconds() << " time to process Input " << std::endl;
            update(TimePerFrame);
//std::cout << clock.getElapsedTime().asSeconds() << " time to update" << std::endl;
            // Check inside this loop, because stack might be empty before update() call
            if (mStatesStack.isEmpty())
                mWindow.close();
        }
        updateStatistics(dt);
//std::cout << clock.getElapsedTime().asSeconds() << "let's render" << std::endl;
        render();
//std::cout << clock.getElapsedTime().asSeconds() << "rendered------------------------------------------------------------------------------------" << std::endl;
    }

    return EXIT_SUCCESS;
}

void Game::processInput() {
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStatesStack.handleEvent(event);

        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            mWindow.close();
        }
    }
}

void Game::update(sf::Time dt) {
    //std::cout << test.x << ", " << test.y << std::endl;
    //animator.update(dt);
    mStatesStack.update(dt);
}

void Game::render() {
    mRenderTexture.clear();

    mStatesStack.draw();

    mRenderTexture.display();

    // Now we start rendering to the window, clear it first
    mWindow.clear();
    mWindow.setView(mWindow.getDefaultView());
    // Draw the texture
    sf::Sprite sprite(mRenderTexture.getTexture());
    // Llegeix mida de la finestra (x, y)
    mWindowSize = mWindow.getSize();
    sprite.setScale(1.0, 1.0);
    sprite.setPosition(0.0, 0.0);
    mScale = sf::Vector2f(float(mWindowSize.x)/float(mRenderTexture.getSize().x), float(mWindowSize.x)/float(mRenderTexture.getSize().x)); // 16:9 aspect
    //std::cout << mScale.x << " " << mScale.y << std::endl;
    sprite.setScale(mScale);
    mWindow.draw(sprite);
    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    // End the current frame and display its contents on screen
    mWindow.display();

}

void Game::updateStatistics(sf::Time dt) {
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;
    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

void Game::registerStates() {
    mStatesStack.registerState<TitleScreen>(StateType::Title);
    mStatesStack.registerState<HelpScreen>(StateType::Help);
    mStatesStack.registerState<GameScreen>(StateType::Game);
    mStatesStack.registerState<ResultsScreen>(StateType::Result);
}

