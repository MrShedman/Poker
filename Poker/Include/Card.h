#pragma once

#include <SFML/Graphics.hpp>
#include <FlipAnimation.h>
#include <DealAnimation.h>
#include <string>
#include <iostream>

class Card
{
public:

	int evalValue;
	
	std::string faceValue;

	Deal dealAnimation;
	Flip flipAnimation;

	sf::Sprite sprite;

private:


};

std::ostream& operator<< (std::ostream& os, const Card& card);
inline bool operator==(const Card& lhs, const Card& rhs);
inline bool operator!=(const Card& lhs, const Card& rhs);