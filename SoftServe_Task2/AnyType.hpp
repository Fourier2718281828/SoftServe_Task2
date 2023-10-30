#ifndef ANY_TYPE_HPP_
#define ANY_TYPE_HPP_
#include "CustomTypeTraits.hpp"

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
concept AcceptableType = TypeTraits::AlmostFundamental<U>  &&
						 TypeTraits::is_in_list<U, T...>()  ;


template<TypeTraits::AlmostFundamental... T>
class AnyType
{
public:

	template<AcceptableType<T...> U>
	constexpr /* implicit */ AnyType(const U some_value) noexcept :
		storage_{},
		current_type_identifier_ { get_type_identifier<U>()}
	{
		auto& actual_value_ref = get_value_reference<U>();
		actual_value_ref = some_value;
	}


	/*template<TypeTraits::AlmostFundamental... U>
	constexpr AnyType& operator= (const AnyType<U...>& other) noexcept
	{
		if (current_type_identifier_ == other.current_type_identifier_)
		{
			storage_ = other.storage_;
			current_type_identifier_ = other.current_type_identifier_;
		}
		else
		{
			throw 1;
		}

		return *this;
	}*/

	template<AcceptableType<T...> U>
	constexpr AnyType& operator= (const U some_value) noexcept
	{
		current_type_identifier_ = get_type_identifier<U>();
		auto& actual_value_ref = get_value_reference<U>();
		actual_value_ref = some_value;
		
		return *this;
	}

	template<AcceptableType<T...> U>
	constexpr U to()
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

	constexpr std::size_t current_type_identifier() const noexcept
	{
		return current_type_identifier_;
	}

private:

	template<AcceptableType<T...> U>
	constexpr std::size_t get_type_identifier()
	{
		return TypeTraits::index_of_type<U, T...>();
	}

	template<AcceptableType<T...> U>
	constexpr auto& get_value_reference()
	{
		static constexpr std::size_t type_index = TypeTraits::index_of_type<U, T...>();
		return get_value_by_index<type_index>(storage_);
	}

private:

	AnyTypeStorage<T...> storage_;

	std::size_t current_type_identifier_;
};

#endif // ! ANY_TYPE_HPP_
