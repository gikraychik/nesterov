#pragma once
#include "basic_type.h"

typedef unsigned long long time_l;

class MyTime : public Basic_Type
{
public:
	friend std::istream &operator >>(std::istream &input, MyTime &time);
	MyTime(const time_l time = 0);
	~MyTime(void);
	//inline unsigned int operator -(const MyTime &time) const;
};

