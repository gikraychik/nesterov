#include "AvlIntTree.h"
#define NULL 0

/*
	Defenition of struct AvlKey
	AvlKey is a unique key in AVL tree
*/

AvlKey::AvlKey(unsigned int min, unsigned int max) : min(min), max(max) {}
bool AvlKey::operator<(const AvlKey &key) const
{
	return this->max < key.min;
}
bool AvlKey::operator==(const AvlKey &key) const
{
	return (this->min == key.min) && (this->max == key.max);
}
bool AvlKey::operator<=(const AvlKey &key) const
{
	return operator <(key) || operator==(key);
}
bool AvlKey::operator>(const AvlKey &key) const
{
	return ! operator <=(key);
}
bool AvlKey::operator>=(const AvlKey &key) const
{
	return ! operator <(key);
}
bool AvlKey::operator!=(const AvlKey &key) const
{
	return ! operator ==(key);
}
bool AvlKey::intersects(const AvlKey &key) const
{
	return ((max >= key.min) && (min <= key.max));
}

/*
	Definition of struct AvlKey is finished.
	Next follows definition of class AvlIntTree
*/

AvlIntTree::AvlIntTree(void) 
	: empty(true), left(NULL), right(NULL), par(NULL), balance(0) {}

AvlIntTree::AvlIntTree(const AvlKey &key, uint value) 
	: key(key), value(value), empty(false), left(NULL), right(NULL), par(NULL), balance(0) {}



AvlIntTree::~AvlIntTree(void)
{
}

void AvlIntTree::make_balance(void)
{
	if (balance == 2)
	{
		if (right->balance >= 0)
		{
			AvlKey tKey = key;
			uint tValue = value;
			key = right->key;
			value = right->value;
			right->key = tKey;
			right->value = tValue;
			AvlIntTree *tNode=right->right;
			right->right = right->left;
			right->left = left;
			left = right;
			right = tNode;
			balance = left->balance - 1;
			left->balance = 1 - left->balance;
			/* correct sums (values) */
			//value += left->value + (left->key.max - left->key.min + 1);
			if (left) { left->value = (left->right) ? left->value - value - zeros() : 0; }
		}
		else
		{
			AvlKey tKey = key;
			uint tValue = value;
			key = right->left->key;
			value = right->left->value;
			right->left->key = tKey;
			right->left->value = tValue;
			AvlIntTree *tNode = right->left->right;
			right->left->right = right->left->left;
			right->left->left = left;
			left = right->left;
			right->left = tNode;
			balance = 0;
			right->balance = (left->balance == -1) ? (1) : (0);
			left->balance = (left->balance == 1) ? (-1) : (0);
			/* correct sums (value) */
			//right->value = right->left->value + (right->left->key.max - right->left->key.min + 1);
			//value = left->value + (left->key.max - left->key.min + 1);
			int tmp;
			tmp = left->value - right->value - right->zeros() - value - zeros();		// a
			value = right->value + right->zeros() + value;								// c
			left->value = tmp;
		}
	}
	else
	{
		if (balance == -2)
		{
			if (left->balance <= 0)
			{
				AvlKey tKey = key;
				uint tValue = value;
				key = left->key;
				value = left->value;
				left->key = tKey;
				left->value = tValue;
				AvlIntTree *tNode = left->left;
				left->left = left->right;
				left->right = right;
				right = left;
				left = tNode;
				balance = 1 + right->balance;
				right->balance = -1 - right->balance;
				/* correct sums (values) */
				//right->value = right->left->value + (right->left->key.max - right->left->key.min + 1);
				if (right) { right->value = (right->right) ? value - right->value - right->zeros() : 0; }
			}
			else
			{
				AvlKey tKey = key;
				uint tValue = value;
				key = left->right->key;
				value = left->right->value;
				left->right->key = tKey;
				left->right->value = tValue;
				AvlIntTree *tNode = left->right->left;
				left->right->left = left->right->right;
				left->right->right = right;
				right = left->right;
				left->right = tNode;
				balance = 0;
				left->balance = (right->balance == 1) ? (-1) : (0);
				right->balance = (right->balance == -1) ? (1) : (0);
				/* correct sums (values) */
				//right->value = right->left->value + (right->left->key.max - right->left->key.min + 1);
				//value = left->value + (left->key.max - left->key.min + 1);
				int tmp = left->value - value - zeros();
				value = right->zeros() + right->value + value;
				left->value = tmp;
			}
		}
	}
	//value = (right) ? right->value + right->zeros() : 0;
}

/*
	Calculates distance for address with number index.
	Input:
		index of the address
	Output:
		Returns amount of 1 in [prev_index, index)
*/
int AvlIntTree::calc_stack_dist(unsigned int prev_index, unsigned int index, unsigned int cache_size) const
{
	int zeros = calc_sum(prev_index) - (cache_size - index);		// amount of zeros in [prev_index, index)
	return (index - prev_index - 1) - zeros;
}
/*
	Input:
		prev_index - index of the most recently used address
		index - new address
	Output:
		Returns amount of 0 in [prev_index, cache_size)
*/
int AvlIntTree::calc_sum(unsigned int prev_index) const
{
	const AvlIntTree *node = this;
	const unsigned int delta = key.max - key.min + 1;	// amount of zeros in current node
	if (prev_index < key.min)
	{
		if (left) { return value + delta + left->calc_sum(prev_index); }
		else { return value + delta; }
	}
	else if (prev_index > key.max)
	{
		if (right) { return right->calc_sum(prev_index); }
		else { return 0; }
	}
	else
	{
		return (key.max - prev_index + 1) + value;
	}
}
int AvlIntTree::remove(AvlKey Key, AvlIntTree *parent)
{
	int a = balance;
	if (key == Key)
	{
		if (right == NULL && left == NULL)
		{
			if(parent->left->key==this->key)
			{
				parent->left=NULL;
			}
			else
			{
				parent->right=NULL;
			}
			return 1;
		}
		else
		{
			if (balance >= 0)
			{
				if (right != NULL)
				{
					AvlIntTree* tNode = right;
					while (tNode->left != NULL)
					{
						tNode = tNode->left;
					}
					AvlKey tKey = key;
					uint tValue = value;
					key = tNode->key;
					value = tNode->value;
					tNode->key = tKey;
					tNode->value = tValue;
					/* correct sums (values) */
					value = (right != NULL) ? right->value + (right->key.max - right->key.min + 1) : 0;
					tNode->value = 0;
					/* recursive call */
					balance -= right->remove(Key,this);
				}
			}
			else
			{
				if (left != NULL)
				{
					AvlIntTree* tNode = left;
					while (tNode->right != NULL)
					{
						tNode = tNode->right;
					}
					AvlKey tKey = key;
					uint tValue = value;
					key = tNode->key;
					value = tNode->value;
					tNode->key = tKey;
					tNode->value = tValue;
					/* correct sums(values) */
					value = right->value + (right->key.max - right->key.min + 1);
					tNode->value = 0;
					/* recursive call */
					balance += left->remove(Key,this);
				}
			}
		}
	}
	else
	{
		if (Key > key)
		{
			if (right!=NULL)
			{
				balance -= right->remove(Key,this);
				make_balance();
			}
			else
			{
				throw "Не найдено";
			}
		}
		else
		{
			if (left!=NULL)
			{
				balance += left->remove(Key,this);
				make_balance();
			}
			else
			{
				throw "Не найдено";
			}
		}
	}
	if (balance != a)
	{
		return (balance == 0) ? (1) : (0);
	}
	else
	{
		return 0;
	}
}

/*
	Adds interval (the whole node) to the AVL tree.
	New interval does not intersect with any other intervals,
		otherwise an exception is thrown.
	Input:
		new_key - new interval
	Output:
		1, if balance was changed
		0, if balance was not changed
	Value will always be equal to 0.
*/
int AvlIntTree::add_interval(AvlKey new_key)
{
	int old_balance = balance;
	if (new_key.max < key.min)
	{
		if (!left)
		{
			balance -= left->add_interval(new_key);
			make_balance();
		}
		else
		{
			left = new AvlIntTree(new_key, 0);
			balance--;
		}
	}
	else if (new_key.min > key.max)
	{
		if (!right)
		{
			balance += right->add_interval(new_key);
			make_balance();
		}
		else
		{
			right = new AvlIntTree(new_key, 0);
			balance++;
		}
	}
	else  // intersection! critical error
	{
		throw "AvlIntTree::add_interval(AvlKey): interval intersects another one";
	}
	if (old_balance == balance) { return 0; }	// balance didn't change
	else { return 1; }							// balance changed
}

/*
	Adds element that was not in the stack before.
	ind - index of current address
*/
int AvlIntTree::add_new_elem(unsigned int ind, int &delta)
{
	if (empty)
	{
		key = AvlKey(ind, ind);
		value = 0;
		empty = false;
		return 0;
	}
	int old_bal = balance;
	if ((key.min == key.max) && (key.min == ind))	// key.min == key.max == ind
	{
		remove(this->key);
		delta = 1;
		return 0;
	}
	if (ind == key.min)
	{
		key.min++;
		delta = 1;
		return 0;
	}
	if (ind == key.max)
	{
		key.max--;
		delta = 1;
		return 0;
	}
	if ((ind > key.min) && (ind < key.max))		// key.min < ind < key.max
	{
		throw "AvlIntTree::add_new_elem(unsigned int) : insertion into the middle of the interval";
		//key.max = ind;
		//add_interval(AvlKey(ind+1, key.max));
		//return 0;
	}
	if (ind < key.min)
	{
		if (left)
		{
			balance -= left->add_new_elem(ind, delta);
			make_balance();
		}
		else
		{
			throw "AvlIntTree::add_new_elem: element is already in the stack (left case)";
		}
	}
	else if (ind > key.max)
	{
		if (right)
		{
			balance += right->add_new_elem(ind, delta);
			value -= delta;
			make_balance();
		}
		else
		{
			throw "AvlIntTree::add_new_elem: element is already in the stack (right case)";
		}
	}
	//return (old_bal == balance) ? 0 : 1;
	if ((balance * balance == 1) && (old_bal == 0)) { return 1; }
	else { return 0; }
}

/*
	Adds 1 to AVL tree. (1->0)
	Input:
		ind - index that will be added
	Output:
		none
*/
int AvlIntTree::restore(unsigned int ind, unsigned int &delta)
{
	int old_balance = balance;
	if (key.min - 1 == ind)
	{
		delta = 1;
		key.min--;
		return 0;
	}
	else if (key.max + 1 == ind)
	{
		delta = 1;
		key.max++;
		return 0;
	}
	else
	{
		if (ind < key.min)		// go left
		{
			if (left)
			{
				balance -= left->restore(ind, delta);
				make_balance();
			}
			else
			{
				left = new AvlIntTree(AvlKey(ind, ind), 0);
				delta = 1;
				//value = left->key.max - left->key.min + 1;
				balance--;
			}
		}
		if (ind > key.max)
		{
			if (right)
			{
				balance += right->restore(ind, delta);
				value += delta;
				make_balance();
			}
			else
			{
				right = new AvlIntTree(AvlKey(ind, ind), 0);
				delta = 1;
				value = right->zeros();			// value = 1
				balance++;
			}
		}
	}
	//return ((old_balance == balance)) ? 0 : 1;
	if ((balance * balance == 1) && (old_balance == 0)) { return 1; }
	else { return 0; }
}

unsigned int AvlIntTree::zeros(void) const
{
	return key.max - key.min + 1;
}