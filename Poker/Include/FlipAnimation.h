#pragma once

#include <Animation.h>

class Flip : public Animation
{	
private:
	sf::IntRect face;
	sf::IntRect back;

public:	

	void setFlipDirection(bool direction);

	void setTextureRects(sf::IntRect f1, sf::IntRect f2);

	void update();
};