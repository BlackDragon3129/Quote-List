#include <Library/Random.hpp>

#include <iostream>


using namespace QuoteList;


int Random::Randint(const int& min, const int& max)
{
	return min + rand() % (max - min);
}
