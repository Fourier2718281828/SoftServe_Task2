#include <iostream>
#include "AnyType.hpp"

template<typename T>
concept OstreamPrintable = requires(T a, std::ostream & stream)
{
	{ stream << a } -> std::same_as<std::ostream&>;
};

struct Printer
{
	template<OstreamPrintable T>
	void operator() (const T& actual_value)
	{
		std::cout << actual_value;
	}

	void operator() (const wchar_t& actual_value)
	{
		std::wcout << actual_value;
	}
};

void print(AnyType a)
{
	a.visit(Printer{});
}

int main()
{
	static_assert(std::is_default_constructible_v <AnyType>);
	static_assert(std::is_copy_constructible_v <AnyType>);
	static_assert(std::is_copy_assignable_v <AnyType>);
	static_assert(std::is_move_constructible_v <AnyType>);
	static_assert(std::is_move_assignable_v <AnyType>);


	AnyType empty{};
	AnyType a = 1;
	AnyType chhh = u8'a';

	print(chhh);
	std::cout << '\n';
	print(a + chhh);

	BasicAnyType<int, std::size_t> aa = 2;
	BasicAnyType<int, std::size_t> bb = 1;

	aa = aa << bb;
	aa.visit([](const int aaaa) {std::cout << aaaa << '\n'; });

	a.reset();

	std::cout << (a == empty) << '\n';
	std::cout << (a != empty) << '\n';

	return EXIT_SUCCESS;
}