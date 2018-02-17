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
	//���û��typename���������ͻ�ȥRBTree����ȥѰ��Iterator.����RBTree��û��ʵ���������Ի��Ҳ���
	//Ȼ�󱨴�. ����typename���߱��������������һ��ģ������ͣ������Ȳ�Ҫȷ����������.

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