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
		ReceiverAlwaysOff,
                ReceiverAlwaysOn,
		WaveGenerator,
                Logo,
		Start,
		Help,
		Title,
		Exit,
		Return,
		HelpBackground,
                ToolboxBackground,
                ScaleBorder
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
                None,
                MenuTheme,
                Game4TBase,
                Game4THarm1,
                Game4THarm2,
                Game4TMel1,
                Game4TMel2,
                Game4TOutro,
                Game3TBase,
                Game3TMel1,
                Game3TMel2,
                Game3TMel3,
                Winning
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
