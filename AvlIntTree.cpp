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
			}
		}
	}
}

/*
	Calculates distance for address with number index.
	Input:
		index of the address
	Output:
		Returns amount of 1 in [0, index) = [0, index - 1]
*/
int AvlIntTree::calc_stack_dist(unsigned int index) const
{
	return index - calc_sum(index - 1);
}
/*
	Input:
		index of address
	Output:
		Returns amount of 0 in [0, index]
*/
int AvlIntTree::calc_sum(unsigned int index) const
{
	const AvlIntTree *node = this;
	const unsigned int delta = key.max - key.min + 1;	// amount of zeros in current node
	if (index > key.max)
	{
		return value + delta + ((right != NULL) ? node->right->calc_sum(index) : 0);
	}
	else if (index < key.min)
	{
		return (left != NULL) ? node->left->calc_sum(index) : 0;
	}
	else
	{
		return (index - key.min + 1) + ((left != NULL) ? node->left->calc_sum(index) : 0);
	}
}
int AvlIntTree::remove(AvlKey Key, AvlIntTree *parent)
{
	int a = balance;										// ��� ����� �� ������� ���� ��������� ��� , ���� ��� ��� ������� �� ����� NULL
	if (key == Key)										// � ������
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
					value = (left != NULL) ? left->value + (left->key.max - left->key.min + 1) : 0;
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
					value = left->value + (left->key.max - left->key.min + 1);
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
				throw "�� �������";
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
				throw "�� �������";
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
int AvlIntTree::add_new_elem(unsigned int ind)
{
	// if (empty) { ... }
	// proccessing mistakes
	int old_bal = balance;
	if ((key.min == key.max) && (key.min == ind))	// key.min == key.max == ind
	{
		remove(this->key);
		return 0;
	}
	if (ind == key.min)
	{
		key.min++;
		return 0;
	}
	if (ind == key.max)
	{
		key.max--;
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
			balance -= left->add_new_elem(ind);
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
			balance += right->add_new_elem(ind);
			make_balance();
		}
		else
		{
			throw "AvlIntTree::add_new_elem: element is already in the stack (right case)";
		}
	}
}

/*
	Adds 1 to AVL tree. (1->0)
	Input:
		ind - index that will be added
	Output:
		none
*/
int AvlIntTree::restore(unsigned int ind)
{
	int old_balance = balance;
	if (key.min - 1 == ind)
	{
		key.min--;
		return 0;
	}
	else if (key.max + 1 == ind)
	{
		key.max++;
		return 0;
	}
	else
	{
		if (ind < key.min)		// go left
		{
			if (left)
			{
				balance -= left->restore(ind);
				make_balance();
			}
			else
			{
				left = new AvlIntTree(AvlKey(ind, ind), 0);
				balance--;
			}
		}
		if (ind > key.max)
		{
			if (right)
			{
				balance += right->restore(ind);
				make_balance();
			}
			else
			{
				right = new AvlIntTree(AvlKey(ind, ind), 0);
				balance++;
			}
		}
	}
	return (old_balance == balance) ? 0 : 1;
}