#include "Analysis.h"
#include <IO_Manager.h>
#include <limits>

Analysis::Analysis(void)
{
}

Analysis::Analysis(const char *filename)
{
	IO_Manager *m = new IO_Manager(std::string(filename));
	while (Req *req = m->read_next_req())
	{
		v.push_back(*req);
		delete req;
	}
	delete m;
}

Analysis::~Analysis(void)
{
}

void Analysis::calc_stack_dist(void)
{

}

std::vector<Req> Analysis::requests(void) const
{
	return v;
}
Req Analysis::req(int i) const
{
	if ((i < 0) || (i >= v.size()))
	{
		std::cerr << "Req Analysis::req(int i) const : index out of range" << std::endl;
		//throw std::exception("Req Analysis::req(int i) const : index out of range");
	}
	return v[i];
}
Address Analysis::addr(int i) const
{
	return req(i).addr;
}
MyTime Analysis::time(int i) const
{
	return req(i).time;
}
req_size Analysis::size(int i) const
{
	return req(i).size;
}
req_type Analysis::type(int i) const
{
	return req(i).type;
}
Req Analysis::operator [] (int i) const
{
	return req(i);
}

Analysis::AddressAnalisys::AddressAnalisys(void) : v() {}
Analysis::AddressAnalisys::AddressAnalisys(const Analysis &analis)
{
	for (int i = 0; i < analis.requests().size(); i++)
	{
		v.push_back(analis.addr(i));
	}
}
std::vector<Address> Analysis::AddressAnalisys::addresses(void) const
{
	return v;
}

void Analysis::AddressAnalisys::calc_stack_dist(void)
{
	typedef AvlTree<Address, unsigned int> AVL;
	const unsigned int N = v.size();			// amount of links (addresses)
	AVL cache;									// contains all addresses that are currently located at the stack (cache)
	for (unsigned int i = 0; i < N; i++)
	{
		if (AVL *node = cache.find(v[i]))		// v[i] is already in the cache
		{
			node->value = i;
		}
		else
		{
			cache.add(v[i], i);
		}
	}
}

/*
	Defenition of class AvlKey
	AvlKey is used only in "void cals_stack_dist(void)"
	AvlKey is a unique key in AVL tree
*/
Analysis::AddressAnalisys::AvlKey::AvlKey(unsigned int min, unsigned int max) : min(min), max(max) {}
bool Analysis::AddressAnalisys::AvlKey::operator<(const AvlKey &key) const
{
	return this->max < key.min;
}
bool Analysis::AddressAnalisys::AvlKey::operator==(const AvlKey &key) const
{
	return (this->min == key.min) && (this->max == key.max);
}
bool Analysis::AddressAnalisys::AvlKey::operator<=(const AvlKey &key) const
{
	return operator <(key) || operator==(key);
}
bool Analysis::AddressAnalisys::AvlKey::operator>(const AvlKey &key) const
{
	return ! operator <=(key);
}
bool Analysis::AddressAnalisys::AvlKey::operator>=(const AvlKey &key) const
{
	return ! operator <(key);
}
bool Analysis::AddressAnalisys::AvlKey::operator!=(const AvlKey &key) const
{
	return ! operator ==(key);
}
/*
	Definition of class AvlKey is over.
*/