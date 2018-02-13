#include<iostream>
#include<Windows.h>

using namespace std;

//一级空间配置器
#define _THROW_BAN_ALLOC 0

template<int inst>
class __MallocAllocTemplate
{
public:
	static void* Allocate(size_t n)
	{
		void* result = malloc(n);
		if (0 == result) result = __Oom_Malloc(n);

		return result;
	}

	static void Deallocate(void* p)
	{
		free(p);
	}
	static void* Reallocate(void* p,size_t new_size)
	{
		void* result = realloc(p,new_size);
		if (0 == result) result = __Oom_Realloc(p,new_size);

		return result;
	}

	static void(*Set_Malloc_Handler(void(*f)()))()
	{
		void(*old)() = __Malloc_Alloc_Oom_Handler;
		__Malloc_Alloc_Oom_Handler = f;
		return(old);
	}

private:
	static void(*__Malloc_Alloc_Oom_Handler)();

	static void *__Oom_Malloc(size_t n)
	{
		void(*My_Malloc_Handler)();
		void* result;

		for (;;) 
		{
			My_Malloc_Handler = __Malloc_Alloc_Oom_Handler; //用户自定义处理函数地使用
			if (My_Malloc_Handler == 0) 
				throw _THROW_BAN_ALLOC;
			(*My_Malloc_Handler)(); //调用处理函数释放内存;
			result = malloc(n); //再次开辟内存
			if (result)
				return result;
		}
	}


	static void *__Oom_Realloc(void *p,size_t n)
	{
		void(*My_Malloc_Handler)();
		void* result;

		for (;;)
		{
			My_Malloc_Handler = __Malloc_Alloc_Oom_Handler; //用户自定义处理函数地使用
			if (My_Malloc_Handler == 0 )
				throw _THROW_BAN_ALLOC;
			(*My_Malloc_Handler)(); //调用处理函数释放内存;
			result = realloc(p,n); //再次开辟内存
			if (result)
				return result;
		}
	}
};

template<int inst>
void(*__MallocAllocTemplate<inst>::__Malloc_Alloc_Oom_Handler)() = 0; //默认为0

typedef __MallocAllocTemplate<0> malloc_alloc;


void DoFreeAlloc()
{
	for (int i = 0;; ++i)
	{
		cout << "我正在拼命地释放空间\n" << endl;
	}
}


void Test()
{
	malloc_alloc::Set_Malloc_Handler(DoFreeAlloc);
	
	int* p = (int*)malloc_alloc::Allocate(sizeof(int*)* 1000000000);

	malloc_alloc::Deallocate(p);

	system("pause");
}


//int* p = (int*)malloc_alloc::Allocate(sizeof(int)* 10);
//
//for (size_t i = 0; i < 10; ++i)
//{
//	p[i] = i;
//}
//
//p = (int*)malloc_alloc::Reallocate(p, sizeof(int)* 20);
//for (int i = 10; i < 20; ++i)
//{
//	p[i] = i * 3;
//}
//
//for (int i = 0; i < 20; ++i)
//{
//	cout << p[i] << " ";
//}