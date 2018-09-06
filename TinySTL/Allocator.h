
#include "stdafx.h"
#include "Alloc.h"
#include "Construct.h"
#include <cassert>
#include <new>

namespace TinySTL
{
	/*空间配置器,以变量数目为单位分配*/
	template<class T,class Alloc>
	class simple_alloc
	{
	public:
		typedef T  value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	public:
		//内存配置由alloc::allocate()负责，内存释放操作由alloc::deallocate()负责
		//对象构造操作由 ：：construct()负责，对象析构操作由：：destroy()负责

		static T *allocate()
		{
			return static_cast<T *>(alloc::allocate(sizeof(T)));
		}
		static T *allocate(size_t n)
		{
			if (n == 0)  return 0;
			return static_cast<T *>(alloc::allocate(sizeof(T)*n));
		}
		static void deallocate(T *ptr)
		{
			alloc::deallocate(static_cast<void*>(ptr), sizeof(T));
		}
		static void deallocate(T *ptr, size_t n)
		{
			if (n == 0) return;
			alloc::deallocate(static_cast<void*>(ptr), sizeof(T)*n);
		}

		static void construct(T *ptr)
		{
			//placement new就是在用户指定的内存位置上构建新的对象，
			//这个构建过程不需要额外分配内存，只需要调用对象的构造函数即可。
			new(ptr)T(); //placementnew写法 
		}
		static void construct(T* ptr, const T& value)
		{
			new(ptr)T(value);
		}
		static void destroy(T *ptr)
		{
			ptr->~T();
		}
		static void destroy(T *first, T *last)
		{
			for (; first != last; ++first)
				first->~T();
		}
	};
}

