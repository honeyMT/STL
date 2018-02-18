# define _CRT_SECURE_NO_WARNINGS 1
# define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<Windows.h>
using namespace std;

//                                ***智能指针方面的代码***                                     //

//*********************************************************************************************//
//*********************************************************************************************//
//                               ****实现最简单的智能指针****                                  //





//struct AA
//{
//	int a = 10;
//	int b = 20;
//};
//template<class T>
//class A
//{
//public:
//
//	A(T* ptr)
//		:_ptr(ptr)
//	{}
//
//	T* operator->()
//	{
//		return _ptr;
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//	A(A<T>& ap)
//	{}
//	A<T>& operator=(A<T>& ap)
//	{}
//	~A()
//	{delete _ptr;}
//protected:
//	T* _ptr;
//};
//
//int main()
//{
//	A<int>ap1(new int);
//	*ap1 = 10;
//	A<AA>ap2(new AA);
//	cout << *ap1 << endl;
//	cout << (ap2->a)<<"  "<<(ap2->b) << endl;
//	return 0;
//}


//*********************************************************************************************//
//*********************************************************************************************//








//*********************************************************************************************//
//*********************************************************************************************//
//                                 ****//管理权转移****                                        //



//template<class T>
//class AutoPtr
//{
//public:
//
//	AutoPtr(T* ptr)
//		:_ptr(ptr)
//	{}
//
//	T* operator->()
//	{
//		return _ptr;
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//	AutoPtr(AutoPtr<T>& ap)
//	{
//		this->_ptr = ap._ptr;
//		ap._ptr = NULL;
//	}
//	AutoPtr<T>& operator=(AutoPtr<T>& ap)
//	{
//		if (this != &ap)
//		{
//			delete this->_ptr;
//			this->_ptr = ap._ptr;
//			ap._ptr = NULL;
//		}
//		return *this;
//	}
//	~AutoPtr()
//	{
//		cout << "智能指针爸爸已经释放过空间了" << endl;
//		delete _ptr;
//	}
//protected:
//	T* _ptr;
//};
//

//*********************************************************************************************//
//*********************************************************************************************//







//*********************************************************************************************//
//*********************************************************************************************//
//                                 ****简单粗暴 防拷贝智能指针****                             //




//template<class T>
//class ScopedPtr
//{
//public:
//	ScopedPtr()
//	{}
//	AutoPtr(T* ptr)
//		:_ptr(ptr)
//	{}
//
//	T* operator->()
//	{
//		return _ptr;
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//	~AutoPtr()
//	{
//		cout << "智能指针爸爸已经释放过空间了" << endl;
//		delete _ptr;
//	}
//
//protected:
//	ScopedPtr(ScopedPtr<T>& s);
//	ScopedPtr<T> operator=(ScopedPtr<T>& s);
//protected:
//	T* _ptr;
//};
//

//*********************************************************************************************//
//*********************************************************************************************//







//*********************************************************************************************//
//*********************************************************************************************//
//                                 ****计数原理的智能指针***                                  //
//template<class T>
//class shared
//{
//public:
//	shared(T* ptr)
//		:_ptr(ptr)
//		, _num(new int(1))
//	{
//	}
//	shared(const shared<T>& ap)
//		:_ptr(ap._ptr)
//		, _num(ap._num)
//	{
//		++(*_num);
//	}
//	shared<T>& operator=(const shared<T>& ap)
//	{
//		if (_ptr != ap._ptr)
//		{
//			Release();
//			_ptr = ap._ptr;
//			_num = ap._num;
//			++(*_num);
//		}
//		return *this;
//	}
//	T* operator->()
//	{
//		return _ptr;
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//	void Release()
//	{
//		if (0 == (--*_num))
//		{
//			cout << "智能指针爸爸帮你释放空间了" << endl;
//			delete _ptr;
//			delete _num;
//			_ptr = NULL;
//			_num = NULL;
//		}
//	}
//	~shared()
//	{
//		Release();
//	}
//protected:
//	T* _ptr;
//	int* _num;
//};
//
//int main()
//{
//	shared<int>ap1(new int);
//	*ap1 = 2;
//	shared<int>ap2(ap1);
//	cout << *ap2 << endl;
//	shared<int>ap3(new int);
//	ap3 = ap1;
//
//}
//*********************************************************************************************//
//*********************************************************************************************//






//*********************************************************************************************//
//*********************************************************************************************//
//             *** 仿函数实现多方式删除，以及使用计数原理的智能指针***                         //


//计数原理
//运用仿函数实现多方式删除

//使用delete释放空间的仿函数
template<class T>
class Delete
{
public:
	Delete()
	{}
	void operator()(T* _ptr)
	{
		cout << "delete" << endl;
		delete _ptr;
		_ptr = NULL;
	}
	~Delete()
	{}
protected:
	T* _ptr;
};


//使用delete[]释放空间的仿函数
template<class T>
class DeleteArray
{
public:
	DeleteArray()
	{}
	void operator()(T* _ptr)
	{
		cout << "delete[]" << endl;
		delete[] _ptr;
		_ptr = NULL;
	}
	~DeleteArray()
	{}

};


template<class T,class Del = Delete<T>>
class shared
{
public:
	shared(T* ptr)
		:_ptr(ptr)
		, _num(new int(1))
	{
	}
	shared(const shared<T>& ap)
		:_ptr(ap._ptr)
		, _num(ap._num)
	{
		++(*_num);
	}
	shared<T>& operator=(const shared<T>& ap)
	{
		if (_ptr != ap._ptr)
		{
			Release();
			_ptr = ap._ptr;
			_num = ap._num;
			++(*_num);
		}
		return *this;
	}
	T* operator->()
	{
		return _ptr;
	}
	
	T& operator*()
	{
		return *_ptr;
	}
	inline void Release()
	{
		if (0 == (--*_num))
		{
			delete _num;
			_num = NULL;
			Del _del;
			_del(_ptr);
		}
	}
	~shared()
	{
		Release();
	}
protected:
	T* _ptr;
	int* _num;
};

void Test()
{
	shared<int>ap2(new int(1));
	shared<string, DeleteArray<string>>ap1(new string[10]);
}
int main()
{
	
	Test();
	system("pause");
}
/*void _del operator()(DeleteArray* ptr)
{
cout << "delete" << endl;
delete[] ptr;
ptr = NULL;
}

void _del operator()(Delete* ptr)
{
cout << "delete[]" << endl;
delete ptr;
ptr = NULL;
}*/


//*********************************************************************************************//
//*********************************************************************************************//








//*********************************************************************************************//
//*********************************************************************************************//
//                                 ****探究循环引用的例子****                                  //





//#include<memory>
//
//struct ListNode
//{
//	int _data;
//	shared_ptr<ListNode> _prev;
//	shared_ptr<ListNode> _next;
//
//	ListNode(int x)
//		:_data(x)
//		, _prev(NULL)
//		,_next(NULL)
//	{}
//	~ListNode()
//	{
//		cout << "~ListNode" << endl;
//	}
//};
//
//void Test()
//{
//	shared_ptr<ListNode> cur(new ListNode(1));
//	shared_ptr<ListNode> next(new ListNode(2));
//	cur->_next = next;
//	next->_prev = cur;
//	cout << "cur" << "     " << cur.use_count() << endl;
//	cout << "next" << "     " << next.use_count() << endl;
//}
//int main()
//{
//	Test();
//	system("pause");
//	return 0;
//}

//template<class T>
//struct A
//{
//	bool operator()(const T& a,const T& b)
//	{
//		return (a == b);
//	}
//};
//
//int main()
//{
//	A<int>a;
//	cout << a(1, 2) << endl;
//	system("pause");
//	return 0;
//}


//template <typename T1, typename T2>
//class Data
//{
//public:
//	Data();
//private:
//	T1 _d1;
//	T2 _d2;
//};
//template <typename T1, typename T2>
//Data<T1, T2>::Data()
//{
//	cout << "Data<T1, T2>" << endl;
//}
//
//// 局部特化第二个参数
//template <typename T1>
//class Data <T1, int>
//{
//public:
//	Data();
//private:
//	T1 _d1;
//	int _d2;
//};
//template <typename T1>
//Data<T1, int>::Data()
//{
//	cout << "Data<T1, int>" << endl;
//}
//
//template <typename T1>
//class Data <T1, int>
//{
//public:
//	Data();
//private:
//	T1 _d1;
//	int _d2;
//};
//template <typename T1>
//Data<T1, int>::Data()
//{
//	cout << "Data<T1, int>" << endl;
//}
//
//void test2()
//{
//	Data<double, int> d1;
//	Data<int, double> d2;
//}
//
//int main()
//{
//	test2();
//	system("pause");
//	return 0;
//}
