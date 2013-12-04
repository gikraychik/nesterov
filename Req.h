#pragma once
#include "Address.h"
#include "MyTime.h"

typedef enum { read, write } req_type;
typedef unsigned char req_size;

class Req
{
public:
	Req(void);
	Req(const MyTime &time, const Address &addr, req_size size, req_type type);
	
	friend std::istream &operator >>(std::istream &input, Req &req);
	/* Data section */
	Address addr;
	MyTime time;
	req_size size;
	req_type type;
};