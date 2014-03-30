#include "MyTime.h"


MyTime::MyTime(const time_l time)
{
	set_val(time);
}


MyTime::~MyTime(void)
{
}
/*unsigned int MyTime::operator -(const MyTime &time) const
{
	return get_val() - time.get_val();
}*/
/*std::istream &operator >>(std::istream &input, MyTime &time)
{
	return input >> time.get_val();
}*/