#pragma once

#include <SFML/Graphics.hpp>

#define PI (4 * atan(1))

class Animation
{
protected:

	float smoothstep(float fx);

	bool initialized;
	bool stopped;

	float factor;
	float scalefX;
	float scalefY;
	float rotatef;

	bool scale;
	bool rotate;
	bool flipDirection;
	bool hasFlipped;
	bool reverse;

	sf::Clock clock;
	sf::Time total;
	sf::Time delay;

	sf::RenderWindow *windowPointer;

	sf::Sprite *sprite;

public:

	sf::Vector2f initial;
	sf::Vector2f destination;

	Animation();

	void setSprite(sf::Sprite *spr);

	virtual void setScale(float sizeX, float sizeY);

	virtual void setTime(float finish, float wait);
	
	virtual void update() = 0;

	bool isRunning();

	void draw();

	void start();
};