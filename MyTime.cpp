#include "MyTime.h"


MyTime::MyTime(const time_l time)
{
	set_val(time);
}


MyTime::~MyTime(void)
{
}

/*std::istream &operator >>(std::istream &input, MyTime &time)
{
	return input >> time.get_val();
}*/