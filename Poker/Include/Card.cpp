#include "Card.h"

std::ostream& operator<< (std::ostream& os, const Card& card) 
{ 
	os << card.evalValue << " " << card.faceValue << "\n"; 
	return os; 
}

inline bool operator==(const Card& lhs, const Card& rhs) { return lhs.evalValue == rhs.evalValue; }
inline bool operator!=(const Card& lhs, const Card& rhs) { return !operator==(lhs, rhs); }