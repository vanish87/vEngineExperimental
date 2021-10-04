
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
			explicit constexpr Vector(const Vector &other) {} //copy constructor
			explicit constexpr Vector(const T &other) {std::cout<<"call";}
			constexpr Vector &operator=(const Vector &other) { return *this;} //assignment operator

			virtual ~Vector() {}// virtual destructor

			constexpr Vector(const Vector &&other) {} //move constructor
			constexpr Vector &operator=(const Vector &&other) {} //move operator

			//ambiguous/undefined actions
			explicit constexpr Vector(const T *other) noexcept {} // constructor obj with pointer
		};

	}
}

#endif
