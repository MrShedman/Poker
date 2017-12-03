#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <Card.h>
#include <array>
#include <Table.h>
#include <Evaluator.h>
#include <State.hpp>
#include "Utility.h"

#include <SceneNode.hpp>

class Hand;

class Deck : public SceneNode
{
public:
	Deck(State::Context context);

	enum Action
	{
		CheckCall,
		Fold,
		Raise
	};

	struct PendingMove
	{
		PendingMove(Action action, float amount)
			:
			action(action),
			amount(amount)
		{}

		Action action;
		float amount;
	};

	std::vector<PendingMove> mPendingList;
	
	inline void applyMove(Action action, float amount = 0.f)
	{
		if (mPendingList.size() >= 9)
		{
			roundFinished();
		}

		mPendingList.push_back(PendingMove(action, amount));

		switch (action)
		{
		case CheckCall: std::cout << "check/call" << std::endl; break;
		case Fold: std::cout << "fold" << std::endl; break;
		case Raise: std::cout << "raise: " << amount << std::endl; break;
		}
	}

	const std::vector<PendingMove>& getPreviousMoves() const
	{
		return mPendingList;
	}

	PendingMove popLastMove() const
	{
		return mPendingList.back();
	}

	inline void roundFinished()
	{
		std::cout << "Round finished" << std::endl;

		mPendingList.clear();
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
		
	}

	inline void lol()
	{
		std::cout << "lol" << std::endl;
	}

	unsigned int getCategory() const
	{
		return Category::Deck;
	}

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (!board_old.empty())
		{
			for (auto &b : board_old)
			{
				target.draw(b->sprite, states);
			}
		}
	}

	void createDeck();

	template <typename T> void shuffle(T& Data);

	void dealCard(std::vector<Card*> &hand);

	Card dealCard()
	{
		Card c = deck.back();
		deck.pop_back();
		return c;
	}

	Card getRandomCard()
	{
		int r = randomize(0, deck.size() - 1);

		return deck[r];
	}

	bool containsCard(const Card& card)
	{
		return std::find(std::begin(deck), std::end(deck), card) != std::end(deck);
	}

	int evaluateHand(const Hand& hand, const std::array<Card, 5>& board);
	
	void testPreFlop();
	void testPostFlop();
	void testComparisons();

	sf::Vector2f cardPosition(int player, int card);

	void flop();

	void animate();

	void getBoardPosition();

	int rateHand(int h1, int h2);

	std::vector<Card*> board_old;
	std::array<Card, 5> board;

	int cardCount;
	int cardnum;
	int numberOfPlayers;

	std::vector<sf::Vector2f> position;

	std::vector<int> playerDealOrder;

	void onResize();

	sf::Font font;

private:

	unsigned int i;

	sf::RenderWindow &window;
	
	std::vector<Card> deck;

	float scale;

	sf::Texture texture;
};