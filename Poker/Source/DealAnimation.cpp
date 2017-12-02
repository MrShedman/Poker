#pragma once

#include <DealAnimation.h>


void Deal::setInitialPosition(sf::Vector2f init)
{
	initial = init;
}

void Deal::setDestination(sf::Vector2f dest)
{
	destination = dest;
	//distance = hypotf(destination.x - initial.x, destination.y - initial.y);
	//total = sf::seconds(distance/velocity);
}

void Deal::setRotation(float angle)
{
	rotatef = angle;
	rotate = true;
}

void Deal::setReverse(bool direction)
{
	reverse = direction;
}

void Deal::setFade(bool yes)
{
	fade = yes;
}

void Deal::update()
{
	factor = clock.getElapsedTime().asSeconds() / total.asSeconds();
	factor = smoothstep(factor);

	if( factor > 1.f )
	{
        factor = 1.f;
		stopped = true;
		initialized = false;
	}

	if (!reverse)
	{
		sprite->setPosition(initial + (destination - initial) * factor);
	}
	else
	{
		sprite->setPosition(destination + (initial - destination) * factor);
	}

	if (rotate)
	{
		sprite->setRotation(factor * rotatef);
	}

	if (scale)
	{
		sprite->setScale(factor * scalefX, factor * scalefY);
	}

	if (fade)
	{
		sprite->setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(factor * 255)));
	}
}

