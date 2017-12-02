#include <Player.h>
#include <Utility.h>
#include <memory>
#include <Button.hpp>


player::player(Deck &deck, std::string name)
	:
	deck(&deck),
	name(name)
{
	bankroll = 0;
	
	chipSetUp();
	updateBankroll(0);

	setCardPosition();
}

void player::requestToLeave()
{
	requestLeave = true;
}

bool player::hasRequestedLeave() const
{
	return requestLeave;
}

void player::setPosition(sf::Vector2f newPosition)
{
	setCardPosition();
	hand.onResize(static_cast<sf::Vector2u>(newPosition));
}

void player::handleEvent(const sf::Event& event)
{

}

template <typename T>
std::string player::toString(T& Data)
{
	std::stringstream convert;

	convert << std::fixed << std::setprecision(3) << Data;

	return convert.str();
}

void player::info()
{
	std::cout << "\nName: " << name << "\nBankroll: " << bankroll << std::endl;
	
	for (auto i : chips)
	{
		std::cout << i.first << " chips: " << i.second << std::endl;
	}
}

void player::setCardPosition()
{
	/*sf::Vector2f pos;
	pos.x = window.getSize().x * position.x;
	pos.y = window.getSize().y * position.y;

	position = pos;

	hand.position.clear();
	hand.position.resize(2);

	hand.position[0] = position + sf::Vector2f(20.f + cWidth / 4.f, - 60.f);
	hand.position[1] = position + sf::Vector2f(20.f + cWidth / 2.f, -60.f);*/
}

void player::chipSetUp()
{	
	chips[0].first = 500;
	chips[0].second = randomize(80, 240);

	chips[1].first = 1000;
	chips[1].second = randomize(40, 120);

	chips[2].first = 5000;
	chips[2].second = randomize(20, 60);

	chips[3].first = 25000;
	chips[3].second = randomize(10, 30);

	chips[4].first = 100000;
	chips[4].second = randomize(5, 15);
}

void player::updateBankroll(int money)
{
	bankroll += money;

	for (auto &i : chips)
	{
		bankroll += i.first * i.second;
	}

	std::string temp;

	temp = toString(bankroll);

	if (temp.size() > 3)
	{
		temp.insert(temp.end() - 3, ',');
		if (temp.size() > 7)
		{
			temp.insert(temp.end() - 7, ',');
		}
	}
}