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

	////***1*** �������Ĳ���
	//T.insert(pair<int, int>(1, 1));
	//T.insert(pair<int, int>(2, 2));
	//T.insert(pair<int, int>(3, 3));
	////����������Ĳ������������û��ǰ����ģ���Ϊ�������Ḻ����㰲��λ��
	////���ﲻ��Ҫ�����.

	//T.insert(mymake_pair(4, 4));
	//T.insert(mymake_pair(5, 5));
	//T.insert(mymake_pair(6, 6));

	//map<int, int>::iterator it1 = T.begin();

	//cout << "����T�е�Ԫ��:" << endl;
	//while (it1 != T.end())
	//{
	//	cout << it1->second << " ";
	//	cout << "��valΪ" << " ";
	//	cout << it1->first << endl;
	//	++it1;
	//}
	//cout << endl;

	////***2** ���õ����������������

	//std::map<int, int> anothermap;
	//anothermap.insert(T.begin(), T.find(4));
	////

	//map<int, int>::iterator it2 = anothermap.begin();

	//cout << "����anothermap�е�Ԫ��:" << endl;
	//while (it2 != anothermap.end())
	//{
	//	cout << it2->second << " ";
	//	cout << "��valΪ " << " ";
	//	cout << it2->first << endl;
	//	++it2;
	//}

	
	//at, begin, end, count, find.

	//map<int, int> T;

	//T[0] = 1;
	//T[1] = 2;
	//T[2] = 3;
	//T[3] = 4;
	////operator[]����ָ���±������.

	//cout << "map�����йؼ�ֵΪ2��valΪ��";
	//cout << T.at(2) << endl;
	////at�������������ֵ��Ӧ��Ԫ��. 

	//cout << "��ͷ������mapԪ��" << endl;
	//map<int, int>::iterator it = T.begin();
	////����map�е�һ��Ԫ��λ�õĵ�����

	//while (it != T.end())
	////����map�����һ��Ԫ����һ��λ�õĵ�����
	//{
	//	cout << it->first << "  ->>>  " << it->second << endl;
	//	++it;
	//	//�õ�������ת����һ��Ԫ�ص�λ��.
	//}

	//cout << "findһ��Ԫ�صĵ��������ҷ�����:";
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

	cout << "����T�е�Ԫ��:" << endl;
	while (it1 != T.end())
	{
		cout << it1->second << " ";
		cout << "��valΪ" << " ";
		cout << it1->first << endl;
		++it1;
	}
	cout << endl;

	//***2*** ɾ������������

	map<int, int>::iterator it3 = T.find(2);
	//ͨ��find�õ��ؼ���Ϊ2�ĵ�����

	T.erase(it3);
	//Ȼ��ɾ����Ԫ��.

	it1 = T.begin();

	cout << "����T�е�Ԫ��:" << endl;
	while (it1 != T.end())
	{
		cout << it1->second << " ";
		cout << "��valΪ" << " ";
		cout << it1->first << endl;
		++it1;
	}
	cout << endl;


	//***2*** ɾ������������

	it3 = T.find(3);
	//ͨ��find�õ��ؼ���Ϊ3�ĵ�����

	T.erase(it3, T.end());
	//ɾ����it3��map�������������нڵ�.

	it1 = T.begin();

	cout << "����T�е�Ԫ��:" << endl;
	while (it1 != T.end())
	{
		cout << it1->second << " ";
		cout << "��valΪ" << " ";
		cout << it1->first << endl;
		++it1;
	}
	cout << endl;


	//***3*** �ռ����� ɾ������Ԫ��.

	T.insert(mymake_pair(1, 1));
	T.insert(mymake_pair(2, 2));
	T.insert(mymake_pair(3, 3));
	T.insert(mymake_pair(4, 4));
	T.insert(mymake_pair(5, 5));
	T.insert(mymake_pair(6, 6));

	T.clear();
	//ɾ������Ԫ��.

	it1 = T.begin();

	cout << "����T�е�Ԫ��:" << endl;
	while (it1 != T.end())
	{
		cout << it1->second << " ";
		cout << "��valΪ" << " ";
		cout << it1->first << endl;
		++it1;
	}
	cout << endl;


 	system("pause");
}