#pragma once

#include <SFML/Audio.hpp>

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum ID
	{
		ReceiverAlwaysOn,
		WaveGenerator,
		Start,
		Help,
		Title,
		Exit,
		Return,
		HelpBackground
	};
}

namespace Fonts
{
	enum ID
	{
        AlluraRegular,
        Sansation,
        Gomo
	};
}

namespace Music
{
        enum ID
        {
                MenuTheme,
                GameTheme,
                StartTheme,
                FinishTheme,
                WinningTheme,
        };
}

namespace SoundEffect {
        enum ID
        {
                Cage,
                Gong,
                Jump,
                Spikeball,
                Spikes,
                Switch,
        };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>	FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;
