#ifndef SIMPLE_VECTOR_HEADER
#define SIMPLE_VECTOR_HEADER

__STXXL_BEGIN_NAMESPACE

template < class _Tp /*, class _Alloc=__STL_DEFAULT_ALLOCATOR(_Tp) */  >
	class simple_vector
{

	simple_vector ()
	{
	};
  public:
	typedef size_t size_type;
	typedef _Tp value_type;
//  typedef simple_alloc<_Tp, _Alloc> _data_allocator;
  protected:
	size_type _size;
	value_type *_array;
  public:

	typedef value_type *iterator;
	typedef const value_type *const_iterator;
	typedef value_type & reference;
	typedef const value_type & const_reference;

  simple_vector (size_type sz):_size (sz)
	{
		//    _array = _data_allocator.allocate(sz);
		_array = new _Tp[sz];
	}
	~simple_vector ()
	{
		//    _data_allocator.deallocate(_array,_size);
		delete [] _array;
	}
	iterator begin ()
	{
		return _array;
	}
	const_iterator begin () const
	{
		return _array;
	}
	iterator end ()
	{
		return _array + _size;
	}
	const_iterator end () const
	{
		return _array + _size;
	}
	size_type size () const
	{
		return _size;
	}
	reference operator [] (size_type i)
	{
		return *(begin () + i);
	}
	const_reference operator [] (size_type i) const
	{
		return *(begin () + i);
	}
};

__STXXL_END_NAMESPACE

#endif
