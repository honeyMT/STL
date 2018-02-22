#include<iostream>
#include<windows.h>
#include<assert.h>
#include<vector>

using namespace std;

static size_t GetNextPrime(size_t value)
{
	// 使用素数表对齐做哈希表的容量，降低哈希冲突
	const int _PrimeSize = 28;
	static const unsigned long _PrimeList[_PrimeSize] =
	{
		53ul, 97ul, 193ul, 389ul, 769ul,
		1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
		49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
		1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
		50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};

	for (size_t i = 0; i < _PrimeSize; ++i)
	{
		if (_PrimeList[i] > value)
		{
			return _PrimeList[i];
		}
	}

	return _PrimeList[_PrimeSize - 1];
}

template<class K>
struct __HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};


template<>
struct __HashFunc<string>
{
	static size_t BKDRHash(const char * str)
	{
		unsigned int seed = 131; // 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}

	size_t operator()(const string& key)
	{
		return  BKDRHash(key.c_str());
	}
};


template<class ValueType>
struct HashNode
{
	ValueType _ValueFired;
	HashNode<ValueType>* _next;

	HashNode(const ValueType& T)
		:_ValueFired(T)
		, _next(NULL)
	{}
};

template<class K, class V,class KeyOfValue,class HashFunc = __HashFunc<K>>
class HashTable;

template<class K,class V, class KeyOfValue,class HashFunc = __HashFunc<K>>
struct HashTableIterator
{
	typedef V ValueType;
	KeyOfValue keyofvalue;

	typedef HashNode<ValueType> Node;
	typedef HashTableIterator<K,ValueType,KeyOfValue,HashFunc> self;

	Node* _node;
	HashTable<K,V,KeyOfValue, HashFunc>* _ht;


	HashTableIterator(HashNode<ValueType>* node, HashTable<K, ValueType, KeyOfValue, HashFunc>* ht)
		:_node(node)
		, _ht(ht)
	{}

	ValueType& operator*()
	{
		return _node->_ValueFired;
	}

	ValueType* operator->()
	{
		return &(operator*());
	}

	self& operator++()
	{
		//1.如果当前桶没走完，进行往下走.
		//2.如果走完，那么找到下一个非空桶.
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			HashFunc Hashfunc;
			size_t index = Hashfunc(keyofvalue(_node->_ValueFired)) % _ht->_tables.size();
			_node = NULL;

			for (size_t i = index + 1; i < _ht->_tables.size(); ++i)
			{
				if (_ht->_tables[i] != NULL)
				{
  					_node = _ht->_tables[i];
					break;
				}
			}
		}
		return *this;
	}

	self& operator--()
	{
		HashFunc Hashfunc;
		size_t index = Hashfunc(_node->_kv.first) % _ht->_tables.size();
		Node* cur = NULL;

		if (_node->_next == NULL)
		{
			cur = _ht->_tables[index];
			for (size_t i = index - 1; i > 0; i--)
			{
				if (_ht->_tables[i] != NULL)
				{
					cur = _ht->_tables[i];

					while (cur)
					{
						cur = cur->_next;
					}

					_node = cur;
				}
			}
		}
		else
		{
			cur = _ht->_tables[index];
			while (cur->_next != _node)
			{
				cur = cur->_next;
			}

			_node = cur;
		}
		return *this;
	}

	bool operator==(const self& T)
	{
		return _node == T._node;
	}

	bool operator!=(const self& T)
	{
		return _node != T._node;
	}


};


template<class K, class V, class KeyOfValue, class HashFunc = __HashFunc<K>>
class HashTable
{
	
public:

	typedef V ValueType;
	friend struct HashTableIterator<K, ValueType, KeyOfValue, HashFunc>;

	typedef HashNode<ValueType> Node;
	typedef HashTableIterator<K, ValueType, KeyOfValue, HashFunc> Iterator;

	Iterator Begin()
	{
		size_t index = 0;
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			if (_tables[i] != NULL)
			{
				return Iterator(_tables[i], this);
			}
		}
		return Iterator(NULL, this);
	}

	Iterator End()
	{
		return Iterator(NULL, this);
	}

	HashTable()
		:_n(0)
	{}

	pair<Iterator, bool> Insert(const ValueType& kv)
	{
		KeyOfValue keyofvalue;
		_CheckCapacity();

		size_t i = 1;
		size_t index = _HashFunc(keyofvalue(kv), _tables.size());

		Node* newNode = new Node(kv);

		if (_tables[index] == NULL)
		{
			_tables[index] = newNode;
		}
		else
		{
			Node* cur = _tables[index];

			while (cur)
			{
				if (keyofvalue(cur->_ValueFired) == keyofvalue(kv))
				{
					return pair<Iterator, bool>(Iterator(cur,this), false);
				}
				cur = cur->_next;
			}

			newNode->_next = _tables[index];
			_tables[index] = newNode;
		}
		++_n;

		return pair<Iterator, bool>(Iterator(newNode,this), false);
	}


	HashNode<ValueType>* Find(const ValueType& kv)
	{
		KeyOfValue keyofvalue;
			size_t index = _HashFunc(keyofvalue(kv), _tables.size());

		if (_tables[index] != NULL)
		{
			Node* cur = _tables[index];
			while (cur)
			{
				if (keyofvalue(cur->_ValueFired) == keyofvalue(kv))
				{
					return cur;
				}
				cur = cur->_next;
			}
		}

		return NULL;
	}

	bool Remove(const ValueType& kv)
	{
		KeyOfValue keyofvalue;
		HashNode<ValueType>* node = Find(kv);
		if (node)
		{
			size_t index = _HashFunc(keyofvalue(kv), _tables.size());
			Node* cur = _tables[index];
			if (_tables[index] == NULL)
				return false;

			else if (_tables[index]->_next == NULL)
			{
				delete node;
				_tables[index] = NULL;
			}
			else
			{
				while (cur)
				{
					if (cur->_next == node)
					{
						break;
					}
					cur = cur->_next;
				}
				cur->_next = node->_next;
				delete node;
			}
			--_n;
			return true;
		}
		return false;
	}

	size_t Size()
	{
		return _n;
	}

	size_t Capacity()
	{
		return _tables.size();
	}

protected:
	//当然我们在这里使用传统的Insert是没有问题的. 但是优秀的程序员需要优化代码. 那么我可不可把这个桶上面的节点
	//直接拿出来头插到对应节点的位置.
	void _CheckCapacity()
	{
		KeyOfValue keyofvalue;
		if (_tables.empty())
		{
			_tables.resize(GetNextPrime(0));
			return;
		}

		if (_n * 10 / _tables.size() >= 7)
		{
			size_t newSize = GetNextPrime(_tables.size());
			HashTable<K, V, KeyOfValue,HashFunc> newHaseTable;
			newHaseTable._tables.resize(newSize);
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				Node* next = cur->_next;
				while (cur)
				{
					next = cur->_next;

					size_t index = _HashFunc(keyofvalue(cur->_ValueFired), newHaseTable._tables.size());

					cur->_next = newHaseTable._tables[index];
					newHaseTable._tables[index] = cur;

					cur = next;
				}
				_tables[i] = NULL;
			}
			_tables.swap(newHaseTable._tables);
		}
	}


	size_t _HashFunc(const K& key, size_t size)
	{
		HashFunc hash;
		return (hash(key) % size);
	}
	
private:
	vector<Node*> _tables;
	size_t _n;
};

