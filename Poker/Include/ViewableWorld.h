#pragma once

#include <vector>
#include "SFML\System\Time.hpp"

class player;
class PlayerPanel;
class Deck;

class ViewableWorld
{
public: // view interface
	virtual const PlayerPanel& getPanel(int position) const = 0;
	virtual const player& getPlayer(std::string name) const = 0;
	virtual const Deck& getDeck() const = 0;
	virtual sf::Time getTimeElapsed() const = 0;
};