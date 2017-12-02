#include <MenuState.hpp>
#include <ResourceHolder.hpp>
#include <MusicPlayer.hpp>
#include <Button.hpp>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <Utility.h>

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::MenuBackground));

	scaleSpriteToFitWindow(mBackgroundSprite, *context.window);

	initializeButtons();

	context.music->play(Music::MenuTheme);
}

void MenuState::initializeButtons()
{
	Context context = getContext();

	mGUIContainer.clear();

	float y = 0.5f * context.window->getSize().y;
	float x = 0.5f * context.window->getSize().x;

	auto playButton = std::make_shared<GUI::Button>(context);
	playButton->setPosition(x - 120, y);
	playButton->setText("Play");
	playButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Game);
	});

	auto settingsButton = std::make_shared<GUI::Button>(context);
	settingsButton->setPosition(x - 120, y + 90);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(x - 120, y + 180);
	exitButton->setText("Exit");
	exitButton->setCallback([this]()
	{
		requestStackPop();
	});

	mGUIContainer.pack(playButton);
	mGUIContainer.pack(exitButton);
	mGUIContainer.pack(settingsButton);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time dt)
{
	mGUIContainer.update();
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}