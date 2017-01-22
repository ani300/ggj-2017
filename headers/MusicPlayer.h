#pragma once

#include "Utils.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

class MusicPlayer : private sf::NonCopyable {
    public:
        MusicPlayer();
        void play(int player, Music::ID theme);
        void stop();
        void setPaused(bool paused);
        void setVolume(float volume);
        sf::Music& getMusicPlayer(int player);

    private:
        std::vector<sf::Music> mMusicPlayers;
        std::map<Music::ID, std::string> mFilenames;
        float mVolume;
};
