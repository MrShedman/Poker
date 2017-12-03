#pragma once

#include <SFML/Graphics.hpp>
#include <Deck.h>

class Hand
{
public:
	Hand();

	~Hand();
		
	std::vector<Card*> pHand;

	std::array<Card, 2> cards;

	void dealAnim();

	void flipAnim();

	void getCardPosition();

	void getHandRank();

	std::vector<sf::Vector2f> position;

	int handValue;
	std::string handRank;

	void onResize(sf::Vector2u size);

private:

	unsigned int i;
};