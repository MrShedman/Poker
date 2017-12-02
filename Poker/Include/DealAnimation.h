#pragma once

#include <Animation.h>

class Deal : public Animation
{
private:
	bool fade;

public:
	
	void setInitialPosition(sf::Vector2f init);

	void setDestination(sf::Vector2f dest);

	void setRotation(float angle);

	void setReverse(bool direction);

	void setFade(bool yes);

	void update();
};