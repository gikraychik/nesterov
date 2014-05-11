#pragma once
#include <string>
#include <iostream>
#include "Basic_Type.h"

typedef big_int mem_rep;

class Address : public Basic_Type
{
public:
	Address(const mem_rep number = 0);
	std::string str_addr(void) const;  // returns m_str_addr
	int num_addr(void) const;  // returns m_num_addr
	void set_str_addr(const std::string &s);  // sets new value for m_str_addr
	void set_num_addr(mem_rep value);  // sets new value for m_num_addr
	void set_dist(unsigned int dist);
	unsigned int get_dist(void) const;

	friend std::istream &operator >>(std::istream &input, Address &addr);
	unsigned int dist;  // stack distance
private:
	void transform_to_string(void);  // transforms m_num_addr to string and sets new value for m_str_addr
	void transform_to_num(void);  //transforms m_str_addr to number and sets new value for m_num_addr
	//std::string m_str_addr;  // represents address as a string
	//mem_rep m_num_addr;  //represents address as a number
};