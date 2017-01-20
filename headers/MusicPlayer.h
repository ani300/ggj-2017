#pragma once

#include "Utils.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

class MusicPlayer : private sf::NonCopyable {
    public:
        MusicPlayer();
        void play(Music::ID theme);
        void stop();
        void setPaused(bool paused);
        void setVolume(float volume);

    private:
        sf::Music mMusic;
        std::map<Music::ID, std::string> mFilenames;
        float mVolume;
};
