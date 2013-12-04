#pragma once
#include <iostream>

typedef unsigned long long big_int;

class Basic_Type
{
public:
	Basic_Type(const big_int number = 0);
	~Basic_Type(void);
	inline virtual bool operator ==(const Basic_Type obj) const;
	inline virtual bool operator <(const Basic_Type obj) const;
	inline virtual bool operator <=(const Basic_Type obj) const;
	inline virtual bool operator >(const Basic_Type obj) const;
	inline virtual bool operator >=(const Basic_Type obj) const;
	inline virtual bool operator !=(const Basic_Type obj) const;

	inline virtual big_int get_val(void) const;
	inline virtual void set_val(big_int new_value);
	
	friend std::ostream &operator <<(std::ostream &stream, const Basic_Type obj);
	inline bool was_defined(void);
private:
	big_int val;  // contains numeric information about object
};