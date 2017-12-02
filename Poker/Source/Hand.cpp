#include <Hand.h>

Hand::Hand()
{
	//getCardPosition();
}

Hand::~Hand()
{

}

void Hand::onResize(sf::Vector2u size)
{
	//getCardPosition();

	if (!pHand.empty())
	{
		for (i = 0; i < 2; ++i)
		{
			if (pHand[i]->dealAnimation.isRunning())
			{
				pHand[i]->dealAnimation.setInitialPosition(sf::Vector2f(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2 - 255)));
				pHand[i]->dealAnimation.setDestination(position[i]);
			}
			else
			{
				pHand[i]->sprite.setPosition(position[i]);
			}
		}
	}	
}

void Hand::dealAnim()
{
	for (i = 0; i < 2; ++i)
	{
		pHand[i]->dealAnimation.setDestination(position[i]);
		pHand[i]->dealAnimation.start();
	}
}

void Hand::flipAnim()
{
	for (auto &p : pHand)
	{
		p->flipAnimation.start();
	}
}

void Hand::getHandRank()
{
	//handValue = point->rateHand(pHand[0]->evalValue, pHand[1]->evalValue, this);
	//handRank = hand_rank(handValue);
}