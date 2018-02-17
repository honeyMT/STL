#include<iostream>
#include<Windows.h>
#include<map>

using namespace std;

template<typename K, typename V>
pair<K, V> mymake_pair(const K& key,const V& val)
{
	return pair<K, V>(key, val);
}

void Test()
{

	//map<int, int> T;

	////***1*** 最正常的插入
	//T.insert(pair<int, int>(1, 1));
	//T.insert(pair<int, int>(2, 2));
	//T.insert(pair<int, int>(3, 3));
	////这是最基本的插入操作，这里没有前插后插的，因为搜索树会负责给你安排位置
	////这里不需要你操心.

	//T.insert(mymake_pair(4, 4));
	//T.insert(mymake_pair(5, 5));
	//T.insert(mymake_pair(6, 6));

	//map<int, int>::iterator it1 = T.begin();

	//cout << "遍历T中的元素:" << endl;
	//while (it1 != T.end())
	//{
	//	cout << it1->second << " ";
	//	cout << "的val为" << " ";
	//	cout << it1->first << endl;
	//	++it1;
	//}
	//cout << endl;

	////***2** 利用迭代器进行区间插入

	//std::map<int, int> anothermap;
	//anothermap.insert(T.begin(), T.find(4));
	////

	//map<int, int>::iterator it2 = anothermap.begin();

	//cout << "遍历anothermap中的元素:" << endl;
	//while (it2 != anothermap.end())
	//{
	//	cout << it2->second << " ";
	//	cout << "的val为 " << " ";
	//	cout << it2->first << endl;
	//	++it2;
	//}

	
	//at, begin, end, count, find.

	//map<int, int> T;

	//T[0] = 1;
	//T[1] = 2;
	//T[2] = 3;
	//T[3] = 4;
	////operator[]返回指定下标的引用.

	//cout << "map容器中关键值为2的val为：";
	//cout << T.at(2) << endl;
	////at函数查找输入键值对应的元素. 

	//cout << "从头遍历该map元素" << endl;
	//map<int, int>::iterator it = T.begin();
	////返回map中第一个元素位置的迭代器

	//while (it != T.end())
	////返回map中最后一个元素下一个位置的迭代器
	//{
	//	cout << it->first << "  ->>>  " << it->second << endl;
	//	++it;
	//	//让迭代器跳转到下一个元素的位置.
	//}

	//cout << "find一个元素的迭代器并且访问它:";
	//cout << T.find(3)->first << "  ->>>  " << T.find(3)->second << endl;
	//
	//cout<<T.count(1)<<" ";
	//cout << T.count(2) << " ";
	//cout << T.count(3) << " ";

	map<int, int> T;

	T.insert(mymake_pair(1, 1));
	T.insert(mymake_pair(2, 2));
	T.insert(mymake_pair(3, 3));
	T.insert(mymake_pair(4, 4));
	T.insert(mymake_pair(5, 5));
	T.insert(mymake_pair(6, 6));

	map<int, int>::iterator it1 = T.begin();

	cout << "遍历T中的元素:" << endl;
	while (it1 != T.end())
	{
		cout << it1->second << " ";
		cout << "的val为" << " ";
		cout << it1->first << endl;
		++it1;
	}
	cout << endl;

	//***2*** 删除单个迭代器

	map<int, int>::iterator it3 = T.find(2);
	//通过find拿到关键字为2的迭代器

	T.erase(it3);
	//然后删除该元素.

	it1 = T.begin();

	cout << "遍历T中的元素:" << endl;
	while (it1 != T.end())
	{
		cout << it1->second << " ";
		cout << "的val为" << " ";
		cout << it1->first << endl;
		++it1;
	}
	cout << endl;


	//***2*** 删除迭代器区间

	it3 = T.find(3);
	//通过find拿到关键字为3的迭代器

	T.erase(it3, T.end());
	//删除掉it3到map容器结束的所有节点.

	it1 = T.begin();

	cout << "遍历T中的元素:" << endl;
	while (it1 != T.end())
	{
		cout << it1->second << " ";
		cout << "的val为" << " ";
		cout << it1->first << endl;
		++it1;
	}
	cout << endl;


	//***3*** 终极大招 删除所有元素.

	T.insert(mymake_pair(1, 1));
	T.insert(mymake_pair(2, 2));
	T.insert(mymake_pair(3, 3));
	T.insert(mymake_pair(4, 4));
	T.insert(mymake_pair(5, 5));
	T.insert(mymake_pair(6, 6));

	T.clear();
	//删除所有元素.

	it1 = T.begin();

	cout << "遍历T中的元素:" << endl;
	while (it1 != T.end())
	{
		cout << it1->second << " ";
		cout << "的val为" << " ";
		cout << it1->first << endl;
		++it1;
	}
	cout << endl;


 	system("pause");
}