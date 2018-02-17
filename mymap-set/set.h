#include<iostream>
#include<set>
#include<Windows.h>

using namespace std;

void Test()
{

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

	//set<int> T;


	////***1*** 最普通的插入方式
	//T.insert(2);
	//T.insert(3);
	//T.insert(4);
	//T.insert(5);
	//T.insert(6);
	////插入元素

	//cout << "遍历T的元素: " << " ";
	//set<int>::iterator it1 = T.begin();

	//while (it1 != T.end())
	//
	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;

	////***2*** 利用数组集合插入
	//set<int> OtherSet;
	//int arr[10] = { 1, 2, 3, 4, 5 };
	//OtherSet.insert(arr, arr + 3);

	//cout << "遍历OtherSet的元素: " << " ";
	//it1 = OtherSet.begin();

	//while (it1 != OtherSet.end())

	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;

	////***3*** 利用迭代器区间进行插入

	//set<int> OtherSet2;

	//OtherSet2.insert(T.begin(), T.end());

	//cout << "遍历OtherSet的元素: " << " ";
	//it1 = OtherSet2.begin();

	//while (it1 != OtherSet2.end())

	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;

	//set<int> T;
	//int arr[10] = { 1, 2, 3, 4, 6, 7 };

	//T.insert(arr, arr + 6);

	//cout << "遍历T的元素: " << " ";
	//set<int>::iterator it1 = T.begin();

	//while (it1 != T.end())

	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;


	////***1***  找到节点迭代器然后删除节点

	//set<int>::iterator it2 = T.find(2);
	////先找到键值为2的迭代器，然后删除该迭代器.

	//T.erase(it2);

	//cout << "遍历T的元素: " << " ";
	//it1 = T.begin();

	//while (it1 != T.end())

	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;

	////***2*** 删除一个迭代器区间
	//
	//it2 = T.find(3);

	//T.erase(it2, T.end());
	////删除3到set结束这段区间的所有元素.

	//cout << "遍历T的元素: " << " ";
	//it1 = T.begin();

	//while (it1 != T.end())

	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;

	////***3*** 终极大招 clear

	//T.clear();

	//cout << "遍历T的元素: " << " ";
	//it1 = T.begin();

	//while (it1 != T.end())

	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;
	//

	system("pause");
}