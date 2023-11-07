#ifndef CONCEPTS_HPP_
#define CONCEPTS_HPP_
#include <concepts>

namespace Concepts
{
	/*template<typename T, typename ReturnValue, typename... Args>
	concept Callable = requires(T f, Args... args)
	{
		{ f(args...) } -> std::same_as<ReturnValue>;
	};*/

	template<typename F, typename... Args>
	concept Callable = requires(F f, Args... args)
	{
		{ f(args...) };
	};

	template<typename F, typename... Args>
	concept SingularCallable = (Callable<F, Args> && ...);

	namespace Operators
	{
		namespace Arithmetic
		{
			template<typename T>
			concept UnaryPlusable = requires(T a)
			{
				{ +a };
			};


			template<typename T>
			concept UnaryMinusable = requires(T a)
			{
				{ -a };
			};

			template<typename T>
			concept Addable = requires(T a, T b)
			{
				{ a + b };
			};

			template<typename T>
			concept Subractable = requires(T a, T b)
			{
				{ a - b };
			};

			template<typename T>
			concept Multipliable = requires(T a, T b)
			{
				{ a * b };
			};

			template<typename T>
			concept Divisible = requires(T a, T b)
			{
				{ a / b };
			};

			template<typename T>
			concept Remaindable = requires(T a, T b)
			{
				{ a % b };
			};

			template<typename T>
			concept BitwiseNegatable = requires(T a)
			{
				{ ~a };
			};

			template<typename T>
			concept BitwiseAndable = requires(T a, T b)
			{
				{ a & b };
			};

			template<typename T>
			concept BitwiseOrable = requires(T a, T b)
			{
				{ a | b };
			};

			template<typename T>
			concept BitwiseXorable = requires(T a, T b)
			{
				{ a ^ b };
			};

			template<typename T>
			concept BitwiseLeftShiftable = requires(T a, T b)
			{
				{ a << b };
			};

			template<typename T>
			concept BitwiseRightShiftable = requires(T a, T b)
			{
				{ a >> b };
			};
		}

		namespace ArithmeticAssignments
		{
			template<typename T>
			concept PlusAssignable = requires(T a, T b)
			{
				{ a += b } -> std::same_as<T&>;
			};

			template<typename T>
			concept MinusAssignable = requires(T a, T b)
			{
				{ a -= b } -> std::same_as<T&>;
			};

			template<typename T>
			concept MultiplyAssignable = requires(T a, T b)
			{
				{ a *= b } -> std::same_as<T&>;
			};

			template<typename T>
			concept DivideAssignable = requires(T a, T b)
			{
				{ a /= b } -> std::same_as<T&>;
			};

			template<typename T>
			concept RemainderAssignable = requires(T a, T b)
			{
				{ a %= b } -> std::same_as<T&>;
			};

			template<typename T>
			concept BitwiseAndAssignable = requires(T a, T b)
			{
				{ a &= b } -> std::same_as<T&>;
			};

			template<typename T>
			concept BitwiseOrAssignable = requires(T a, T b)
			{
				{ a |= b } -> std::same_as<T&>;
			};

			template<typename T>
			concept BitwiseXorAssignable = requires(T a, T b)
			{
				{ a ^= b } -> std::same_as<T&>;
			};

			template<typename T>
			concept BitwiseLeftShiftAssignable = requires(T a, T b)
			{
				{ a <<= b } -> std::same_as<T&>;
			};

			template<typename T>
			concept BitwiseRightShiftAssignable = requires(T a, T b)
			{
				{ a >>= b } -> std::same_as<T&>;
			};
		}

		namespace IncrementDecrements
		{
			template<typename T>
			concept PreIncrementable = requires(T a)
			{
				{ ++a } -> std::same_as<T&>;
			};

			template<typename T>
			concept PostIncrementable = requires(T a)
			{
				{ a++ } -> std::same_as<T>;
			};

			template<typename T>
			concept PreDecrementable = requires(T a)
			{
				{ --a } -> std::same_as<T&>;
			};

			template<typename T>
			concept PostDecrementable = requires(T a)
			{
				{ a-- } -> std::same_as<T>;
			};
		}

		namespace Logical
		{
			template<typename T>
			concept Negatable = requires(T a)
			{
				{ !a } -> std::same_as<bool>;
			};

			template<typename T>
			concept Andable = requires(T a, T b)
			{
				{ a && b } -> std::same_as<bool>;
			};

			template<typename T>
			concept Orable = requires(T a, T b)
			{
				{ a || b } -> std::same_as<bool>;
			};
		}

		namespace Comparison
		{
			template<typename T>
			concept Equatable = requires(T a, T b)
			{
				{ a == b } -> std::same_as<bool>;
			};

			template<typename T>
			concept Inequatable = requires(T a, T b)
			{
				{ a != b } -> std::same_as<bool>;
			};

			template<typename T>
			concept Lessable = requires(T a, T b)
			{
				{ a < b } -> std::same_as<bool>;
			};

			template<typename T>
			concept Greaterable = requires(T a, T b)
			{
				{ a > b } -> std::same_as<bool>;
			};

			template<typename T>
			concept LessEqualsable = requires(T a, T b)
			{
				{ a <= b } -> std::same_as<bool>;
			};

			template<typename T>
			concept GreaterEqualsable = requires(T a, T b)
			{
				{ a >= b } -> std::same_as<bool>;
			};

			template<typename T>
			concept SpaceshipComparable = requires(T a, T b)
			{
				a <=> b;
			};
		}
	}
}


#endif // !CONCEPTS_HPP_
