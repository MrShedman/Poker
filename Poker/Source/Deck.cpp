#include <Deck.h>
#include <Utility.h>
#include <ResourceHolder.hpp>
#include <random>
#include "Hand.h"

void Deck::animate()
{
	for (auto &i : deck)
	{
		i.dealAnimation.draw();
		i.flipAnimation.draw();		
	}
}

Deck::Deck(State::Context context)
:
window(*context.window),
font(context.fonts->get(Fonts::Main)),
texture(context.textures->get(Textures::CardAtlas))
{
	texture.setSmooth(true);
	numberOfPlayers = 0;

	applyMove(CheckCall);

	testComparisons();
}

template <typename T>
void Deck::shuffle(T& Data)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle (Data.begin(), Data.end(), gen);
}

void Deck::createDeck()
{
	cardnum = 51;
	cardCount = 0;

    int s, r, n = 0, suit = 0x8000;

	const int width = 154;
	const int height = 218;
	int dx = 0;
	int dy = 0;

	scale = 0.5f;

	std::array<std::string, 4> suit_text = {{ "Clubs", "Diamonds", "Hearts", "Spades" }};
	std::array<std::string, 13> rank_text = {{ "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" }};

	playerDealOrder.clear();
	board_old.clear();
	deck.clear();
	deck.resize(52);

	sf::IntRect back(2002, 0, 154, 217);
	
    for (s = 0; s < 4; ++s, suit >>= 1, dy += height)
	{
		for (r = 0, dx = 0; r < 13; ++r, ++n, dx += width)
		{
			deck[n].evalValue = primes[r] | (r << 8) | suit | (1 << (16 + r));
			deck[n].faceValue = rank_text[r] + " of " + suit_text[s];

			sf::IntRect front(dx, dy, width, height);

			deck[n].sprite.setTexture(texture);
			deck[n].sprite.setTextureRect(back);
			deck[n].sprite.setScale(0.f, 0.f);
			deck[n].sprite.setPosition(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2 - 255));
			deck[n].sprite.setOrigin(width/2.f, height/2.f);

			deck[n].dealAnimation.setInitialPosition(deck[n].sprite.getPosition());
			deck[n].dealAnimation.setScale(scale, scale);
			deck[n].dealAnimation.setRotation(360.f);
			deck[n].dealAnimation.setFade(false);
			deck[n].dealAnimation.setReverse(false);

			deck[n].flipAnimation.setScale(scale, scale);
			deck[n].flipAnimation.setTextureRects(front, back);
			deck[n].flipAnimation.setFlipDirection(true);
		}
	}

	shuffle(deck);
}

void Deck::dealCard(std::vector<Card*> &hand)
{
	int size = 0;

	hand.push_back(&deck[cardnum--]);

	size = hand.size() - 1;
	
	hand[size]->dealAnimation.setSprite(&hand[size]->sprite);
	hand[size]->dealAnimation.setTime(0.7f, (51 - cardnum)/4.f);

	hand[size]->flipAnimation.setSprite(&hand[size]->sprite);
	hand[size]->flipAnimation.setTime(0.4f, randomize(0.f, 0.6f));
}

void Deck::testPreFlop()
{

}

void Deck::testPostFlop()
{

}

void Deck::testComparisons()
{
	// make a fresh new deck
	createDeck();

	const int num_players = 3;

	std::vector<Hand> player_hands;

	player_hands.resize(num_players);

	for (auto& h : player_hands)
	{
		h.cards[0] = dealCard();
	}

	for (auto& h : player_hands)
	{
		h.cards[1] = dealCard();
	}

	// burn a card before flop
	deck.pop_back();

	// 3 card flop
	for (int i = 0; i < 3; ++i)
	{
		board[i] = dealCard();
	}

	// evaluate hand positions

	const int num_evals = 10000;

	std::vector<int> wins(num_players);
	std::vector<int> draws(num_players);

	for (int i = 0; i < num_evals; ++i)
	{
		std::array<Card, 5> temp_board = board;
		temp_board[3] = getRandomCard();
		temp_board[4] = getRandomCard();

		int best_rank = 9999;
		int best_j = 0;

		for (int j = 0; j < num_players; ++j)
		{
			std::array<int, 7> full_board;
			full_board[0] = temp_board[0].evalValue;
			full_board[1] = temp_board[1].evalValue;
			full_board[2] = temp_board[2].evalValue;
			full_board[3] = temp_board[3].evalValue;
			full_board[4] = temp_board[4].evalValue;
			full_board[5] = player_hands[j].cards[0].evalValue;
			full_board[6] = player_hands[j].cards[1].evalValue;

			int rank = Eval::eval_7hand(full_board);

			if (rank < best_rank)
			{
				best_rank = rank;
				best_j = j;
			}
		}

		wins[best_j]++;
	}

	std::cout << "Flop:\n";
	std::cout << board[0] << ", ";
	std::cout << board[1] << ", ";
	std::cout << board[2] << "\n";

	for (int i = 0; i < num_players; ++i)
	{
		float percent = wins[i] * 100.0f / (float)num_evals;

		std::cout << "Player: " << i << "\n";
		std::cout << "C1: " << player_hands[i].cards[0];
		std::cout << "C2: " << player_hands[i].cards[1];
		std::cout << "Win%: " << percent << "\n";
	}
}

void Deck::flop()
{	
	for (i = 0; i < 5; ++i)
	{
		dealCard(board_old);	
	}

	getBoardPosition();
}

void Deck::getBoardPosition()
{
	position.clear();
	position.resize(5);

	for (i = 0; i < board_old.size(); ++i)
	{
		position[i] = cardPosition(9, i);
		board_old[i]->dealAnimation.setDestination(position[i]);		
	}
}

void Deck::onResize()
{	
	if (!board_old.empty())
	{
		for (i = 0; i < board_old.size(); ++i)
		{
			position[i] = cardPosition(9, i);
	
			if (board_old[i]->dealAnimation.isRunning())
			{
				board_old[i]->dealAnimation.setInitialPosition(sf::Vector2f(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2 - 255)));
				board_old[i]->dealAnimation.setDestination(position[i]);
			}
			else
			{				
				board_old[i]->sprite.setPosition(position[i]);
			}
		}
	}
}

sf::Vector2f Deck::cardPosition(int player, int card)
{
	float x = 0;
	float y = 0;
	float w = static_cast<float>(window.getSize().x / 2);
	float h = static_cast<float>(window.getSize().y / 2);

	const float width = 156.f;
	const float height = 220.f;

	if (player == 0)
	{
		switch (card)
		{
		//player 1
		case 0: x = w + 190 - (width/8); y = h - 260; break;
		case 1: x = w + 190 + (width/8); y = h - 260; break;
		}
	}
	else if (player == 1)
	{	
		switch (card)
		{
		//player 2
		case 0: x = w + 400 - (width/8); y = h - 210; break;
		case 1: x = w + 400 + (width/8); y = h - 210; break;
		}	
	}
	else if (player == 2)
	{	
		switch (card)
		{
		//player 3
		case 0: x = w + 490 - (width/8); y = h + 10; break;
		case 1: x = w + 490 + (width/8); y = h + 10; break;
		}	
	}
	else if (player == 3)
	{	
		switch (card)
		{
		//player 4
		case 0: x = w + 290 - (width/8); y = h + 140; break;
		case 1: x = w + 290 + (width/8); y = h + 140; break;
		}	
	}
	else if (player == 4)
	{	
		switch (card)
		{
		//player 5
		case 0: x = w + 000 - (width/8); y = h + 170; break;
		case 1: x = w + 000 + (width/8); y = h + 170; break;
		}	
	}
	else if (player == 5)
	{	
		switch (card)
		{
		//player 6
		case 0: x = w - 290 - (width/8); y = h + 140; break;
		case 1: x = w - 290 + (width/8); y = h + 140; break;
		}	
	}
	else if (player == 6)
	{	
		switch (card)
		{
		//player 7
		case 0: x = w - 490 - (width/8); y = h + 10; break;
		case 1: x = w - 490 + (width/8); y = h + 10; break;
		}	
	}
	else if (player == 7)
	{	
		switch (card)
		{
		//player 8
		case 0: x = w - 400 - (width/8); y = h - 210; break;
		case 1: x = w - 400 + (width/8); y = h - 210; break;
		}	
	}
	else if (player == 8)
	{	
		switch (card)
		{
		//player 9
		case 0: x = w - 190 - (width/8); y = h - 260; break;
		case 1: x = w - 190 + (width/8); y = h - 260; break;
		}	
	}
	else if (player == 9)
	{	
		switch (card)
		{
		//board
		case 0: x = w - (width/1); break;
		case 1: x = w - (width/2); break;
		case 2: x = w;			   break;
		case 3: x = w + (width/2); break;
		case 4: x = w + (width/1); break;
		}
		y = h - (height/5);
	}

	return sf::Vector2f(x, y);
}

int Deck::rateHand(int h1, int h2)
{	
	std::array<int, 7> temp;

	temp[0] = h1;
	temp[1] = h2;

	for (int i = 2; i < 7; ++i)
	{
		temp[i] = board_old[i - 2]->evalValue;	
	}

	int rank = Eval::eval_7hand(temp);

	return rank;
}