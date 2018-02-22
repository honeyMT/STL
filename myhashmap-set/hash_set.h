#include"HashTableTypename.h"

template<class K>
class Myset
{

public:
	struct KeyOfKey
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};

	typedef typename HashTable<K, K, KeyOfKey>::Iterator Iterator;

	Iterator Begin()
	{
		return Table.Begin();
	}

	Iterator End()
	{
		return Table.End();
	}

	pair<Iterator, bool> Insert(const K& key)
	{
		return Table.Insert(key);
	}

	bool Remove(const K& key)
	{
		return Table.Remove(key);
	}
	
private:
	HashTable<K, K, KeyOfKey> Table;
};

void Test()
{
	/*Myset<int> T;

  	T.Insert(1);
	T.Insert(2);
	T.Insert(3);
	T.Insert(4);
	T.Insert(5);

	T.Remove(2);*/

	Myset<string> T;

	T.Insert("liangliang");
	T.Insert("MT");
	T.Insert("babab");
	T.Insert("mama");

	T.Remove("liangliang");

	Myset<string>::Iterator it1 = T.Begin();

	while (it1 != T.End())
	{
		cout << *it1->c_str() << endl;
		++it1;
	}

	system("pause");
}