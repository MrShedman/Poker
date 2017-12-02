#include "AI.h"
#include "Player.h"

#include <iostream>

bool AI::implProcess()
{
	//std::cout << player.getPlayer().getName() << std::endl;

	if (player.hasRequestedLeave())
	{
		//world.getPanel(2)->removePlayer();
	}

	if (requiresUpdate)
	{
		chooseTime = sf::seconds(randomize(2.f, 6.f));
		requiresUpdate = false;
	}

	if (world.getTimeElapsed() < chooseTime)
	{
		return false;
	}
	else
	{
		requiresUpdate = true;
	}

	std::cout << chooseTime.asSeconds() << std::endl;
	//std::cout << player.getPlayer().getName() << "	";

	auto m = world.getDeck().popLastMove();

	int rand = randomize(0, 100);

	if (rand % 7 == 1)
	{
		player.fold();
	}
	else if (m.action == Deck::Action::CheckCall)
	{
		if (player.getHandRank() > 60.f)
		{
			player.raise(3.f);
		}
		else
		{
			player.check();
		}
	}
	else if (m.action == Deck::Action::Fold)
	{
		if (player.getHandRank() < 20.f)
		{
			player.fold();
		}
		else
		{
			player.check();
		}
	}
	else if (m.action == Deck::Action::Raise)
	{
		if (player.getHandRank() > 80.f)
		{
			player.raise(m.amount * 2.f);
		}
		else
		{
			player.check();
		}
	}

	return true;
}