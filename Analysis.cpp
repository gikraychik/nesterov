#include "Analysis.h"
#include <IO_Manager.h>
#include <limits>
#include <set>
#include <map>
#include <vector>
#include "AvlIntTree.h"

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

int Analysis::len(void) const
{
	return v.size();
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
	const unsigned int inf = std::numeric_limits<unsigned int>::max();
	const unsigned int cache_size = v.size();			// amount of links in stack
	std::set<Address> cache;
	std::map<Address, int> index;						// for each address there is an index of it's last use
	AvlIntTree avl(AvlKey(0, cache_size - 1), 0);		// in the beginning avl tree contains only one node	
	avl.par = NULL;
	//AvlIntTree avl;
	for (int i = 0; i < cache_size; i++)
	{
		std::set<Address>::iterator itr = cache.find(v[i]);
		if (itr == cache.end())				// v[i] is not in the stack
		{
			cache.insert(v[i]);
			index[v[i]] = i;
			int delta = 0;
			avl.add_new_elem(i, delta);
			v[i].dist = inf;
		}
		else								// v[i] is already in the stack
		{
			int prev_index = index[*itr];
			v[i].dist = avl.calc_stack_dist(prev_index, i, cache_size);
			int delt = 0;
			avl.add_new_elem(i, delt);
			unsigned int delta = 0;
			avl.restore(prev_index, delta);		// removes prev_index from the avl tree
			index[*itr] = i;
		}
	}
}
Analysis::TimeAnalisys::TimeAnalisys(void) {}
Analysis::TimeAnalisys::TimeAnalisys(const Analysis &analis)
{
	std::vector <unsigned int> data(analis.len()-1, 0);
	for (int i = 1; i < analis.len(); i++)
	{
		data.push_back(analis.time(i).get_val() - analis.time(i-1).get_val());
	}
	//double lambda = calc_lambda_moments(data);
	//std::cout << lambda << std::endl;
	calc_lambda_distr(data);
}
double Analysis::TimeAnalisys::calc_lambda_moments(const std::vector<unsigned int> &data)
{
	unsigned int sum = 0;
	for (int i = 0; i < data.size(); i++)
		sum += data[i];
	return (double)data.size() / (double)sum;
}
double Analysis::TimeAnalisys::calc_lambda_distr(const std::vector<unsigned int> &data)
{
	double sum = 0.0;
	const double a = 0.0000001;			// must be configured
	const double b = 1;				// must be configured
	const double n = data.size();
	for (int i = 0; i < n; i++)
		sum += data[i];
	std::cout << (a*sum*n)/(2 + sum*n) << std::endl;
	/*std::pair<double, double> res = MyMath::solve_square_equation(sum, n + 2 + a*sum, a*n);
	if ((res.first >= a) && (res.first <= b)) { std::cout << res.first; }
	else if ((res.second >= a) && (res.second <= b)) { std::cout << res.second; }
	else { std::cout << -1; }
	std::cout << std::endl;*/
	return 0;
}
std::pair<double, double> MyMath::solve_square_equation(double a, double b, double c)
{
	double d = b*b - 4*a*c;
	if (d < 0) { throw 1; }
	return std::pair<double, double>((-b - sqrt(d)) / (2*a), (-b + sqrt(d)) / (2*a));
}
/*
	Definition of class AvlKey is over.
*/