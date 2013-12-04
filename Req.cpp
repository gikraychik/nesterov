#include "Req.h"

Req::Req(void) : addr(0), time(0), size(0), type(read) {}
Req::Req(const MyTime &time, const Address &addr, req_size size, req_type type) : addr(addr), time(time), size(size), type(type) {}

/*
	This realisation is sign dependent!
	It works only for unsigned integer types
*/
/*std::istream &operator >>(std::istream &input, Req &req)
{
	input >> req.time >> req.addr >> req.size;
	time_l time = req.time.get_val();  // time_l is numeric representation of time declared in Time.h
	/*
		if first bit == 0 then req.type = read
		else req.type = write
	//
	req.type = ((time << 1) >> 1) == time ? read : write;
	// erase first bit of req.time
	req.time = ((time << 1) >> 1);  // unsigned operations
	return input;
}
*/