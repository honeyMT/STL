#include"RBTree.h"

template<class K,class V>
class MakeMap
{

public:
	typedef pair<K, V> ValueType;

	struct KeyOfValue
	{
		const K& operator()(const ValueType& kv)
		{
			return kv.first;
		}
	};

	typedef typename RBTree<K, ValueType,KeyOfValue>::Iterator Iterator;

	pair<Iterator, bool> Insert(const ValueType& v)
	{
		return _Tree.Insert(v);
	}

	V& operator[](const K& key)
	{
		pair<Iterator,bool> ret = _Tree.Insert(make_pair(key, V()));
		//模板参数的V() 缺省值.
		return ret.first;
	}
	Iterator Begin()
	{
		return _Tree.Begin();
	}

	Iterator End()
	{
		return _Tree.End();
	}
private:
	RBTree<K, ValueType, KeyOfValue> _Tree;
};

void Test()
{
	MakeMap<string, string> dict;

	dict.Insert(make_pair("liangliang", "亮亮"));
	dict.Insert(make_pair("MT", "梦婷"));
	dict.Insert(make_pair("Steam", "吃鸡"));
	dict.Insert(make_pair("type", "字节"));

	MakeMap<string, string>::Iterator it = dict.Begin();

	while (it != dict.End())
	{
		cout << it->second << " ";
		++it;
	}
}