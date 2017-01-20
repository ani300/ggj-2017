/********************************TitleScreen.h***************************************/
#pragma once

#include "Utils.h"
#include "State.h"
#include "SceneNode.h"
#include "TextNode.h"
#include "SpriteNode.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class TitleScreen: public State {

    public:
        //Constructor with name of the image it want's to display
        TitleScreen(StatesStack& stack, Context& context);

        void draw();
        bool update(sf::Time dt);
        bool handleEvent(const sf::Event& event);

    private:
        void click(mouseButtons mouseButton, sf::Vector2f mouseClick);
        bool contains(const sf::FloatRect& rect, sf::Vector2i pos);

        enum class Layer {
            Background,
            Text,
            LayerCount
        };

        SceneNode mSceneGraph;
        std::array<SceneNode*, static_cast<std::size_t>(Layer::LayerCount)> mSceneLayers;

        SpriteNode* mButtonPlay;
        SpriteNode* mButtonHelp;
        SpriteNode* mButtonExit;

        std::string str;
};
