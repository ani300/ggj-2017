#pragma once

#include "Utils.h"
#include "SceneNode.h"
#include "AnimationNode.h"

class Player: public AnimationNode {
    public:
        explicit Player(const sf::Texture& texture, const std::string& file);

        enum class States {
            IdleRight,
            IdleLeft,
            Right,
            Left,
            JumpRight,
            JumpLeft,
            FallRight,
            FallLeft,
            DeadRight,
            DeadLeft,
            WallRight,
            WallLeft,
        };

        Player::States getState();
        void setState(Player::States state);
        void setLookingRight(bool state);

        void addVel(float x, float y);
        void setVel(float x, float y);
        void scaleVel(float x, float y);
        bool isJumping() const;
        bool canJump() const;
        void jump(float v);
        bool isDead() const;

    private:
        void updateCurrent(sf::Time dt);
        void updateState();
        void changeAnimation();

        States mState;

        bool mDoubleJumpUsed;
        bool mLookingRight;
        bool mDead;
        int mInGround;
        int mInWall;
};
