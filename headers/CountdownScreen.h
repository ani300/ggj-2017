/********************************CountdownScreen.h***************************************/

#pragma once

#include "Utils.h"
#include "State.h"
#include "SceneNode.h"
#include "TextNode.h"
#include "AnimatedTextNode.h"
#include "SpriteNode.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class CountdownScreen: public State {

    public:
        //Constructor with name of the image it want's to display
        CountdownScreen(StatesStack& stack, Context& context);

        void draw() override;
        bool update(sf::Time dt) override;
        bool handleEvent(const sf::Event& event) override;

    private:
        enum Layer {
            Background,
            Text,
            LayerCount
        };

        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayers;
        
        std::array<AnimatedTextNode*, 2> mTextNodes;
        AnimatedTextNode* mText;

        float mWaitingTime;
        sf::Clock mClock;
};
