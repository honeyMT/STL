#include<iostream>
#include<vector>

using namespace std;

//һλλͼ
class BitMap
{
public:
	BitMap(size_t range)
	{
		_bitTable.resize((range >> 3) + 1);
	}

	//��ʶһ��������λͼ�е�λ��
	void SetBit(size_t x)
	{
		size_t index = x >> 3;
		size_t num = x % 8;

		_bitTable[index] |= (1 << num);
	}

	//ȡ��������λͼ���еı�ʶ.
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

	//λͼ���������ݳ��ִ���.
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

	//�����Ƿ�С��3
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