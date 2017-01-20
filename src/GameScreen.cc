/*********************************GameScreen.cc***********************************/
#include "GameScreen.h"
#include "AnimationNode.h"

GameScreen::GameScreen(StatesStack& stack, Context& context)
: State(stack, context)
, mWalls(2)
, mGround(nullptr)
, mCursor(nullptr)
, mTrapButtons(4)
, mPlayer(nullptr)
, mJumpVel(2000.0f)
, mMovVel(1000.0f)
, wololo(false)
, topkek(false)
, mGamepad1(-1)
, mGamepad2(-1)
, mHasGamepads(false)
, mCountdown() {
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

void GameScreen::handleRealtimeInput(){
}


