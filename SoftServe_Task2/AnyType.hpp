#ifndef ANY_TYPE_HPP_
#define ANY_TYPE_HPP_
#include "BasicAnyType.hpp"

enum class AlmostFundamentalTypes
{
	SIGNED_CHAR = 0,
	UNSIGNED_CHAR,
	SIGNED_SHORT_INT,
	UNSIGNED_SHORT_INT,
	SIGNED_INT,
	UNSIGNED_INT,
	SIGNED_LONG_INT,
	UNSIGNED_LONG_INT,
	SIGNED_LONG_LONG_INT,
	UNSIGNED_LONG_LONG_INT,
	STD_SIZE_T,
	BOOL,
	WCHAR_T,
	CHAR16_T,
	CHAR32_T,
	CHAR8_T,
	CHAR,
	FLOAT,
	DOUBLE,
	LONG_DOUBLE,
};

using AnyType = BasicAnyType
<
	signed char,
	unsigned char,
	signed short int,
	unsigned short int,
	signed int,
	unsigned int,
	signed long int,
	unsigned long int,
	signed long long int,
	unsigned long long int,
	std::size_t,
	bool,
	wchar_t,
	char16_t,
	char32_t,
	char8_t,
	char,
	float,
	double,
	long double
> ;

AlmostFundamentalTypes getCurrentTypeOf(const AnyType& val)
{
	return static_cast<AlmostFundamentalTypes>(val.current_type_identifier());
}

#endif // !ANY_TYPE_HPP_
