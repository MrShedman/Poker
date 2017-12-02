#include <Animation.h>

Animation::Animation()
{
	initialized = false;
	stopped = true;
	reverse = false;
	scale = false;
	rotate = false;
	hasFlipped = false;
	flipDirection = true;
	factor = 0.f;
	delay = sf::seconds(0.f);
}

void Animation::setSprite(sf::Sprite *spr)
{
	sprite = spr;
}

float Animation::smoothstep(float fx)
{
	return fx * fx * fx * (fx * (fx * 6 - 15) + 10);
}

void Animation::setScale(float sizeX, float sizeY)
{
	scalefX = sizeX;
	scalefY = sizeY;
	scale = true;
}

void Animation::setTime(float finish, float wait)
{
	total = sf::seconds(finish);
	delay = sf::seconds(wait);
}

void Animation::draw()
{
	if (!stopped)
	{
		if (!initialized)
		{
			if (clock.getElapsedTime() >= delay)
			{
				clock.restart();
				update();
				initialized = true;
			}
		}
		else
		{
			update();
		}
	}
}

bool Animation::isRunning()
{
	return !stopped;
}

void Animation::start()
{
	if (stopped)
	{
		stopped = false;
		clock.restart();
	}
}