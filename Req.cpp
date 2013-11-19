#include "Req.h"

Req::Req(void) : addr(0), time(0), size(0), type(read) {}
Req::Req(const Address &addr, const MyTime &time, req_size size, req_type type) : addr(addr), time(time), size(size), type(type) {}
