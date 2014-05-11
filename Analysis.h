#pragma once
#include <exception>
#include "Req.h"
#include <vector>
#include "IO_Manager.h"
#include <set>
#include "AvlTree.h"

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
	inline int len(void) const;

	Req operator [] (int i) const;  // acceses a request at index i

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
	class TimeAnalisys
	{
	public:
		TimeAnalisys(void);
		TimeAnalisys(const Analysis &analis);
	private:
		static double calc_lambda_moments(const std::vector<unsigned int> &data);
		static double calc_lambda_distr(const std::vector<unsigned int> &data, double a, double b);
	};
private:
	std::fstream input;
	std::vector<Req> v;
};

class MyMath
{
public:
	MyMath(void);
	static std::pair<double, double> solve_square_equation(double a, double b, double c);
};

