#pragma once

#include <SFML/Graphics.hpp>
#include <FlipAnimation.h>
#include <DealAnimation.h>
#include <string>

struct cards
{
	int evalValue;
	
	std::string faceValue;

	Deal dealAnimation;
	Flip flipAnimation;

	sf::Sprite sprite;
};