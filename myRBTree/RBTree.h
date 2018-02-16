#include<iostream>
#include<Windows.h>
#include<assert.h>
using namespace std;

//
enum colour
{
	RED,
	BLACK
};

template<class K, class V>
struct RBTreeNode
{
	K _key;
	K _val;

	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	colour _col;

	RBTreeNode(const K& key, const V& val)
		:_key(key)
		, _val(val)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _col(RED)
	{}
};

template<class K,class V>
struct __RBtreeIteartor
{
	typedef RBTreeNode<K, V> Node;
	typedef __RBtreeIteartor<K, V> self;

public:

	__RBtreeIteartor(const Node* node)
		:_node(node)
	{}

	__RBtreeIteartor(const __RBtreeIteartor& node)
		:_node(node._node)
	{}

	V operator*()
	{
		return _node->_val;
	}

	V operator->()
	{
		return &operator*();
	}

	self& operator=(const __RBtreeIteartor& node)
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

	self& operator==(const self& s)
	{
		return _node == s._node;
	}

	self& operator!=(const self& s)
	{
		return _node != s._node;
	}

private:
	Node* _node;

};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
	
public:

	typedef __RBtreeIteartor<K, V>* Iterator;

	RBTree()
		:_root(NULL)
	{}

	Iterator Begin()
	{
		Node* cur = _root;

		while (cur->_left)
		{
			cur = cur->_left;
		}

		return Iterator(cur);
	}

	Iterator End()
	{
		return Iterator(NULL);
	}
	bool Insert(const K& key, const V& val)
	{
		//_Insert(_root, x, y);
		if (_root == NULL)
		{
			_root = new Node(key, val);
			_root->_col = BLACK;
		}

		Node* cur = _root;
		Node* parent = cur;

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
			else if (cur->_key == key)
			{
				return true;
			}
		}

		if (parent->_key > key)
		{
			parent->_left = new Node(key, val);
			parent->_left->_parent = parent;
			cur = parent->_left;
		}
		else
		{
			parent->_right = new Node(key, val);
			parent->_right->_parent = parent;
			cur = parent->_right;
		}
	
		//目前父亲节点，插入节点，叔叔节点已经就绪.
		while(parent && parent->_col == RED)
		{
			Node* parentparent = parent->_parent;
			Node* uncle = NULL;

			if (parentparent->_left == parent)
				uncle = parentparent->_right;

			else
				uncle = parentparent->_left;

			if(uncle && uncle->_col == RED)
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
			if (_root->_col == RED)
			{
				_root->_col = BLACK;
			}
		}
		return false;
	}

	bool ISRBtree()
	{
		if (_root->_col == RED)
		{
			return false;
		}
		size_t n = 0;
		size_t m = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				n++;
			}
			cur = cur->_left;
		}
		return _ISRBtree(_root, m, n);
	}

	void print()
	{
		_print(_root);
	}

protected:

	void _print(Node* root)
	{
		if (root == NULL)
			return;

		_print(root->_left);
		cout << root->_val << " ";
		_print(root->_right);
	}

	bool _ISRBtree(Node* root, size_t m, size_t n)
	{
		if (root == NULL)
		{
			if (m == n)
				return true;
			else
				return false;
		}


		if (root->_col == BLACK)
		{
			m++;
		}
		if (root->_col == RED && root->_parent && root->_parent->_col == RED)
		{
			return false;
		}

		return _ISRBtree(root->_left, m, n) && _ISRBtree(root->_right, m, n);

	}

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
		Node* subLR = NULL;
		if (subL)
			subLR = subL->_right;
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
		Node* subRL = NULL;
		if (subR)
			subRL = subR->_left;

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



void Test()
{
	RBTree<int, int> T;
	//8 9 2 4 1 6 3 5
	T.Insert(8, 8);
	T.Insert(9, 9);
	T.Insert(2, 2);
	T.Insert(4, 4);
	T.Insert(1, 1);
	T.Insert(6, 6);
	T.Insert(3, 3);
	T.Insert(5, 5);

	cout << "该二叉树是否为红黑树??" << T.ISRBtree() << endl;

	RBTree<int, int>::Iterator it = T.Begin();

	while (it != T.End())
	{
		//cout << *it << endl;
		++it;
	}
	system("pause");

 }
