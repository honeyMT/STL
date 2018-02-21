/************************************************************************************************************************
*************************************************************************************************************************
*************************************************************************************************************************
*                                                                                                                       *
*										vector简单容器实现  			    										 *
*                                             author:张晨亮                                                             *
*                                             Date:2017.12.18                                                           *
*************************************************************************************************************************
*************************************************************************************************************************
*************************************************************************************************************************/

#include"alloc.h"
#include"STLiterator.h"


template<class T, class alloc = __DefaultAllocTemplate<0, 0>>
class Vector
{
public:

	typedef T* Iterator;
	typedef const T* ConstIteartor;

	typedef T ValueType;

	typedef ValueType* pointer;
	typedef const ValueType* const_pointer;

	typedef ValueType* iterator;
	typedef const ValueType* const_iterator;

	typedef ValueType& reference;
	typedef const ValueType& const_reference;

	typedef size_t difference_type;


	typedef ReverseIterator<Iterator> ReverseIterator;
	//typedef ReverseIterator<ConstIteartor> ConstReverseIterator;

	typedef simpleAlloc <T, alloc> data_allocator;

	Vector()
		:_start(0)
		, _finish(0)
		, _endOfStorage(0)
	{}
	
	Iterator Begin()
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}

	ReverseIterator Rbegin()
	{
		return ReverseIterator(End());
	}

	ReverseIterator Rend()
	{
		return ReverseIterator(Begin());
	}

	void pushback(const T& x)
	{

		/*if (_finish == _endOfStorage)
		{
			size_t capacity = Capacity();
			capacity = capacity * 2 + 1;
			Expand(capacity);
		}
		*_finish = n;
		++_finish;*/

		if (_finish != _endOfStorage){
			_Construct(_finish, x);
			++_finish;
		}
		else
			InsertAux(End(), x);
	}

	iterator erase(iterator first, iterator last) {
		iterator i = copy(last, _finish, first);
		//destroy(i, finish);
		_finish = _finish - (last - first);
		return first;
	}

	void insert(iterator position, size_t n, const T& x) {
		if (n != 0) {
			if (size_t(_endOfStorage - _finish) >= n) {
				T x_copy = x;
				const size_t elems_after = _finish - position;
				iterator old_finish = _finish;
				if (elems_after > n) {
					uninitialized_copy(_finish - n, _finish, _finish);
					_finish += n;
					copy_backward(position, old_finish - n, old_finish);
					fill(position, position + n, x_copy);
				}
				else {
					uninitialized_fill_n(_finish, n - elems_after, x_copy);
					_finish += n - elems_after;
					uninitialized_copy(position, old_finish, _finish);
					_finish += elems_after;
					fill(position, old_finish, x_copy);
				}
			}
			else {
				const size_t old_size = size();
				const size_t len = old_size + max(old_size, n);
				iterator new_start = data_allocator::Allocate(len);
				iterator new_finish = new_start;

				new_finish = uninitialized_copy(_start, position, new_start);
				new_finish = uninitialized_fill_n(new_finish, n, x);
				new_finish = uninitialized_copy(position, _finish, new_finish);

				//destroy(_start,_finish);
				data_allocator::Deallocate(_start, sizeof(_start));
				_start = new_start;
				_finish = new_finish;
				_endOfStorage = new_start + len;
			}
		}
	}
	void InsertAux(Iterator pos, const T& x){
		if (_finish != _endOfStorage)
		{}
		else
		{
			const size_t old_size = size();
			const size_t len = old_size != 0 ? 2 * old_size + 1 : 1;
			Iterator new_start = data_allocator::Allocate(len);
			Iterator new_finish = new_start;

			new_finish = uninitialized_copy(_start, pos, new_start);
			_Construct(new_finish, x);

			++new_finish;
			new_finish = uninitialized_copy(pos, _finish, new_finish);

			_start = new_start;
			_finish = new_finish;
			_endOfStorage = new_start + len;
		}
	}


	//void Expand(size_t n)
	//{
	//	if (n < Capacity())
	//	{
	//		return;
	//	}

	//	size_t capacity = Capacity();
	//	T* tmp = new T[n];
	//	Copy(_start, _finish, tmp);
	//	delete[] _start;

	//	_start = tmp;
	//	_endOfStorage = _start + n;
	//	_finish = _start + capacity;
	//}

	void Copy(Iterator start, Iterator finish, Iterator tmp)
	{
		for (int i = 0; i < finish - start; i++)
		{
			tmp[i] = start[i];
		}
	}

	const T& operator[](int position) const
	{
		return _start[position];
	}
	 
	//effiective C++ 上面用到的技巧.
	T& operator[](int position)
	{
		return const_cast<T&>(reinterpret_cast<const Vector<T>&>(*this)[position]);
	}

	void resize(size_t newsize, const T& x)
	{
		if (newsize < size())
			erase(Begin() + newsize, End());
		else
			insert(End(), newsize - size(), x);
	}

	void resize(size_t newsize)
	{
		resize(newsize, T());
	}

	template <class ForwardIterator>
	iterator allocateAndCopy(size_t n,ForwardIterator first, ForwardIterator last) {

		iterator result = data_allocator::Allocate(n);
		uninitialized_copy(first, last, result);
		return result;

	}

	iterator allocateAndCopy(size_t n, const_iterator first, const_iterator last) {

		iterator result = data_allocator::Allocate(n);
		uninitialized_copy(first, last, result);
		return result;
	}
	
	void reserve(size_t n)
	{
		if (Capacity() < n)
		{
			const size_t oldsize = size();
			Iterator tmp = allocateAndCopy(n, _start, _finish);
			data_allocator::Deallocate(_start, sizeof(_start));

			_start = tmp;
			_finish = tmp + oldsize;
			_endOfStorage = _start + n;
		}
	}

	size_t Capacity()
	{
		return (_endOfStorage - _start);
	}
	size_t size()
	{
		return _finish - _start;
	}

	void print()
	{
		cout << "该顺序表内容为 ： ";
		for (size_t i = 0; i < size(); i++)
		{
			cout << _start[i] << " ";
		}
		cout << endl;
	}

	~Vector()
	{
		data_allocator::Deallocate(_start, sizeof(_start));
	}
private:
	Iterator _start;
	Iterator _finish;
	Iterator _endOfStorage;
};

void TestVector()
{
	Vector<int> arr;

	arr.pushback(5);
	arr.pushback(3);
	arr.pushback(2);
	arr.pushback(4);

	Vector<int>::Iterator  it1 = arr.Begin();

	//cout << Distance(arr.Begin(), arr.End()) << endl;
	arr.insert(it1, 3, 1);

	Vector<int>::Iterator  it2 = arr.Begin();
	while (it2 != arr.End())
	{
 		cout << *it2 << " ";
		++it2;
	}
	cout << endl;

	arr.resize(4);

	it2 = arr.Begin();
	while (it2 != arr.End())
	{
		cout << *it2 << " ";
		++it2;
	}
	cout << endl;

	cout << arr.Capacity() << endl;
	arr.reserve(20);
	cout << arr.Capacity() << endl;

	cout << endl;

	/*Vector<int>::ReverseIterator it2 = arr.Rbegin();
	while (it2 != arr.Rend())
	{
		cout << *it2 << " ";
		++it2;
	}
	cout << endl;
	*/
	system("pause");
}


