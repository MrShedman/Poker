#include <Pot.h>

Pot::Pot(std::vector<player*> temp)
{
	players.clear();

	for (auto &i : temp)
	{
		players.push_back(i);
	}

	chips[0].first = 500;
	chips[0].second = 0;

	chips[1].first = 1000;
	chips[1].second = 0;

	chips[2].first = 5000;
	chips[2].second = 0;

	chips[3].first = 25000;
	chips[3].second = 0;

	chips[4].first = 100000;
	chips[4].second = 0;
}

void Pot::getChipCount(int mon)
{
	money = mon;
	start = money;
	int remainder = 0;
	bool solved = false;
	int it = chips.size() - 1;

	while (!solved && it >= 0)
	{
		if (money / chips[it].first >= 1)
		{
			chips[it].second = money / chips[it].first;

			remainder = money % chips[it].first;

			money -= chips[it].second * chips[it].first;

			if (remainder == 0)
			{
				solved = true;
			}
		}

		--it;
	}

	if (remainder != 0)
	{
		std::cout << "invalid chip count!" << std::endl;
	}

	std::cout << start << ": " << std::endl;

	for (int i = 0; i < 5; ++i)
	{
		std::cout << chips[i].first << " chips: " << chips[i].second << std::endl;
	}
}