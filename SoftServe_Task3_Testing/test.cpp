#include "pch.h"
#include "AnyType.hpp"

TEST(AnyTypeAssignment, AllTypesOfAssignments) 
{
    const signed char sc = 'a';
    const unsigned char usc = 'b';
    const signed short int ssi = 1;
    const unsigned short int usi = 2;
    const signed int si = 3;
    const unsigned int ui = 4;
    const signed long int sli = 5;
    const unsigned long int uli = 6;
    const signed long long int slli = 7;
    const unsigned long long int ulli = 8;
    const std::size_t szt = 9;
    const bool bl = false;
    const wchar_t wchrt = L'a';
    const char16_t ch16 = u'A';
    const char32_t ch32 = U'A';
    const char8_t ch8 = u8'A';
    const float fl = 10.f;
    const double d = 1.0;
    const long double ld = 2.0L;

    AnyType a{};

    EXPECT_NO_THROW(a = sc);
    EXPECT_NO_THROW(a = usc);
    EXPECT_NO_THROW(a = ssi);
    EXPECT_NO_THROW(a = usi);
    EXPECT_NO_THROW(a = si);
    EXPECT_NO_THROW(a = ui);
    EXPECT_NO_THROW(a = sli);
    EXPECT_NO_THROW(a = uli);
    EXPECT_NO_THROW(a = slli);
    EXPECT_NO_THROW(a = ulli);
    EXPECT_NO_THROW(a = szt);
    EXPECT_NO_THROW(a = bl);
    EXPECT_NO_THROW(a = wchrt);
    EXPECT_NO_THROW(a = ch16);
    EXPECT_NO_THROW(a = ch32);
    EXPECT_NO_THROW(a = ch8);
    EXPECT_NO_THROW(a = fl);
    EXPECT_NO_THROW(a = d);
    EXPECT_NO_THROW(a = ld);

    AnyType b{};
    EXPECT_NO_THROW(a = b);
    EXPECT_EQ(a, b);
}

TEST(AnyTypeConversions, Basic)
{
    {
        double from = 0.0;
        AnyType a = from;
        EXPECT_THROW(a.to<int>(), std::bad_cast);
        EXPECT_NO_THROW(a.to<double>());
        EXPECT_EQ(a.to<double>(), from);
    }
    {
        std::size_t from = 0u;
        AnyType a = from;
        EXPECT_THROW(a.to<double>(), std::bad_cast);
        EXPECT_NO_THROW(a.to<std::size_t>());
        EXPECT_EQ(a.to<std::size_t>(), from);
    }
}

TEST(DestroyMethod, Basic)
{
    AnyType empty{};
    AnyType a = 1;
    EXPECT_NE(a, empty);
    EXPECT_NE(a.current_type_identifier(), AnyType::EMPTY_TYPE_IDENTIFIER);
    a.reset();
    EXPECT_EQ(a.current_type_identifier(), AnyType::EMPTY_TYPE_IDENTIFIER);
    EXPECT_EQ(a, empty);
}


TEST(SwapMethod, Basic)
{
    AnyType a = 2.0;
    AnyType b = 1;

    AnyType prev_a = a;
    AnyType prev_b = b;

    a.swap(b);

    EXPECT_EQ(a, prev_b);
    EXPECT_EQ(b, prev_a);
}

TEST(TypeIdentifiers, Basic)
{
    AnyType a = 1;
    EXPECT_EQ(getCurrentTypeOf(a), AlmostFundamentalTypes::SIGNED_INT);
    a = 2.0;
    EXPECT_EQ(getCurrentTypeOf(a), AlmostFundamentalTypes::DOUBLE);
    a = 2.0f;
    EXPECT_EQ(getCurrentTypeOf(a), AlmostFundamentalTypes::FLOAT);
    a = 'a';
    EXPECT_EQ(getCurrentTypeOf(a), AlmostFundamentalTypes::CHAR);
}

TEST(Operators, ArithmeticOperators)
{
    int a_num = 20;
    int b_num = 30;

    AnyType a = a_num;
    AnyType b = b_num;

    AnyType sum = a + b;
    AnyType subtraction = a - b;
    AnyType product = a * b;

    AnyType expected_sum = a_num + b_num;
    AnyType expected_subtraction = a_num - b_num;
    AnyType expected_product = a_num * b_num;

    EXPECT_EQ(sum, expected_sum);
    EXPECT_EQ(subtraction, expected_subtraction);
    EXPECT_EQ(product, expected_product);
}

TEST(Operators, EmptyOperations)
{
    AnyType empty{};
    AnyType non_empty = 2;

    EXPECT_THROW(empty + non_empty, std::invalid_argument);
    EXPECT_THROW(non_empty - empty, std::invalid_argument);
    EXPECT_THROW(empty * empty, std::invalid_argument);

    EXPECT_NE(empty, non_empty);
    EXPECT_NE(non_empty, empty);
    EXPECT_EQ(empty, empty);
}