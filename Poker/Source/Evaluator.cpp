#include <Evaluator.h>

namespace Eval
{
	std::string hand_rank(int val)
	{
		if (val > 6185) return("High Card");        // 1277 high card
		if (val > 3325) return("One Pair");         // 2860 one pair
		if (val > 2467) return("Two Pair");         //  858 two pair
		if (val > 1609) return("Three of a Kind");  //  858 three-kind
		if (val > 1599) return("Straight");         //   10 straights
		if (val > 322)  return("Flush");            // 1277 flushes
		if (val > 166)  return("Full House");       //  156 full house
		if (val > 10)   return("Four of a Kind");   //  156 four-kind
		return("Straight Flush");                   //   10 straight-flushes
	}

	unsigned find_fast(unsigned u)
	{
		unsigned a, b, r;
		u += 0xe91aaa35;
		u ^= u >> 16;
		u += u << 8;
		u ^= u >> 4;
		b = (u >> 8) & 0x1ff;
		a = (u + (u << 2)) >> 19;
		r = a ^ hash_adjust[b];
		return r;
	}

	int eval_5hand_fast(const std::array<int, 5>& c)
	{
		int q = (c[0] | c[1] | c[2] | c[3] | c[4]) >> 16;
		int s;

		if (c[0] & c[1] & c[2] & c[3] & c[4] & 0xf000)
		{
			return flushes[q];	// check for flushes and straight flushes
		}
		if ((s = unique5[q]))
		{
			return s;	// check for straights and high card hands
		}

		return hash_values[find_fast((c[0] & 0xff) * (c[1] & 0xff) * (c[2] & 0xff) * (c[3] & 0xff) * (c[4] & 0xff))];
	}

	int eval_7hand(const std::array<int, 7>& combined)
	{
		int i, j, q, best = 9999;

		std::array<int, 5> subhand;

		for (i = 0; i < 21; ++i)
		{
			for (j = 0; j < 5; ++j)
			{
				subhand[j] = combined[perm7[i][j]];
			}

			q = eval_5hand_fast(subhand);

			if (q < best)
			{
				best = q;
			}
		}

		return best;
	}
};