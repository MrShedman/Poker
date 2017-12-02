#pragma once

#include <player.h>

#include <iostream>
#include <array>
#include <vector>
#include <utility>

class Pot
{
public:
	Pot(){};

	Pot(std::vector<player*> temp);

	void getChipCount(int mon);

private:

	int start;
	int money;

	std::vector<player*> players;

	std::array<std::pair<int, int>, 5> chips;
};
