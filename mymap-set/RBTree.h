#include<iostream>
#include<Windows.h>
#include<string>
#include<assert.h>
using namespace std;

enum colour
{
	RED,
	BLACK
};

template<class ValueType>
struct RBTreeNode
{
	ValueType _valueField;
	RBTreeNode<ValueType>* _left;
	RBTreeNode<ValueType>* _right;
	RBTreeNode<ValueType>* _parent;

	colour _col;

	RBTreeNode(const ValueType& v)
		:_valueField(v)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _col(RED)
	{}
};

template<class ValueType>
struct __RBtreeIteartor
{
	typedef RBTreeNode<ValueType> Node;
	typedef __RBtreeIteartor<ValueType> self;

public:

	__RBtreeIteartor(Node* node)
		:_node(node)
	{}

	__RBtreeIteartor(const self& node)
		:_node(node._node)
	{}

	ValueType& operator*()
	{
		return _node->_valueField;
	}

	ValueType* operator->()
	{
		return &operator*();
	}

	self& operator=(const self& node)
	{
		_node = node._node;
	}

	self& operator++()
	{
		//1.如果右不为空，访问右树的最左节点
		//2.如果我的右为空，下一个访问的就是沿着这个路径往上找，第一个右树不是我的节点
		//然后访问该节点.
		if (_node->_right)
		{
			Node* subR = _node->_right;
			while (subR->_left)
			{
				subR = subR->_left;
			}
			_node = subR;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	self& operator--()
	{
		if (_node->_left)
		{
			Node* subL = _node->_left;
			while (subL->_right)
			{
				subL = subL->_right;
			}
			_node = subleft;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	bool operator==(const self& s)
	{
		return _node == s._node;
	}

	bool operator!=(const self& s)
	{
		return _node != s._node;
	}

private:
	Node* _node;

};

template<class K, class V,class KeyOfValue>
class RBTree
{
	typedef  V ValueType;
	typedef RBTreeNode<ValueType> Node;

public:

	typedef __RBtreeIteartor<ValueType> Iterator;

	RBTree()
		:_root(NULL)
	{}
	Iterator Begin()
	{
		Node* cur = _root;
		while (cur && cur->_left != NULL)
		{
			cur = cur->_left;
		}

		return Iterator(cur);
	}

	Iterator End()
	{
		return Iterator(NULL);
	}

	pair<Iterator,bool> Insert(const ValueType& v)
	{
		//_Insert(_root, x, y);
		if (_root == NULL)
		{
			_root = new Node(v);
			_root->_col = BLACK;
			return make_pair(Iterator(_root), true);
		}

		KeyOfValue keyofvalue;

		Node* cur = _root;
		Node* parent = cur;

		while (cur)
		{
			if (keyofvalue(cur->_valueField) > keyofvalue(v))
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (keyofvalue(cur->_valueField) < keyofvalue(v))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (keyofvalue(cur->_valueField) == keyofvalue(v))
			{
				return make_pair(Iterator(cur), false);
			}
		}

		if (keyofvalue(parent->_valueField) > keyofvalue(v))
		{
			parent->_left = new Node(v);
			parent->_left->_parent = parent;
			cur = parent->_left;
		}
		else
		{
			parent->_right = new Node(v);
			parent->_right->_parent = parent;
			cur = parent->_right;
		}

		Node* newNode = cur;
		//目前父亲节点，插入节点，叔叔节点已经就绪.
		while (parent && parent->_col == RED)
		{
			Node* parentparent = parent->_parent;
			Node* uncle = NULL;

			if (parentparent->_left == parent)
				uncle = parentparent->_right;

			else
				uncle = parentparent->_left;

			if (uncle && uncle->_col == RED)
			{
				parentparent->_col = RED;
				parent->_col = BLACK;
				uncle->_col = BLACK;

				cur = parentparent;
				parent = cur->_parent;

			}
			else if (uncle == NULL || uncle->_col == BLACK)
			{
				if (parentparent->_left == parent)
				{
					if (parent->_left == cur)
					{
						RotateR(parentparent);
						parent->_col = BLACK;
					}
					else
					{
						RotateLR(parentparent);
						cur->_col = BLACK;
					}
				}
				else
				{
					if (parent->_right == cur)
					{
						RotateL(parentparent);
						parent->_col = BLACK;
					}
					else
					{
						RotateRL(parentparent);
						cur->_col = BLACK;
					}
				}
				parentparent->_col = RED;
				if (parentparent == _root)
				{
					_root = parent;
				}

			}
			else
			{
				assert(false);
			}
		}
		_root->_col = BLACK;
		return make_pair(Iterator(newNode), true);
		//担心经过旋转之后，找不到新增节点了,所以提前记录好.
	}


	Iterator Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (keyofvalue(cur->_valueField) > keyofvalue(key))
			{
				cur = cur->_right;
			}
			else if (keyofvalue(cur->_valueField) < keyofvalue(key))
			{
				cur = cur->_left;
			}
			else if (keyofvalue(cur->_valueField) == keyofvalue(key))
			{
				return Iterator(cur);
			}
		}
		return Iterator(NULL);
	}

protected:

	void RotateLR(Node*& parent)
	{

		RotateL(parent->_left);

		RotateR(parent);
	}

	void RotateRL(Node*& parent)
	{
		RotateR(parent->_right);
		RotateL(parent);
	}

	void RotateR(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		Node* ppNode = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		if (ppNode == NULL)
		{
			_root = subL;
			_root->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
			subL->_parent = ppNode;
		}
	}

	void RotateL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* ppNode = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			_root->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}
	}
private:
	Node* _root;
};
