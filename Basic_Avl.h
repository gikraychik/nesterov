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
	typedef Basic_Avl Node;			// each AVL tree is not logically the same as Node
									// but in this very realisation they are equal
	Basic_Avl(void);
	~Basic_Avl(void);
	virtual void add(const Key &key, const Value value) = 0;
	virtual void remove(const Node *node) = 0;
	virtual void remove(const Key &key) = 0;
	virtual Node *find(const Key &key) = 0;

protected:
	virtual void make_balance(void) = 0;
};

