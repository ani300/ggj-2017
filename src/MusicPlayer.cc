#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
: mMusicPlayers(5)
, mFilenames()
, mVolume(100.f) {
    mFilenames[Music::MenuTheme] = "res/music/menu.wav";
    mFilenames[Music::Game4TBase] = "res/music/game_4t_base.wav";
    mFilenames[Music::Game4THarm1] = "res/music/game_4t_harmony1.wav";
    mFilenames[Music::Game4THarm2] = "res/music/game_4t_harmony2.wav";
    mFilenames[Music::Game4TMel1] = "res/music/game_4t_melody1.wav";
    mFilenames[Music::Game4TMel2] = "res/music/game_4t_melody2.wav";
    mFilenames[Music::Game4TOutro] = "res/music/game_4t_outro.wav";
    mFilenames[Music::Game3TBase] = "res/music/game_3t_base.wav";
    mFilenames[Music::Game3TMel1] = "res/music/game_3t_melody1.wav";
    mFilenames[Music::Game3TMel2] = "res/music/game_3t_melody2.wav";
    mFilenames[Music::Game3TMel3] = "res/music/game_3t_melody2.wav";
    mFilenames[Music::Winning] = "res/music/winningTheme.ogg";
}

void MusicPlayer::play(int player, Music::ID theme) {
    std::string filename = mFilenames[theme];
    if (!mMusicPlayers[player].openFromFile(filename)) {
        throw std:: runtime_error("Music " + filename + " could not be loaded.");
    }
    mMusicPlayers[player].setVolume(mVolume);
    mMusicPlayers[player].setLoop(true);
    mMusicPlayers[player].play();
}

void MusicPlayer::stop() {
    for (auto& player : mMusicPlayers) {
        player.stop();
    }
}

void MusicPlayer::setVolume(float volume) {
    mVolume = volume;
}

void MusicPlayer::setPaused(bool paused) {
    for (auto& player : mMusicPlayers) {
        if (paused) player.pause();
        else player.play();
    }
}
