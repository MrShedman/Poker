#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <utility>
#include <array>
#include <string>
#include <sstream>
#include <iomanip>

#include <Deck.h>
#include <Hand.h>
#include <Container.hpp>
#include <Utility.h>
#include <ControllablePlayer.h>
#include <ViewableWorld.h>
#include <Command.hpp>
#include <CommandQueue.hpp>
#include <SceneNode.hpp> 

#include <AI.h>

class Controller;

class player : public ControllablePlayer, public SceneNode
{
public:
	player(Deck &deck, std::string name);

	sf::Vector2f position;

	std::string name;
	int index;
	int bankroll;
	std::array<std::pair<int, int>, 5> chips;

	void updateBankroll(int money);

	void setPosition(sf::Vector2f newPosition);

	void handleEvent(const sf::Event& event);
	
	inline bool isMarkedForRemoval() const
	{
		return false;
	}

	inline bool isDestroyed() const
	{
		return false;
	}

	inline void updateCurrent(sf::Time dt, CommandQueue& commands)
	{
	/*	Command command;
		command.category = Category::Deck;

		auto finder = [this](Deck& d, sf::Time)
		{
			d.lol();
		};

		command.action = derivedAction<Deck>(finder);

		commands.push(command);*/
	}

	inline void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (!hand.pHand.empty())
		{
			target.draw(hand.pHand[0]->sprite, states);
			target.draw(hand.pHand[1]->sprite, states);
		}
	}

	inline std::string getName() const
	{
		return name;
	}

	void requestToLeave() override;

	bool hasRequestedLeave() const override;

	inline void check() override
	{
		deck->applyMove(Deck::Action::CheckCall);
	}

	inline void fold() override
	{
		deck->applyMove(Deck::Action::Fold);
	}

	inline void raise(float amount) override
	{
		deck->applyMove(Deck::Action::Raise, amount);
	}

	inline float getHandRank() const override
	{
		return randomize(0.f, 100.f);
	}

	inline float getChipCount() const override
	{
		return bankroll;
	}

	inline const player& getPlayer() const override
	{
		return *this;
	}

	inline void setController(const ViewableWorld &world)
	{
		std::unique_ptr<AI> control(new AI(*this, world));
			
		controller = control.get();

		attachChild(std::move(control));
	}

	inline bool process()
	{
		return controller->process();
	}

	void info();

	void setCardPosition();

	Deck *deck;

	Hand hand;

	AI* controller;

	template <typename T> std::string toString(T& Data);

	void chipSetUp();
};