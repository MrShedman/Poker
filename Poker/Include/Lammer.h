#pragma once

#include <SFML/Graphics.hpp>
#include <player.h>
#include <vector>

class Lammer : public sf::Transformable, public sf::Drawable
{
public:

	Lammer(){};
	Lammer(int pos, sf::Color color, char c);

	void setPlayers(std::vector<player*> *temp);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void updatePosition();
	void setPosition();

	void onResize(sf::Vector2u size);

	int position;
	int size;

private:
	float x;
	float y;
	float cx;
	float cy;

	char letter;

	bool firstDeal;

	std::vector<player*> *players;

	sf::Color color;

	sf::CircleShape circle;
	
	sf::Font font;
	sf::Text text;
};