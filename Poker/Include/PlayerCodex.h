#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include <memory>

#include <player.h>

#include <SceneNode.hpp>

class Deck;

class PlayerCodex : public SceneNode
{
public:

	PlayerCodex(Deck &deck)
		:
		deck(deck)
	{}

	void registerPlayer(const std::string name)
	{
		if (!containsPlayer(name))
		{
			std::unique_ptr<player> p(new player(deck, name));
			player* playerPtr = p.get();
			attachChild(std::move(p));
			players.push_back(playerPtr);
		}	
	}

	player& getPlayer(const std::string name)
	{
		return **std::find_if(players.begin(), players.end(),
			[&name](player* p) -> bool
		{
			return p->getName() == name;
		});
	}

private:

	bool containsPlayer(const std::string name) const
	{
		return 0 < std::count_if(players.begin(), players.end(),
			[&name](player* p) -> bool
		{
			return p->getName() == name;
		});
	}

	Deck &deck;
	std::vector<player*> players;
};