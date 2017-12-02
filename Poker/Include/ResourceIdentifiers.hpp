#pragma once

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Image;
	class Font;
	class SoundBuffer;
}

class Animation;

namespace Textures
{
	enum ID
	{
		GameBackground,
		MenuBackground,
		CardAtlas,
		Table
	};
}

namespace Images
{
	enum ID
	{
		DayNightPalette,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
	};
}

namespace SoundEffect
{
	enum ID
	{
		Button
	};
}

namespace Music
{
	enum ID
	{
		None,
		MenuTheme
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Image, Images::ID>				ImageHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;