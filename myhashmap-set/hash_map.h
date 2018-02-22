#include"HashTableTypename.h"

template<class K, class V>
class Mymap
{
public:

	typedef pair<K, V> ValueType;

	struct KeyOfkeyValue
	{
		const K& operator()(const ValueType& kv)
		{
			return kv.first;
		}
	};

	//如果你取决于模板参数嵌套内部的问题，那么你需要在它的前面加上typename.
	typedef typename HashTable<K, ValueType, KeyOfkeyValue>::Iterator Iterator;

	Iterator Begin()
	{
		return Table.Begin();
	}

	Iterator End()
	{
		return Table.End();
	}

	pair<Iterator, bool> Insert(const ValueType& kv)
	{
		return Table.Insert(kv);
	}

	bool Remove(const ValueType& kv)
	{
		return Table.Remove(kv);
	}


private:
	HashTable<K, ValueType, KeyOfkeyValue> Table;
};


void Test()
{
	Mymap<string, string> T;
	T.Insert(make_pair("liangliang", "张晨亮"));
	T.Insert(make_pair("MT", "崽崽"));
	T.Insert(make_pair("MOM", "妈妈"));
	T.Insert(make_pair("FA", "爸爸"));

	T.Remove(make_pair("liangliang", "张晨亮"));

	/*Mymap<int, int> T;

	T.Insert(make_pair(1, 1));
	T.Insert(make_pair(2, 2));
	T.Insert(make_pair(3, 3));*/

	Mymap<string,string>::Iterator it1 = T.Begin();

 	while (it1 != T.End())
	{
		cout << it1->second.c_str() << endl;
		++it1;
	}

	system("pause");

}