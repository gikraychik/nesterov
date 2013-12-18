#pragma once
#define NULL 0

// Struct is a Key in AVL tree
struct AvlKey
{
	AvlKey(unsigned int min = 0, unsigned int max = 0);
	inline bool operator <(const AvlKey &key) const;
	inline bool operator ==(const AvlKey &key) const;
	inline bool operator <=(const AvlKey &key) const;
	inline bool operator >(const AvlKey &key) const;
	inline bool operator >=(const AvlKey &key) const;
	inline bool operator !=(const AvlKey &key) const;
	inline bool intersects(const AvlKey &key) const;
	unsigned int min, max;		// left and rigth boundaries
};
typedef unsigned int uint;		// Value in AVL tree
//typedef Node AvlIntTree 		// it is already written in Basic_Avl

class AvlIntTree
{
public:
	AvlIntTree(void);
	AvlIntTree(const AvlKey &key, uint value);
	int add_new_elem(unsigned int ind, int &delta);
	//int add_existing_elem(unsigned int ind);
	int add_interval(AvlKey interval);
	int calc_stack_dist(unsigned int prev_index, unsigned int index, unsigned int cache_size) const;
	int remove(void);
	int remove_del(AvlKey Key, AvlIntTree *parent);
	int restore(unsigned int ind, unsigned int &delta);
	int merge(AvlIntTree *root);
	inline unsigned int zeros(void) const;	// return amount of zeros in current node
	~AvlIntTree(void);

	// Data section
	AvlKey key;			// Key of the current node
	uint value;			// Value of the current node
	int balance;
	AvlIntTree *left;	// left child
	AvlIntTree *right;	// right child
	AvlIntTree *par;	// parent
	bool empty;			// idicates whether key and value are set

private:
	static void swap(AvlIntTree *node1, AvlIntTree *node2);
	int remove_by_par(AvlKey key, int &delta);
	void make_balance(void);
	int calc_sum(unsigned int prev_index) const;
};

