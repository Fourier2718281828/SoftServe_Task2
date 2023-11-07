#ifndef OPERATORS_HPP_
#define OPERATORS_HPP_

#include "Concepts.hpp"

struct unary_plus_operator
{
	template<Concepts::Operators::Arithmetic::UnaryPlusable T>
	auto operator() (const T& a)
	{
		return +a;
	}
};

struct unary_minus_operator
{
	template<typename T>
	auto operator() (const T& a)
	{
		return -a;
	}
};

struct add_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a + b;
	}
};

struct subtract_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a - b;
	}
};

struct multyply_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a * b;
	}
};

struct divide_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a / b;
	}
};

struct remainder_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a % b;
	}
};

struct bitwise_negate_operator
{
	template<typename T>
	auto operator() (const T& a)
	{
		return ~a;
	}
};

struct bitwise_or_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a | b;
	}
};

struct bitwise_and_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a & b;
	}
};

struct bitwise_xor_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a ^ b;
	}
};

struct bitwise_left_shift_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a << b;
	}
};

struct bitwise_right_shift_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a >> b;
	}
};

struct equals_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a == b;
	}
};

struct not_equals_operator
{
	template<typename T, typename U>
	auto operator() (const T& a, const U& b)
	{
		return a != b;
	}
};

#endif // !OPERATORS_HPP_
