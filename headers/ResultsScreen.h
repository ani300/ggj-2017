/********************************ResultsScreen.h***************************************/
#pragma once

#include "Utils.h"
#include "State.h"
#include "SceneNode.h"
#include "TextNode.h"
#include "AnimatedTextNode.h"
#include "SpriteNode.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "StateIdentifiers.h"

class ResultsScreen: public State {

    public:
        //Constructor with name of the image it want's to display
        ResultsScreen(StatesStack& stack, Context& context);

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
        TextNode* mText;

        sf::Time mMusicTimer;
        bool hasMusicFinale = false;

	Levels nextLevel;
};
