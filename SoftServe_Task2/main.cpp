#include <iostream>
#include <variant>

#include "AnyType.hpp"
#include "CustomTypeTraits.hpp"


int main()
{
	AnyType<int, double, float> a = 1.0;


	std::cout << a.current_type_identifier() << '\n';
	a = 1;
	std::cout << a.current_type_identifier() << '\n';
	a = 1.0f;
	std::cout << a.current_type_identifier() << '\n';

	static_assert(TypeTraits::is_in_list<int, int>());

	a = 1;
	int a_int = a.to<int>();
	std::cout << "converted = " << a_int << '\n';

	try
	{
		double a_long = a.to<double>();
	}
	catch (const std::bad_cast& ex)
	{
		std::cout << ex.what() << '\n';
	}

	/*AnyTypeStorage<std::size_t, double, int> storage{};
	get_value_by_index<1u>(storage) = 2;

	std::cout << get_value_by_index<1u>(storage) << '\n';

	std::cout << sizeof (decltype(storage)) << '\n';
	std::cout << storage.head() << '\n';
	std::cout << storage.tail().head() << '\n';*/

	return EXIT_SUCCESS;
}