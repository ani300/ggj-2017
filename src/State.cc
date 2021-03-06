#include "State.h"
#include "StatesStack.h"



State::Context::Context(sf::RenderTexture& rTexture, TextureHolder& textures, 
    FontHolder& fonts, sf::Vector2f Scale, sf::RenderWindow& window, MusicPlayer& music, 
    SoundPlayer& sound, GameData& gameData)
: mRTexture(&rTexture)
, mTextures(&textures)
, mFonts(&fonts)
, mScale(Scale)
, mWindow(&window)
, mMusic(&music)
, mSound(&sound)
, mGameData(&gameData) {
}

State::State(StatesStack& stack, Context& context)
: mContext(context),mStack(&stack) 
{}

State::~State() {
}

void State::requestStackPush(StateType IDState) {
    mStack->pushState(IDState);
}

void State::requestStackSetLevel(Levels level) {
    mStack->setLevel(level);
}

void State::requestStackPop() {
    mStack->popState();
}

void State::requestStackClear() {
    mStack->clearStates();
}

State::Context State::getContext() const {
    return mContext;
}
