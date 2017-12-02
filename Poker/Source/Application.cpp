#include <Application.h>
#include <cmath>

#include <State.hpp>
#include <GameState.hpp>
#include <MenuState.hpp>
#include <PauseState.hpp>
#include <SettingsState.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>
#include <Utility.h>

const sf::Time Application::timePerFrame = sf::seconds(1.f / 60.f);

Application::Application(unsigned int width, unsigned int height)
:
mTextures(),
mImages(),
mFonts(),
mStateStack(State::Context(window, mTextures, mImages, mFonts, mMusic, mSounds)),
mStatisticsText(),
mStatisticsUpdateTime(),
mStatisticsNumFrames(0)
{
	/*sf::VideoMode mode(w, h, sf::VideoMode::getFullscreenModes()[0].bitsPerPixel);

	if (!mode.isValid())
	{
		std::vector<sf::VideoMode> validModes = getValidVideoModes();

		auto low = std::lower_bound(validModes.begin(), validModes.end(), mode);

		low--;

		mode.bitsPerPixel = low->bitsPerPixel;
		mode.width = low->width;
		mode.height = low->height;
	}*/

	//sf::Uint32 style = mSettings.fullScreen ? sf::Style::Fullscreen : sf::Style::Close;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(sf::VideoMode(width, height), "Platformer", sf::Style::Close, settings);

	loadResources();

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(30u);
	mStatisticsText.setFillColor(sf::Color::Yellow);

	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<SettingsState>(States::Settings);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);

	mStateStack.pushState(States::Menu);
}

void Application::getInput()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			close();
		}

		mStateStack.handleEvent(event);
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	window.clear();

	mStateStack.draw();

	window.setView(window.getDefaultView());
	window.draw(mStatisticsText);

	window.display();
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{
		sf::Time dt;
		dt = clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;

			getInput();
			update(timePerFrame);

			if (mStateStack.isEmpty())
			{
				close();
			}
		}

		updateStatistics(dt);
		render();
	}
}

void Application::loadResources()
{
	mFonts.load(Fonts::Main, "Fonts/Sansation.otf");

	mTextures.load(Textures::GameBackground, "Textures/GameBackground.png");
	mTextures.load(Textures::MenuBackground, "Textures/MenuBackground.png");
	mTextures.load(Textures::CardAtlas,		 "Textures/CardAtlas.png");
	mTextures.load(Textures::Table,			 "Textures/Table.png");

	mImages.load(Images::DayNightPalette, "Textures/DayNightColourRamp.png");
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.f))
	{
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.f);
		mStatisticsNumFrames = 0;
	}
}

void Application::close()
{
	window.close();
}