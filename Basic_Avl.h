#pragma once
/*
	Basic class for all AVL trees. Class is abstract.
	Class contains no data definitions.
	Key is a unique value for each tree.
	Value is not unique.
*/
template <class Key, class Value> class Basic_Avl
{
public:
	/*
	typedef Basic_Avl Node;			// each AVL tree is not logically the same as Node
									// but in this very realisation they are equal
	*/
	Basic_Avl(void);
	~Basic_Avl(void);
	virtual int add(const Key &key, Value value) = 0;
	virtual void remove(const Basic_Avl *avl_tree) = 0;
	virtual void remove(const Key &key) = 0;
	virtual Basic_Avl *find(const Key &key) = 0;

protected:
	virtual void make_balance(void) = 0;
};

