#include "Address.h"

Address::Address(const mem_rep number)
{
	val = number;
}

void Address::set_dist(unsigned int dist)
{
	this->dist = dist;
}
unsigned int Address::get_dist(void) const
{
	return dist;
}