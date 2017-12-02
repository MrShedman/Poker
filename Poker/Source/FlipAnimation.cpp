#pragma once

#include <FlipAnimation.h>

void Flip::setFlipDirection(bool direction)
{
	flipDirection = direction;
}

void Flip::setTextureRects(sf::IntRect f1, sf::IntRect f2)
{
	face = f1;
	back = f2;
}

void Flip::update()
{
	factor = clock.getElapsedTime().asSeconds() / total.asSeconds();
	factor = smoothstep(factor);
	
	if (flipDirection)
	{
		sprite->setScale(static_cast<float>(std::abs(std::cos(factor * PI)) * scalefX), scalefY);
	}
	else
	{
		sprite->setScale(scalefX, static_cast<float>(std::abs(cos(factor * PI)) * scalefY));
	}

	if (factor > 0.5 && !hasFlipped)
	{
		sprite->setTextureRect(sprite->getTextureRect() == face ? back : face);
		hasFlipped = true;
	}

	if (factor > 1)
	{
		factor = 1.f;
		initialized = false;
		stopped = true;
		hasFlipped = false;
	}
}