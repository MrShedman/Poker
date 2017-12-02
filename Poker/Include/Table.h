#pragma once

#include <array>

// this is a table lookup for all "flush" hands (e.g.  both
// flushes and straight-flushes.  entries containing a zero
// mean that combination is not possible with a five-card
// flush hand.

extern std::array<int, 7937> flushes; 

// this is a table lookup for all non-flush hands consisting
// of five unique ranks (i.e.  either Straights or High Card
// hands).  it's similar to the above "flushes" array.

extern std::array<int,7937> unique5;

extern std::array<unsigned int, 512> hash_adjust; 

extern std::array<unsigned int, 8192> hash_values;

extern std::array<int, 13> primes;

extern std::array<std::array<int, 5>, 21> perm7;