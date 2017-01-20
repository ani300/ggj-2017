/********************************GameScreen.h***************************************/

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "Utils.h"
#include "State.h"
#include "SceneNode.h"
#include "TextNode.h"
#include "Player.h"
#include "SpriteNode.h"
#include "InvisibleNode.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

namespace Traps {
    enum Traps {
        Boxes = 0,
        SpikesBall,
        Spikes,
        Platform,
        TrapsCount,
    };
}

class GameScreen: public State {

    public:
        //Constructor with name of the image it want's to display
        GameScreen(StatesStack& stack, Context& context);

        void draw();
        bool update(sf::Time dt);
        bool handleEvent(const sf::Event& event);

        void addTrap(int type, sf::Vector2f pos);

    private:
        void handleRealtimeInput();
        void handleCollisions();
        void click(mouseButtons mouseButton, sf::Vector2f mouseClick);

        enum Layer {
            Background,
            World,
            Players,
            Traps,
            Text,
            LayerCount
        };

        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayers;
        std::vector<SpriteNode*> mWalls;
        SpriteNode* mGround;
        SpriteNode* mCursor;
        std::vector<AnimationNode*> mTrapButtons;

        TextNode* mText;

        Player* mPlayer;
        float mJumpVel;
        float mMovVel;
        bool wololo;
        bool topkek;

        int mGamepad1;
        int mGamepad2;
        bool mHasGamepads;

        std::vector<SpriteNode*> mTraps;

        std::string str;

        sf::Clock mCountdown;
};


#endif // GAME_SCREEN_H
