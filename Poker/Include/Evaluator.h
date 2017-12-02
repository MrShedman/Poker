#pragma once

#include <Table.h>
#include <string>
#include <array>
	
namespace Eval
{
	extern int eval_7hand(const std::array<int, 7>& combined);

	extern std::string hand_rank(int val);

	extern unsigned find_fast(unsigned u);

	extern int eval_5hand_fast(const std::array<int, 5>& c);

};