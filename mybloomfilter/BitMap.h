#include<iostream>
#include<vector>

using namespace std;

//一位位图
class BitMap
{
public:
	BitMap(size_t range)
	{
		_bitTable.resize((range >> 3) + 1);
	}

	//标识一个数字在位图中的位置
	void SetBit(size_t x)
	{
		size_t index = x >> 3;
		size_t num = x % 8;

		_bitTable[index] |= (1 << num);
	}

	//取消数字在位图当中的标识.
	void RemoveBit(size_t x)
	{
		size_t index = x >> 3;
		size_t num = x % 8;

		_bitTable[index] &= ~(1 << num);
	}


	bool TestBit(size_t x)
	{
		size_t index = x >> 3;
		size_t num = x % 8;

		return _bitTable[index] & (1 << num);
	}

private:
	vector<char> _bitTable;
};


class NBitMap
{
public:

	NBitMap(int range)
	{
		_bitTable.reserve((range >> 2) + 1);
	}

	//位图中增加数据出现次数.
	void Add(size_t x)
	{
		size_t index = x >> 2;
		size_t num = x % 4;
		num *= 2;

		bool first = _bitTable[index] & (1 << num);
		bool second = _bitTable[index] & (1 << (num + 1));

		if (!(first && second))
		{
			_bitTable[index] += (1 << num);
		}

	}

	//检验是否小于3
	int Test(size_t x)
	{
		size_t index = x >> 2;
		size_t num = x % 4;

		num *= 2;
		return (_bitTable[index] >> num) & 0x03;
	}

private:
	vector<char> _bitTable;
};