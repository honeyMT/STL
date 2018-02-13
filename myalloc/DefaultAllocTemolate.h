#include"alloc.h"

template<bool threads,int inst>
class __DefaultAllocTemplate
{
private:

	union Obj
	{
		Obj* _freeListLink;

		char _client_data[1]; //做硬件层优化
	};

	enum { __ALIGN = 8 };
	enum { __MAX_BYTES = 128 };
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };

	static Obj* __freeList[__NFREELISTS];

	static char* _startFree;
	static char* _endFree;
	static size_t _heapsize;

public:

	static size_t FREE_LIST_INDEX(size_t n) //确定下标.
	{
		return (n + __ALIGN - 1) / __ALIGN - 1;
	}

	static size_t ROUND_UP(size_t n)
	{
		return (n + __ALIGN - 1)&(~(__ALIGN - 1));
	}

	static char* ChunkAlloc(size_t n, size_t& nobjs)
	{
		size_t totalBytes = nobjs*n;
		size_t leftBytes = _endFree - _startFree;

		//足够20个申请小内存.
		if (leftBytes >= totalBytes)
		{
			char* ret = _startFree;
			_startFree += totalBytes;
			return ret;
		}

		//足够一次内存块 但是不足20块.
		else if (leftBytes > n)
		{
			nobjs = leftBytes / n;
			totalBytes = nobjs*n;
			char* ret = _startFree;
			_startFree += totalBytes;

			return ret;
		}

		//一次都不足够
		else
		{
			//先处理剩余的小块内存
			if (leftBytes > 0)
			{
				size_t index = FREE_LIST_INDEX(leftBytes);

				((Obj*)_startFree)->_freeListLink = __freeList[index];
				__freeList[index] = (Obj*)_startFree;
			}
		}

		//尝试向系统申请大块的内存
		size_t bytesToget = totalBytes * 2 + ROUND_UP(_heapsize >> 4);
		_startFree = (char*)malloc(bytesToget);

		//系统也没有申请出空间
		if (_startFree == NULL)
		{
			//去更大的自由链表当中去找.
			size_t index = FREE_LIST_INDEX(n);

			for (; index < __NFREELISTS; ++index)
			{
				Obj* obj = __freeList[index];
				__freeList[index] = obj->_freeListLink;

				_startFree = (char*)obj;
				_endFree = _startFree + (index + 1)*__ALIGN;

				//已经搞出来了空间，让ChunkAlloc函数重新调用.
				return ChunkAlloc(n, nobjs);
			}
			//自由链表中也没有更大的内存块 怕是要凉了.
			//这个时候再尝试调用一级空间配置器. 我们来看看！

			_endFree = NULL;
			_startFree = (char*)__MallocAllocTemplate<0>::Allocate(bytesToget);
		}

		_heapsize += bytesToget;
		_endFree = _startFree + bytesToget;

		return ChunkAlloc(n, nobjs);
	}


	static void* Refill(size_t n)
	{
		size_t nobjs = 20;
		char* chunk = ChunkAlloc(n, nobjs);

		if (nobjs == 1)
		{
			return chunk;
		}

		Obj* cur = (Obj*)(chunk + n);
		size_t index = FREE_LIST_INDEX(n);
		__freeList[index] = cur;

		for (size_t i = 0; i < nobjs - 2; ++i)
		{
			Obj* next = (Obj*)((char*)cur + n);
			cur->_freeListLink = next;
			cur = next;
		}
		cur->_freeListLink = NULL;

		return chunk;
	}

	static void* Allocate(size_t n)
	{
		if (n > __MAX_BYTES)
		{
			return __MallocAllocTemplate<0>::Allocate(n);
		}

		size_t index = FREE_LIST_INDEX(n);
		if (__freeList[index] == 0)
		{
			return Refill(ROUND_UP(n));
		}
		else
		{
			Obj* ret = __freeList[index];
			__freeList[index] = ret->_freeListLink;
			return ret;
		}
	}

	static void Deallocate(void *p, size_t n)
	{
		if (n > __MAX_BYTES)
		{
			return __MallocAllocTemplate<0>::Deallocate(p);
		}

		size_t index = FREE_LIST_INDEX(n);

		((Obj*)p)->_freeListLink = __freeList[index];
		__freeList[index] = (Obj*)p;
	}

};

template<bool threads,int inst>
typename __DefaultAllocTemplate<threads, inst>::Obj*
__DefaultAllocTemplate<threads, inst>::__freeList[__NFREELISTS] = { 0 }; //

template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_startFree = NULL;

template<bool threads,int inst>
char* __DefaultAllocTemplate<threads, inst>::_endFree = NULL;

template<bool threads,int inst>
size_t __DefaultAllocTemplate<threads, inst>::_heapsize = 0;

template<class T,class Alloc>
class simpleAlloc{
public:

	static T* Allocate(size_t n)
	{
		return 0 == n ? 0 : (T*)Alloc::Allocate(n*sizeof(T));
	}

	static T* Allocate(void)
	{
		return (T*)Alloc::Allocate(sizeof(T));
	}

	static void Deallocate(T* p, size_t n)
	{
		if (0 != n)
		{
			Alloc::Deallocate(p, n*sizeof(T));
		}
	}

	static void Deallocate(T* p)
	{
		Alloc::Deallocate(p, sizeof(T));
	}
};

void TestAlloc1()
{	
	int i = 10000;
	while (i--)
	{
		__DefaultAllocTemplate<0, 0>::Allocate(100);
	}
	getchar();

	system("pause");
}

//void* p1 = __DefaultAllocTemplate<0, 0>::Allocate(100);
//void* p2 = __DefaultAllocTemplate<0, 0>::Allocate(100);
//void* p3 = __DefaultAllocTemplate<0, 0>::Allocate(100);
//void* p4 = __DefaultAllocTemplate<0, 0>::Allocate(100);
//void* p5 = __DefaultAllocTemplate<0, 0>::Allocate(100);
//void* p6 = __DefaultAllocTemplate<0, 0>::Allocate(100);
//void* p7 = __DefaultAllocTemplate<0, 0>::Allocate(100);
//void* p8 = __DefaultAllocTemplate<0, 0>::Allocate(100);
//
//getchar();
//
//__DefaultAllocTemplate<0, 0>::Deallocate(p1, 100);
//__DefaultAllocTemplate<0, 0>::Deallocate(p2, 100);
//__DefaultAllocTemplate<0, 0>::Deallocate(p3, 100);
//__DefaultAllocTemplate<0, 0>::Deallocate(p4, 100);
//__DefaultAllocTemplate<0, 0>::Deallocate(p5, 100);
//__DefaultAllocTemplate<0, 0>::Deallocate(p6, 100);
//__DefaultAllocTemplate<0, 0>::Deallocate(p7, 100);
//__DefaultAllocTemplate<0, 0>::Deallocate(p8, 100);