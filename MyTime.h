#pragma once
#include "basic_type.h"

typedef big_int time_l;

class MyTime : public Basic_Type
{
public:
	MyTime(const time_l time = 0);
	~MyTime(void);
};

