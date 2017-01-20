#include "Player.h"

Player::Player(const sf::Texture& texture, const std::string& file) : 
    AnimationNode(texture, file),
    mState(Player::States::IdleRight),
    mDoubleJumpUsed(false),
    mLookingRight(true),
    mDead(false),
    mInGround(0),
    mInWall(0) {
}

void Player::updateCurrent(sf::Time dt) {
    AnimationNode::updateCurrent(dt);
}

void Player::addVel(float x, float y) {
}

void Player::setVel(float x, float y) {
}

void Player::scaleVel(float x, float y) {
}


bool Player::isDead() const {
    return mDead;
}

Player::States Player::getState() {
    return mState;
}

void Player::setState(Player::States state) {
    mState = state;
}

void Player::updateState() {
}

void Player::setLookingRight(bool state) {
    mLookingRight = state;
}

void Player::changeAnimation() {
    switch(mState) {
        case States::IdleRight:
            setAnimation("IdleRight");
            break;
        case States::IdleLeft:
            setAnimation("IdleLeft");
            break;
        case States::JumpRight:
            setAnimation("JumpRight");
            break;
        case States::JumpLeft:
            setAnimation("JumpLeft");
            break;
        case States::FallRight:
            setAnimation("FallRight");
            break;
        case States::FallLeft:
            setAnimation("FallLeft");
            break;
        case States::Right:
            setAnimation("Right");
            break;
        case States::Left:
            setAnimation("Left");
            break;
        case States::DeadRight:
            setAnimation("DeadRight");
            break;
        case States::DeadLeft:
            setAnimation("DeadLeft");
            break;
        case States::WallRight:
            setAnimation("WallRight");
            break;
        case States::WallLeft:
            setAnimation("WallLeft");
            break;
        default:
            break;
    }
}

