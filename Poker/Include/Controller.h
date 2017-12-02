#pragma once

#include <ControllablePlayer.h>

class Controller
{
public:
	Controller(ControllablePlayer& player)
		:
		player(player)
	{}

	virtual ~Controller() 
	{

	}

	inline bool process()
	{
		if (enabled)
		{
			return implProcess();
		}
		else
		{
			return false;
		}
	}

	inline void enable()
	{
		enabled = true;
	}

	inline void disable()
	{
		enabled = false;
	}

	inline bool isEnabled() const
	{
		return enabled;
	}

protected:

	virtual bool implProcess() = 0;

	ControllablePlayer& player;

private:

	bool enabled = true;
};