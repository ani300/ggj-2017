/********************************GameScreen.h***************************************/
#pragma once

#include "Utils.h"
#include "State.h"
#include "SceneNode.h"
#include "TextNode.h"
#include "Player.h"
#include "SpriteNode.h"
#include "InvisibleNode.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class WaveGenerator;
class Receiver;
class GameScreen: public State {

    public:
        //Constructor with name of the image it wants to display
        GameScreen(StatesStack& stack, Context& context);


        void draw();
        bool update(sf::Time dt);
        bool handleEvent(const sf::Event& event);

    private:
        void click(mouseButtons mouseButton, sf::Vector2f mouseClick);

        enum class Layer {
            Background,
            WavePattern,
            Nodes,
            Text,
            Count
        };

        bool isLevelCompleted();

        void handleRealtimeInput();

        SceneNode mSceneGraph;
        std::array<SceneNode*, static_cast<std::size_t>(Layer::Count)> mSceneLayers;
        SpriteNode* mCursor;

        std::vector<WaveGenerator*> generators;
        std::vector<Receiver*> receivers;

        TextNode* mText;

        Player* mPlayer;

        int mSelectedGenerator;
};
