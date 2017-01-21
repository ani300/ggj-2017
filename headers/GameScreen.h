/********************************GameScreen.h***************************************/
#pragma once

#include <unordered_map>

#include "Utils.h"
#include "State.h"
#include "SceneNode.h"
#include "TextNode.h"
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
	void setLevel(Levels level);

    private:
        void click(mouseButtons mouseButton, sf::Vector2f mouseClick);

        enum class Layer {
            Background,
            WavePattern,
            Grid,
            Nodes,
            UI,
            Text,
            Count
        };
        
	enum class GeneratorTypes {
            Standard,
	    Wavelength,
	    Frequency,
	    Amplitude,
	    Editable,
            Count
        };

	enum class ReceiverTypes {
            Threshold,
            AlwaysOn,
            AlwaysOff,
            Count
        };
        bool isLevelCompleted();

        void handleRealtimeInput();

        sf::Vector2f snapGrid(sf::Vector2f pos, sf::Vector2f grid_size);

        SceneNode mSceneGraph;
        std::array<SceneNode*, static_cast<std::size_t>(Layer::Count)> mSceneLayers;
        SpriteNode* mCursor;

        std::vector<WaveGenerator*> generators;
        std::vector<Receiver*> receivers;

	std::unordered_map<std::string, GeneratorTypes> generator_name_map;
	std::unordered_map<std::string, ReceiverTypes> receiver_name_map;

        TextNode* mText;

        int mSelectedGenerator;

	Levels level;

	bool rgb;
	bool time;
};
