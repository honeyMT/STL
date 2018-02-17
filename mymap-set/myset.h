#include"RBTree.h"

template<class K>
class mySet
{
public:
	typedef K ValueType;
	struct KeyOfKey
	{
		const ValueType& operator()(const ValueType& key)
		{
			return key;
		}
	};

	typedef typename RBTree<K, K,KeyOfValue>::Iterator Iterator;
	//如果没有typename，编译器就会去RBTree里面去寻找Iterator.但是RBTree并没有实例化，所以会找不到
	//然后报错. 所以typename告诉编译器这个类型是一个模板的类型，现在先不要确定它的类型.

	pair<Iterator, bool>insert(const K& key)
	{
		return Tree.Insert(key);
	}

	Iterator Begin()
	{
		return Tree.Begin();
	}

	Iterator End()
	{
		return Tree.End();
	}


protected:

	RBTree<K, ValueType, KeyOfKey> Tree;
};


void Test()
{
	mySet<int> T;

	T.insert(1);
	T.insert(2);
	T.insert(3);
	T.insert(4);
	T.insert(5);
	T.insert(6);
	T.insert(7);

	mySet<int>::Iterator it = T.Begin();

	while (it != T.End())
	{
		cout << *it << " ";
		++it;
	}

	cout << endl;

}