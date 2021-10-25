
#ifndef VECTOR_H
#define VECTOR_H

#pragma once

#include <array>
#include <iostream>

namespace vEngine
{
	namespace Core
	{
		template <typename T = float, int N = 4>
		class Vector
		{
		private:
			typedef std::array<T, N> DataType;

			DataType data_;

		public:
			constexpr Vector() noexcept : data_{0} {}

			explicit constexpr Vector(const T &other)
			//explicit one parameter constructor to avoid implicit conversion
			{

			}

			constexpr Vector(const Vector &other) 
			//big five - 3: copy constructor
			//called by 
			// 1. ClassA a = b;
			// 2. Func(ClassA a) -> pass by value
			// 3. return temp; -> return by value
			{

			}

			constexpr Vector &operator=(const Vector &other) noexcept
			//big five - 2: assignment operator
			//with const formal paramter
			//with constexpr TODO: to clarify usage of constexpr
			{
				//1.check self assignment
				//2.allocate new object before-> to assure memory before delete existing one
				 return *this;
			} 
			virtual ~Vector() 
			// big five - 1: virtual destructor -> assure desctor of subclass called
			{

			}

			constexpr Vector(const Vector &&other) {} //move constructor
			constexpr Vector &operator=(const Vector &&other) {} //move operator

			//ambiguous/undefined actions
			explicit constexpr Vector(const T *other) noexcept {} // constructor obj with pointer
		};

	}
}

#endif
