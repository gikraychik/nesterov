#pragma once
#include <fstream>
#include <exception>
#include "Req.h"
#include <vector>

class Analysis
{
public:
	Analysis(void);
	Analysis(const char *filename);
	~Analysis(void);

	void calc_stack_dist(void);

	/* Access to array elements */
	inline std::vector<Req> requests(void) const;
	Req req(int i) const;
	inline Address addr(int i) const;
	inline MyTime time(int i) const;
	inline req_size size(int i) const;
	inline req_type type(int i) const;
protected:
	class AddressAnalisys
	{
	public:
		AddressAnalisys(void);
		AddressAnalisys(const Analysis &analis);
		void calc_stack_dist(void);
		inline std::vector<Address> addresses(void) const;
	protected:
		std::vector<Address> v;
	private:

	};
private:
	std::ifstream input;
	std::vector<Req> v;
};

