#include "AvlInterval.h"

/*
	Definition of class AvlInterval
*/
AvlInterval::AvlInterval(KEY key, uint number) : left(NULL), right(NULL)
{
	this->key = key;
	this->value = number;
	empty = false;
	balance = 0;
}

AvlInterval::~AvlInterval(void)
{
}

void AvlInterval::add(uint number)
{
	AvlInterval *node = this;
	AvlInterval *prev_node = NULL;
	while (node)
	{
		prev_node = node;
		if (node->key.min == number + 1)
		{
			node->key.min--;
			break;
		}
		else if (node->key.max == number - 1)
		{
			node->key.max++;
			break;
		}
		else if (node->key.min > number)
		{
			node = node->left;
		}
		else if (node->key.max < number)
		{
			node = node->right;
		}
		else { throw "Error: 2 same indicies found"; }
	}
	if (node == NULL)				// create new node
	{
		node = new AvlInterval(KEY(number, number), 0);
		if (prev_node->key.min > number) { prev_node->left = node; }
		else { prev_node->right = node; }
	}
	TurnAround();
}

void AvlInterval::update_sum(void)
{
	rec_update_sum(this);
}
// next follows private functions

/*
	This void joins 2 nodes into 1 node
	Nodes will be merged if one of two conditions are perfomed:
		1. cur: [k1, k2] --------- par: [k2+1, k3]
		2. cur: [k1, k2] --------- par: [k3, k1+1]
	If conditions are not perfomed, an exception is thrown
*/
void AvlInterval::merge(AvlInterval *cur, AvlInterval *par)
{
	if (cur == par->left)
	{
		par->key.min = cur->key.min;
	}
	else if (cur == par->right)
	{
		par->key.max = cur->key.max;
	}
	else { throw "Error in AvlInterval::merge(AvlInterval *cur, AvlInterval *par): par is not a parent of cur"; }
	remove(cur->key, par);
}

/*
	Updates sum of subtree "node"
	Written to embody recursion
*/
uint AvlInterval::rec_update_sum(AvlInterval *node)
{
	if (!node) return 0;
	node->value = (node->key.max - node->key.min + 1) + rec_update_sum(node->right);
	return node->value;
}

/*
	Definition is over.
*/