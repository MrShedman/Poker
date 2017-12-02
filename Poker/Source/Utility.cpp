#include <Utility.h>
#include <random>

sf::Vector2f getMousePosition(const sf::RenderWindow &window)
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

sf::View getAlignedView(sf::View view)
{
	sf::Vector2f pos = view.getCenter();

	pos.x = std::round(pos.x) + 0.375f;
	pos.y = std::round(pos.y) + 0.375f;

	view.setCenter(pos);

	return view;
}

std::vector<sf::VideoMode> getValidVideoModes()
{
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	// get the best bits per pixel supported
	unsigned int bpp = modes.front().bitsPerPixel;

	// remove all modes that have different bits per pixel
	auto end = std::remove_if(modes.begin(), modes.end(), [&](const sf::VideoMode &v)
	{
		return v.bitsPerPixel != bpp;
	});

	std::vector<sf::VideoMode> validModes;

	// populate new vector with found modes
	for (auto i = modes.begin(); i != end; ++i)
	{
		validModes.emplace_back(i->width, i->height, i->bitsPerPixel);
		//validModes.push_back(sf::VideoMode(i->width, i->height, bpp));
	}

	// reverse so worst is at front and best is at back
	std::reverse(validModes.begin(), validModes.end());

	return validModes;
}

void centreOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor((bounds.left + bounds.width) / 2.f), std::floor((bounds.top + bounds.height) / 2.f));
}

void centreOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor((bounds.left + bounds.width) / 2.f), std::floor((bounds.top + bounds.height) / 2.f));
}

void centreSpriteToWindow(sf::Sprite &sprite, const sf::RenderWindow &window, sf::Vector2f offset)
{
	sf::Vector2u origin = sprite.getTexture()->getSize() / 2u;
	sprite.setOrigin(static_cast<sf::Vector2f>(origin));

	sf::Vector2u centre = window.getSize() / 2u;
	sprite.setPosition(static_cast<sf::Vector2f>(centre) + offset);
}

void scaleSpriteToFitWindow(sf::Sprite &sprite, const sf::RenderWindow &window)
{
	sf::Vector2u tSize = sprite.getTexture()->getSize();
	sf::Vector2u wSize = window.getSize();

	float sx = static_cast<float>(wSize.x) / static_cast<float>(tSize.x);
	float sy = static_cast<float>(wSize.y) / static_cast<float>(tSize.y);

	sprite.setScale(sx, sy);
}

float randomize(float min, float max)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(generator);
}

int randomize(int min, int max)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}