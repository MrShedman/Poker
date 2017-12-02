#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <StateStack.hpp>

#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>

class Application
{
public:
	Application(unsigned int width, unsigned int height);

	void						run();

private:

	void						getInput();
	void						update(sf::Time dt);
	void						render();

	void						updateStatistics(sf::Time dt);
	void						loadResources();
	void						close();

private:

	static const sf::Time		timePerFrame;

	sf::RenderWindow			window;

	TextureHolder				mTextures;
	ImageHolder					mImages;
	FontHolder					mFonts;
	MusicPlayer					mMusic;
	SoundPlayer					mSounds;

	StateStack					mStateStack;

	sf::Text					mStatisticsText;
	sf::Time					mStatisticsUpdateTime;
	std::size_t					mStatisticsNumFrames;
};