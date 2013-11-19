#include "Basic_Type.h"

Basic_Type::Basic_Type(const big_int number)
{
	val = number;
}
Basic_Type::~Basic_Type(void)
{
}
bool Basic_Type::operator ==(const Basic_Type obj) const
{
	return val == obj.val;
}
bool Basic_Type::operator <(const Basic_Type obj) const
{
	return val < obj.val;
}
bool Basic_Type::operator !=(const Basic_Type obj) const
{
	return ! operator ==(obj);
}
bool Basic_Type::operator >(const Basic_Type obj) const
{
	return ! operator <=(obj);
}
bool Basic_Type::operator >=(const Basic_Type obj) const
{
	return ! operator <(obj);
}
bool Basic_Type::operator <=(const Basic_Type obj) const
{
	return (operator <(obj) || operator ==(obj));
}
bool Basic_Type::was_defined(void)
{
	return val != 0;
}
big_int Basic_Type::get_val(void) const
{
	return val;
}
std::ostream &operator <<(std::ostream &stream, const Basic_Type obj)
{
	std::cout << obj.val;
	return std::cout;
}