#pragma once

#include "Utils.h"
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"

class StatesStack;

class State {
    public:
        typedef std::unique_ptr<State> Ptr;

        struct Context {
            Context(sf::RenderTexture& rTexture, TextureHolder& textures, FontHolder& fonts, sf::Vector2f Scale, sf::RenderWindow& window, MusicPlayer& music, SoundPlayer& sound, GameData& gameData);

            sf::RenderTexture* mRTexture;
            TextureHolder* mTextures;
            FontHolder* mFonts;
            sf::Vector2f mScale;
            sf::RenderWindow* mWindow;
            MusicPlayer* mMusic;
            SoundPlayer* mSound;
            GameData* mGameData;
        };

        State(StatesStack& stack, Context& context);
        virtual ~State();

        virtual void draw() = 0;
        virtual bool update(sf::Time dt) = 0;
        virtual bool handleEvent(const sf::Event& event) = 0;

    protected:
        void requestStackPush(StateType stateID);
        void requestStackPop();
        void requestStackClear();
	void requestStackSetLevel(Levels level);

        Context	getContext() const;

        Context mContext;
    private:
        StatesStack* mStack;
};
