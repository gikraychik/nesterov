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
	const int N = v.size();
	const unsigned int inf = std::numeric_limits<unsigned int>::max();  // max value of unsigned int
	int **P = new int *[N+1];
	int **B = new int *[N+1];
	for (int i = 0; i < N+1; i++)
	{
		P[i] = new int[N+1];
		B[i] = new int[N+1];
	}
	for (int t = 0; t < N; t++)
	{
		bool P_defined = false;
		for (int i = t; i >=0 ; i--)
		{
			if (v[t] == v[i]) { P[t][t] = i; P_defined = true; break; }
		}
		if (!P_defined) { P[t][t] = inf; }
		
		// next calculating dist(t)
		if (!P_defined)
		{
			v[t].set_dist(inf);
		}
		else
		{
			unsigned int sum = 0;
			for (int i = P[t][t]; i < t; i++)
			{
				if (B[t][i] == 1) { sum++; }
			}
			v[t].set_dist(sum);
		}

		// updating stage
		for (int i = 0; i <= t; i++)
		{
			if (i == t) { B[t+1][i] = 1; }
			else if (i == P[t][t]) { B[t+1][i] = 0; }
			else { B[t+1][i] = B[t][i]; }
			P[t+1][i] = (v[i] == v[t]) ? t : P[t][i];
		}
	}

	// cleaning up memory
	for (int i = 0; i < N+1; i++)
	{
		delete[] P[i];
		delete[] B[i];
	}
	delete[] P;
	delete[] B;
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