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

	//set<int> T;


	////***1*** ����ͨ�Ĳ��뷽ʽ
	//T.insert(2);
	//T.insert(3);
	//T.insert(4);
	//T.insert(5);
	//T.insert(6);
	////����Ԫ��

	//cout << "����T��Ԫ��: " << " ";
	//set<int>::iterator it1 = T.begin();

	//while (it1 != T.end())
	//
	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;

	////***2*** �������鼯�ϲ���
	//set<int> OtherSet;
	//int arr[10] = { 1, 2, 3, 4, 5 };
	//OtherSet.insert(arr, arr + 3);

	//cout << "����OtherSet��Ԫ��: " << " ";
	//it1 = OtherSet.begin();

	//while (it1 != OtherSet.end())

	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;

	////***3*** ���õ�����������в���

	//set<int> OtherSet2;

	//OtherSet2.insert(T.begin(), T.end());

	//cout << "����OtherSet��Ԫ��: " << " ";
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

	//cout << "����T��Ԫ��: " << " ";
	//set<int>::iterator it1 = T.begin();

	//while (it1 != T.end())

	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;


	////***1***  �ҵ��ڵ������Ȼ��ɾ���ڵ�

	//set<int>::iterator it2 = T.find(2);
	////���ҵ���ֵΪ2�ĵ�������Ȼ��ɾ���õ�����.

	//T.erase(it2);

	//cout << "����T��Ԫ��: " << " ";
	//it1 = T.begin();

	//while (it1 != T.end())

	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;

	////***2*** ɾ��һ������������
	//
	//it2 = T.find(3);

	//T.erase(it2, T.end());
	////ɾ��3��set����������������Ԫ��.

	//cout << "����T��Ԫ��: " << " ";
	//it1 = T.begin();

	//while (it1 != T.end())

	//{
	//	cout << *it1 << "  ";
	//	++it1;
	//}
	//cout << endl;

	////***3*** �ռ����� clear

	//T.clear();

	//cout << "����T��Ԫ��: " << " ";
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