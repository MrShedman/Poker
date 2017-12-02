#pragma once

#include <Controller.h>
#include <ViewableWorld.h>
#include <SceneNode.hpp>

class AI : public Controller, public SceneNode
{
public:

	AI(ControllablePlayer& player, const ViewableWorld& world)
		:
		Controller(player),
		world(world),
		requiresUpdate(true)
	{}

	bool implProcess();

private:

	const ViewableWorld& world;
	bool requiresUpdate;
	sf::Time chooseTime;
};