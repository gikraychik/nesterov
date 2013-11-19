#pragma once
#include "Address.h"
#include "MyTime.h"

typedef enum { read, write } req_type;
typedef unsigned int req_size;

class Req
{
public:
	Req(void);
	Req(const Address &addr, const MyTime &time, req_size size, req_type type);
	
	/* Data section */
	Address addr;
	MyTime time;
	req_size size;
	req_type type;
};