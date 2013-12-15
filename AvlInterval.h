#pragma once
#include "avltree.h";
#include "Analysis.h";

typedef Analysis::AddressAnalisys::AvlKey KEY;
typedef unsigned int uint;

template <class Key, Value> class AvlInterval : public Basic_Avl
{
public:
	AvlInterval *left;
	AvlInterval *right;

	void update_sum(void);
	void add(uint number);
	void dist(uint index);			// calculates dist(index)

	AvlInterval(KEY key = KEY(-1, -1), uint number = 0);
	~AvlInterval(void);
private:
	void merge(AvlInterval *cur, AvlInterval *par);
	uint rec_update_sum(AvlInterval *node);
};

