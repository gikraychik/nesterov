#pragma once

template <typename KEY,typename VALUE> class AvlTree
{

public:
	KEY key;
	VALUE value;
	int balance;
	AvlTree<KEY, VALUE>* left;
	AvlTree<KEY, VALUE>* right;
	bool empty;						//��������� ���� � �������� ��� ���

	AvlTree()
	{
		empty=true;
		left = NULL;
		right = NULL;
		balance = 0;
	}

	AvlTree(KEY Key,VALUE Value)
	{ 
		empty=false;
		key = Key;
		value = Value;
		left = NULL;
		right = NULL;
		balance = 0;
	}

	int add(KEY Key, VALUE Value)	//���������� ����, ���������� ��������� ������(1) ��� ��� (0)
	{								//��� ���������� � ������ ����� ������ ���� ���������� �� ��������� ����������
		if (empty)					//� ����� ��������
		{							//����� ������� ������ add(...) ������� TurnAround();
			key = Key;				//������ ��������������� ���� ������� �������� ���� � ������ ����������� �� ����� NULL
			value = Value;			//����� � ����� ������� ���������� ����� ��������
			empty=false;
			return 0;
		}
		if (Key == key)
			throw "��� ����";
		int a = balance;
		if (Key > key)
		{
			if (right != NULL)
			{
				balance += right->add(Key, Value);
				TurnAround();
			}
			else
			{
				right = new AvlTree<KEY, VALUE>(Key, Value);
				balance++;
			}
		}
		else
		{
			if (left != NULL)
			{
				balance -= left->add(Key, Value);
				TurnAround();
			}
			else
			{
				left = new AvlTree<KEY, VALUE>(Key, Value);
				balance--;
			}
		}
		if (balance != a)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	void TurnAround()	//������������ ������, ���� ������ �� ����������� ������(�����������) ���� ���, 
	{					//����� ���������� �������� ������ � ����� �� ���������� ������ , ��� �� 1 
		if (balance == 2)
		{
			if (right->balance >= 0)
			{
				KEY tKey = key;
				VALUE tValue = value;
				key = right->key;
				value = right->value;
				right->key = tKey;
				right->value = tValue;
				AvlTree<KEY, VALUE>*tNode=right->right;
				right->right = right->left;
				right->left = left;
				left = right;
				right = tNode;
				balance = left->balance - 1;
				left->balance = 1 - left->balance;
			}
			else
			{
				KEY tKey = key;
				VALUE tValue = value;
				key = right->left->key;
				value = right->left->value;
				right->left->key = tKey;
				right->left->value = tValue;
				AvlTree<KEY, VALUE>* tNode = right->left->right;
				right->left->right = right->left->left;
				right->left->left = left;
				left = right->left;
				right->left = tNode;
				balance = 0;
				right->balance = (left->balance == -1) ? (1) : (0);
				left->balance = (left->balance == 1) ? (-1) : (0);
			}
		}
		else
		{
			if (balance == -2)
			{
				if (left->balance <= 0)
				{
					KEY tKey = key;
					VALUE tValue = value;
					key = left->key;
					value = left->value;
					left->key = tKey;
					left->value = tValue;
					AvlTree<KEY, VALUE>* tNode = left->left;
					left->left = left->right;
					left->right = right;
					right = left;
					left = tNode;
					balance = 1 + right->balance;
					right->balance = -1 - right->balance;
				}
				else
				{
					KEY tKey = key;
					VALUE tValue = value;
					key = left->right->key;
					value = left->right->value;
					left->right->key = tKey;
					left->right->value = tValue;
					AvlTree<KEY, VALUE>* tNode = left->right->left;
					left->right->left = left->right->right;
					left->right->right = right;
					right = left->right;
					left->right = tNode;
					balance = 0;
					left->balance = (right->balance == 1) ? (-1) : (0);
					right->balance = (right->balance == -1) ? (1) : (0);
				}
			}
		}
	}

	typename AvlTree<KEY, VALUE>* getNode(KEY Key)		//����� ���� �� �����
	{
		AvlTree<KEY, VALUE>* node=this;
		while (true)
		{
			if (node == NULL)
				throw "�� �������";
			if (node->key == Key)
				return node;
			if (node->key < Key)
			{
				node = node->right;
			}
			else
			{
				node = node->left;
			}
	 
		}
	}

	int remove(KEY Key,AvlTree<KEY, VALUE>*parent=NULL) //�������� ����, ����������� �� ������, �� �����
	{														//��� ����������� ���� ����� ����� ������ � ����������� �� ����������� � ����������� ��� TurnAround()
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
						AvlTree<KEY, VALUE>* tNode = right;
						while (tNode->left != NULL)
						{
							tNode = tNode->left;
						}
						KEY tKey = key;
						VALUE tValue = value;
						key = tNode->key;
						value = tNode->value;
						tNode->key = tKey;
						tNode->value = tValue;
						balance -= right->remove(Key,this);
					}
				}
				else
				{
					if (left != NULL)
					{
						AvlTree<KEY, VALUE>* tNode = left;
						while (tNode->right != NULL)
						{
							tNode = tNode->right;
						}
						KEY tKey = key;
						VALUE tValue = value;
						key = tNode->key;
						value = tNode->value;
						tNode->key = tKey;
						tNode->value = tValue;
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
					TurnAround();
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
					TurnAround();
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
	~AvlTree(void)
	{
		AvlTree <KEY, VALUE> *node = this;
	}
private:
	void free_subtree(AvlTree <KEY, VALUE> *node)
	{
		if (node->right == NULL && node->left == NULL)
		{
			delete node;
		}
		else
		{
			free_subtree(node->left);
			free_subtree(node->right);
		}
	}
};