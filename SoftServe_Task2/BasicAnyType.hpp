#ifndef BASIC_ANY_TYPE_HPP_
#define BASIC_ANY_TYPE_HPP_
#include "CustomTypeTraits.hpp"
#include "Concepts.hpp"
#include "Operators.hpp"

template<TypeTraits::AlmostFundamental... T>
class AnyTypeStorage;

template<typename Head, typename... Tail>
class AnyTypeStorage<Head, Tail...>
{
public:

	constexpr AnyTypeStorage() noexcept = default;

public:

	[[nodiscard]] constexpr Head& head() noexcept
	{
		return head_;
	}

	[[nodiscard]] constexpr const Head& head() const noexcept
	{
		return head_;
	}

	[[nodiscard]] constexpr AnyTypeStorage<Tail...>& tail() noexcept
	{
		return tail_;
	}

	[[nodiscard]] constexpr const AnyTypeStorage<Tail...>& tail() const noexcept
	{
		return tail_;
	}

private:

	union
	{
		Head head_;
		AnyTypeStorage<Tail...> tail_;
	};
};

template<>
class AnyTypeStorage<> {};

template<std::size_t Index, typename Head, typename... Tail>
constexpr auto& get_value_by_index(AnyTypeStorage<Head, Tail...>& storage)
{
	static_assert(Index <= sizeof...(Tail), "Index out of pack's bounds.");

	if constexpr (Index == 0)
	{
		return storage.head();
	}
	else
	{
		return get_value_by_index<Index - 1, Tail...>(storage.tail());
	}
}

template<typename U, typename... T>
concept AcceptableType = TypeTraits::AlmostFundamental<U> &&
TypeTraits::is_in_list<U, T...>();

template<typename U, typename... T>
concept TypeIdentifier = std::integral<U>;

template<TypeTraits::AlmostFundamental... T>
class BasicAnyType
{
private:

	static_assert(sizeof...(T) > 0, "BasicAnyType is supposed to be based on a non-empty type set.");

public:

	static constexpr const std::size_t
		EMPTY_TYPE_IDENTIFIER = ~static_cast<std::size_t>(0u);

	template<std::size_t Index>
	using TypeAtIndex = TypeTraits::TypeAtIndex_t<Index, T...>;

	template<Concepts::SingularCallable<T...> Callable>
	using VisitResult = decltype(std::invoke(std::declval<Callable>(), std::declval<TypeTraits::head_t<T...>>()));

public:

	BasicAnyType() :
		storage_{},
		current_type_identifier_{ EMPTY_TYPE_IDENTIFIER }
	{

	}

	template<AcceptableType<T...> U>
	/* implicit */ BasicAnyType(const U some_value) noexcept :
		storage_{},
		current_type_identifier_{ get_type_identifier<U>() }
	{
		auto& actual_value_ref = get_value_reference<U>();
		actual_value_ref = some_value;
	}

	template<AcceptableType<T...> U>
	[[nodiscard]] constexpr U to()
	{
		std::size_t type_identifier = get_type_identifier<U>();

		if (current_type_identifier_ == type_identifier)
		{
			return get_value_reference<U>();
		}
		else
		{
			throw std::bad_cast{};
		}
	}

	template<Concepts::SingularCallable<T...> Visitor>
	VisitResult<Visitor> visit(Visitor&& visitor)
	{
		const std::size_t current_index = current_type_identifier();
		return static_cast<VisitResult<Visitor>>(visit_impl<Visitor, T...>(std::forward<Visitor>(visitor), current_index));
	}

	template<Concepts::SingularCallable<T...> Visitor, typename Head, typename... Tail>
	VisitResult<Visitor> visit_impl(Visitor&& visitor, std::size_t current_index)
	{
		if (TypeTraits::index_of_type<Head, T...>() == current_index)
		{
			return visitor(get_value_reference<Head>());
		}
		else
		{
			return visit_impl<Visitor, Tail...>(std::forward<Visitor>(visitor), current_index);
		}
	}

	template<Concepts::SingularCallable<T...> Visitor>
	VisitResult<Visitor> visit_impl(Visitor&& visitor, std::size_t current_index)
	{
		throw std::out_of_range("No matching type found for the current index.");
	}

	void reset() noexcept
	{
		(*this) = BasicAnyType();
	}

	void swap(BasicAnyType& other)
	{
		std::swap(*this, other);
	}

	std::size_t current_type_identifier() const noexcept
	{
		return current_type_identifier_;
	}

	bool is_empty() const noexcept 
	{
		return current_type_identifier() == EMPTY_TYPE_IDENTIFIER;
	}

private:

	template<AcceptableType<T...> U>
	[[nodiscard]] std::size_t get_type_identifier()
	{
		return TypeTraits::index_of_type<U, T...>();
	}

	template<AcceptableType<T...> U>
	[[nodiscard]] auto& get_value_reference()
	{
		static constexpr std::size_t type_index = TypeTraits::index_of_type<U, T...>();
		return get_value_by_index<type_index>(storage_);
	}

private:
	AnyTypeStorage<T...> storage_;
	std::size_t current_type_identifier_;
};

template<typename Operator, typename... T>
auto binary_operator(Operator&& f, BasicAnyType<T...> a, BasicAnyType<T...> b)
{
	if (a.is_empty() || b.is_empty())
	{
		throw std::invalid_argument("Trying to apply an operator to an empty AnyType value");
	}

	auto c = a.visit([&b, &f](const auto& left) {
		return b.visit([&left, &f](const auto& right) {
			return f(left, right);
		});
	});

	return c;
}

template<Concepts::Operators::Arithmetic::Addable... T>
BasicAnyType<T...> operator+ (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b)
{
	return binary_operator(add_operator{}, a, b);
}

template<Concepts::Operators::Arithmetic::Subractable... T>
BasicAnyType<T...> operator- (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b)
{
	return binary_operator(subtract_operator{}, a, b);
}

template<Concepts::Operators::Arithmetic::Multipliable... T>
BasicAnyType<T...> operator* (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b)
{
	return binary_operator(multyply_operator{}, a, b);
}

template<Concepts::Operators::Arithmetic::Divisible... T>
BasicAnyType<T...> operator/ (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b)
{
	return binary_operator(divide_operator{}, a, b);
}

template<Concepts::Operators::Arithmetic::Remaindable... T>
BasicAnyType<T...> operator% (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b)
{
	return binary_operator(remainder_operator{}, a, b);
}

template<Concepts::Operators::Arithmetic::BitwiseAndable... T>
BasicAnyType<T...> operator& (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b)
{
	return binary_operator(bitwise_and_operator{}, a, b);
}

template<Concepts::Operators::Arithmetic::BitwiseOrable... T>
BasicAnyType<T...> operator| (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b)
{
	return binary_operator(bitwise_or_operator{}, a, b);
}

template<Concepts::Operators::Arithmetic::BitwiseXorable... T>
BasicAnyType<T...> operator^ (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b)
{
	return binary_operator(bitwise_xor_operator{}, a, b);
}

template<Concepts::Operators::Arithmetic::BitwiseLeftShiftable... T>
BasicAnyType<T...> operator<< (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b)
{
	return binary_operator(bitwise_left_shift_operator{}, a, b);
}

template<Concepts::Operators::Arithmetic::BitwiseRightShiftable... T>
BasicAnyType<T...> operator>> (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b)
{
	return binary_operator(bitwise_right_shift_operator{}, a, b);
}

template<Concepts::Operators::Comparison::Equatable... T>
bool operator== (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b) noexcept
{
	if (a.is_empty() && b.is_empty())
	{
		return true;
	}

	try
	{
		return binary_operator(equals_operator{}, a, b);
	}
	catch (...)
	{
		return false;
	}
}

template<Concepts::Operators::Comparison::Inequatable... T>
bool operator!= (const BasicAnyType<T...>& a, const BasicAnyType<T...>& b) noexcept
{
	if (a.is_empty() && b.is_empty())
	{
		return false;
	}

	try
	{
		return binary_operator(not_equals_operator{}, a, b);
	}
	catch (...)
	{
		return true;
	}
}


#endif // ! BASIC_ANY_TYPE_HPP_
