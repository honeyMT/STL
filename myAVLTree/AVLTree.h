#include<iostream>
#include<Windows.h>
#include<math.h>
#include<assert.h>

using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	K _key;
	V _value;

	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	int _bf;

	AVLTreeNode(const K& key,const V& val)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(val)
		, _bf(0)
	{}

};


template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	~AVLTree()
	{}

public:

	bool Insert(const K& key,const V& val)
	{
		//空树
		if (_root == NULL)
		{
			_root = new Node(key);
		}

		//2.查找位置
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				return false;
		}

		//3.插入节点
		if (parent->_key > key)
		{
			parent->_left = new Node(key);
			parent->_left->_parent = parent;
		}
		else
		{
			parent->_right = new Node(key);
			parent->_right->_parent = parent;
		}
		Node* parentparent = parent->_parent;


	}

protected:

	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* parentparent = parent->_parent;

		parent->_right = subLR;
		if (subLR != NULL)
			subLR->_parent = parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parentparent == NULL)
		{
			_root = subL;
		}

		if (parentparent->_left = parent)
		{
			parentparent->_left = subL;
		}
		else
		{
			parentparent->_right = subL;
		}
		subL->_parent = parentparent;
	}

	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_left = subRL;
		if (subRL != NULL)
			subRL->_parent = parent;

		Node* parentparent = parent->_parent;
		parent->_parent = subR;
		subR->_left = parent;

		if (parentparent == NULL)
		{
			_root = subR;
		}

		if (parentparent->_left == parent)
		{
			parentparent->_left = subR;
		}
		else
		{
			parentparent->_right = subR;
		}
		subR->_parent = parentparent;
	}
	
};