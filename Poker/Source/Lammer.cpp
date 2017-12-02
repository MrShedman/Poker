#include <Lammer.h>

Lammer::Lammer(int pos, sf::Color col, char c) : position(pos - 1), firstDeal(false)
{
	x = 0;
	y = 0;
	cx = 640;
	cy = 360;
	color = col;
	letter = c;

	circle = sf::CircleShape(10);
	circle.setFillColor(color);
	circle.setOutlineThickness(1);
	circle.setOutlineColor(sf::Color::Black);

	font.loadFromFile("Fonts/roboto.ttf");

	text.setFont(font);
	text.setString(letter);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(15);

	players = nullptr;

	setPosition();
}

void Lammer::setPlayers(std::vector<player*> *temp)
{
	players = temp;
	size = players->size();
}

void Lammer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(circle, states);
	target.draw(text, states);
}

void Lammer::updatePosition()
{
	size = players->size();

	firstDeal = true;

	position++;
	
	if (position >= size)
	{
		position = 0;
	}

	if (position < 0)
	{
		int temp = position;
		position = players->size() + temp;
	}

	setPosition();
}

void Lammer::onResize(sf::Vector2u size)
{
	cx = static_cast<float>(size.x/2);
	cy = static_cast<float>(size.y/2);

	setPosition();
}

void Lammer::setPosition()
{
	if (firstDeal)
	{
		player *temp;

		std::cout << "position" << position << std::endl;

		temp = (*players)[position];

		x = ((cx - 15) - temp->hand.position[0].x) * 0.30f + temp->hand.position[0].x;
		y = ((cy - 15) - temp->hand.position[0].y) * 0.45f + temp->hand.position[0].y;

	
		circle.setPosition(x, y);
		text.setPosition(x + 5, y + 1);	
	}
	else
	{
		circle.setPosition(cx - 20, cy - 170);
		text.setPosition(cx - 15, cy - 170);
	}
}