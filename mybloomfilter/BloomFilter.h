#include"BitMap.h"
#include<string>


template<class K>
struct __HashFunc1
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

	size_t operator()(const K& key)
	{
		return  BKDRHash(key.c_str());
	}
};


template<class K>
struct __HashFunc2
{
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}
		return hash;
	}

	size_t operator()(const K& key)
	{
		return  SDBMHash(key.c_str());
	}
};


template<class K>
struct __HashFunc3
{
	size_t APHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}

	size_t operator()(const K& key)
	{
		return  APHash(key.c_str());
	}
};


template<class K = string, class HashFunc1 = __HashFunc1<K>, class HashFunc2 = __HashFunc2<K>, class HashFunc3 = __HashFunc3<K>>
class BloomFilter
{
public:

	BloomFilter(size_t num)
		:_bm(num * 5)
		, _bitSize(num * 5)
	{}

	void Set(const K& key)
	{
		size_t index1 = HashFunc1()(key);
		_bm.SetBit(index1);

		size_t index2 = HashFunc2()(key);
		_bm.SetBit(index2);

		size_t index3 = HashFunc3()(key);
		_bm.SetBit(index3);
	}

	bool Test(const K& key)
	{
		size_t index1 = HashFunc1()(key);
		if (_bm.TestBit(index1) == false)
		{
			return false;
		}

		size_t index2 = HashFunc2()(key);
		if (_bm.TestBit(index2) == false)
		{
			return false;
		}

		size_t index3 = HashFunc3()(key);
		if (_bm.TestBit(index3) == false)
		{
			return false;
		}

		//所有位置都为真. 但是它是不准确的.
		return true;
	}

private:
	BitMap _bm;
	size_t _bitSize;
};

void Test()
{
	BloomFilter<> T(4000000000);

	T.Set("12312312411231215151251251252151251");
	T.Set("12312312411231215151251251252151252");
	T.Set("12312312411231215151251251252151253");
	T.Set("12312312411231215151251251252151254");
	T.Set("12312312411231215151251251252151255");
	T.Set("12312312411231215151251251252151256");
	T.Set("12312312411231215151251251252151257");

	cout << T.Test("12312312411231215151251251252151251") << endl;
	cout << T.Test("12312312411231215151251251252151252") << endl;
	cout << T.Test("12312312411231215151251251252151253") << endl;
	cout << T.Test("12312312411231215151251251252151254") << endl;
	cout << T.Test("12312312411231215151251251252151255") << endl;
	cout << T.Test("12312312411231215151251251252151256") << endl;
	cout << T.Test("12312312411231215151251251252151257") << endl;

	system("pause");

}