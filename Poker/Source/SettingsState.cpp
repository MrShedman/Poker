#include <SettingsState.hpp>
#include <Utility.h>
#include <ResourceHolder.hpp>
#include <MusicPlayer.hpp>
#include <Slider.h>
#include <Toggle.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
, mIsChanged(false)
{
	desiredMode.width = context.window->getSize().x;
	desiredMode.height = context.window->getSize().y;
	desiredMode.bitsPerPixel = 32;

	mBackgroundSprite.setTexture(context.textures->get(Textures::MenuBackground));

	scaleSpriteToFitWindow(mBackgroundSprite, *context.window);

	validModes = getValidVideoModes();

	initializeButtons();
}

void SettingsState::initializeButtons()
{
	mGUIContainer.clear();

	float y = 0.5f * getContext().window->getSize().y;
	float x = 0.5f * getContext().window->getSize().x;
	
	std::vector<int> iVolume;

	for (int i = 0; i <= 100; ++i)
	{
		iVolume.push_back(i);
	}

	auto musicVolume = std::make_shared<GUI::Slider<int>>(getContext());
	musicVolume->setPosition(sf::Vector2f(x - 250, y));
	musicVolume->setPossibleValues(iVolume);
	musicVolume->setCurrentValue(static_cast<int>(getContext().music->getVolume()));
	musicVolume->setDisplayFunction([](int d)
	{
		return "Music: " + toString(d);
	});
	musicVolume->setCallback([this](int volume)
	{
		getContext().music->setVolume(static_cast<float>(volume));
	});

	auto soundVolume = std::make_shared<GUI::Slider<int>>(getContext());
	soundVolume->setPosition(sf::Vector2f(x + 10, y));
	soundVolume->setPossibleValues(iVolume);
	soundVolume->setCurrentValue(static_cast<int>(getContext().sounds->getVolume()));
	soundVolume->setDisplayFunction([](int d)
	{
		return "SFX: " + toString(d);
	});
	soundVolume->setCallback([this](int volume)
	{
		getContext().sounds->setVolume(static_cast<float>(volume));
	});

	auto resolution = std::make_shared<GUI::Slider<sf::VideoMode>>(getContext());
	resolution->setSize(sf::Vector2f(500, 70));
	resolution->setPosition(sf::Vector2f(x - 250, y + 90));
	resolution->setPossibleValues(validModes);
	resolution->setCurrentValue(desiredMode);
	resolution->setDisplayFunction([](sf::VideoMode d)
	{
		return toString(d.width) + "x" + toString(d.height);
	});
	resolution->setCallback([this](int id)
	{
		desiredMode = validModes[id];
	});

	auto apply = std::make_shared<GUI::Button>(getContext());
	apply->setPosition(x + 10, y + 270);
	apply->setText("Apply");
	apply->setCallback([this]()
	{
		mIsChanged = true;
	});

	auto toggleVsyncButton = std::make_shared<GUI::Toggle>(getContext());
	toggleVsyncButton->setPosition(x - 250, y + 180);
	toggleVsyncButton->setText("vSync: OFF", "vSync: ON");
	toggleVsyncButton->setState(true);
	toggleVsyncButton->setCallback([this](bool flag)
	{
		
	});

	auto toggleFS = std::make_shared<GUI::Toggle>(getContext());
	toggleFS->setPosition(x + 10, y + 180);
	toggleFS->setText("Windowed", "Full Screen");
	toggleFS->setState(true);
	toggleFS->setCallback([this](bool flag)
	{
		mIsChanged = true;
	});

	auto backButton = std::make_shared<GUI::Button>(getContext());
	backButton->setPosition(x - 250, y + 270);
	backButton->setText("Back");
	backButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Menu);
	});

	mGUIContainer.pack(musicVolume);
	mGUIContainer.pack(soundVolume);
	mGUIContainer.pack(resolution);
	mGUIContainer.pack(apply);
	mGUIContainer.pack(toggleFS);
	mGUIContainer.pack(toggleVsyncButton);
	mGUIContainer.pack(backButton);
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time)
{
	mGUIContainer.update();
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);

	if (mIsChanged)
	{
		applyChanges();
	}

	return false;
}

void SettingsState::applyChanges()
{
	sf::RenderWindow& window = *getContext().window;
	
	//sf::Uint32 style = getContext().settings->fullScreen ? sf::Style::Fullscreen : sf::Style::Close;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(desiredMode, "Platformer", sf::Style::Close, settings);

	scaleSpriteToFitWindow(mBackgroundSprite, *getContext().window);
		
	initializeButtons();
	
	//window.setVerticalSyncEnabled(getContext().settings->vSync);
	//window.setKeyRepeatEnabled(getContext().settings->keyRepeat);

//	window.setIcon(icon_image.width, icon_image.height, icon_image.pixel_data);

	mIsChanged = false;
}