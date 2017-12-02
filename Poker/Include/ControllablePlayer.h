#pragma once

class player;

class ControllablePlayer
{
public:
	virtual void check() = 0;
	virtual void fold() = 0;
	virtual void raise(float amount) = 0;
	virtual void requestToLeave() = 0;

	virtual bool hasRequestedLeave() const = 0;
	virtual float getChipCount() const = 0;
	virtual float getHandRank() const = 0;
	virtual const class player& getPlayer() const = 0;

protected:

	bool requestLeave = false;
};