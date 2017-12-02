#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Container.hpp>
#include <Button.hpp>

#include <CommandQueue.hpp>
#include <Command.hpp>
#include <SoundNode.hpp>

#include <SceneNode.hpp>

class player;

class PlayerPanel : public SceneNode
{
public:

	PlayerPanel(State::Context context, sf::FloatRect rect)
		:
		player(nullptr),
		text("Vacant", context.fonts->get(Fonts::Main))
	{
		createPanel(rect);

		auto playButton = std::make_shared<GUI::Button>(context);
		playButton->setSize(sf::Vector2f(rect.height, rect.height));
		playButton->setOrigin(sf::Vector2f(rect.height / 2.f, rect.height / 2.f));
		playButton->setPosition(rect.left, rect.top);
		playButton->setText("^_^");
		playButton->setCallback([this]()
		{
			if (hasPlayer())
			{
				getPlayer().info();
			}
		});

		mGUIContainer.pack(playButton);
	}

	bool hasPlayer()
	{
		return player != nullptr;
	}

	virtual bool isMarkedForRemoval() const
	{
		return false;
	}

	virtual bool isDestroyed() const
	{
		return false;
	}

	virtual void updateCurrent(sf::Time dt, CommandQueue& commands)
	{
	/*	Command command;
		command.category = Category::SoundEffect;
		command.action = derivedAction<SoundNode>(
			[](SoundNode& node, sf::Time)
		{
			node.playSound(SoundEffect::ID::Button);
		});

		commands.push(command);*/
	}

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(shape1, states);
		target.draw(shape2, states);
		target.draw(rectangle, states);
		target.draw(shape3, states);

		target.draw(text, states);

		target.draw(mGUIContainer, states);
	}

	player& getPlayer() const 
	{
		return *player;
	}

	void registerPlayer(player &p)
	{
		player = &p;
		text.setString(player->name);
	}

	void removePlayer()
	{
		player = nullptr;
		text.setString("Vacant");
	}

	void handleEvent(const sf::Event &event)
	{
		mGUIContainer.handleEvent(event);
	}

private:

	void createPanel(sf::FloatRect rect)
	{
		float radius = rect.height / 2.f;
		sf::Vector2f position(rect.left, rect.top);

		shape1 = sf::CircleShape(radius);
		shape1.setOrigin(radius, radius);
		shape1.setPosition(position);
		shape1.setFillColor(sf::Color(110, 110, 110));

		shape2 = sf::CircleShape(radius);
		shape2.setOrigin(radius, radius);
		shape2.setPosition(position + sf::Vector2f(rect.width - rect.height, 0.f));
		shape2.setFillColor(sf::Color(110, 110, 110));

		rectangle = sf::RectangleShape(sf::Vector2f(rect.width - rect.height, rect.height));
		rectangle.setPosition(position + sf::Vector2f(0.f, -radius));
		rectangle.setFillColor(sf::Color(110, 110, 110));

		shape3 = sf::CircleShape(radius * 0.8f);
		shape3.setOrigin(radius * 0.8f, radius * 0.8f);
		shape3.setPosition(position);
		shape3.setFillColor(sf::Color::Black);

		text.setPosition(position + sf::Vector2f(radius * 1.1f, -radius * 1.1f));
	}

	player* player;

	GUI::Container mGUIContainer;

	sf::CircleShape shape1;
	sf::CircleShape shape2;
	sf::CircleShape shape3;
	sf::RectangleShape rectangle;
	sf::Text text;
};