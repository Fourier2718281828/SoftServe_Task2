#ifndef CUSTOM_TYPE_TRAITS_HPP_
#define CUSTOM_TYPE_TRAITS_HPP_
#include <type_traits>
#include <concepts>
#include <optional>
#include "Concepts.hpp"

namespace TypeTraits
{
	template<typename T>
	concept AlmostFundamental = !std::same_as<T, void>           &&
							    !std::same_as<T, std::nullptr_t> &&
							     std::is_fundamental_v<T>		  ;

	template<typename WantedType, typename... Types>
	constexpr std::size_t index_of_type() noexcept
	{
		return impl_index_of_type<0u, WantedType, Types...>();
	}

	template<std::size_t Index, typename WantedType, typename Head, typename... Tail>
	constexpr std::size_t impl_index_of_type() noexcept
	{
		if constexpr (std::same_as<WantedType, Head>)
		{
			return Index;
		}
		else if constexpr (sizeof...(Tail) > 0)
		{
			return impl_index_of_type<Index + 1, WantedType, Tail...>();
		}
		else
		{
			return static_cast<std::size_t>(-1);
		}
	}

	template<typename Head, typename...>
	using head_t = Head;

	template<std::size_t Index, typename Head, typename... Tail>
	struct TypeAtIndex
	{
		using Type = TypeAtIndex<Index - 1, Tail...>::Type;
	};

	template<typename Head, typename... Tail>
	struct TypeAtIndex<0u, Head, Tail...>
	{
		using Type = Head;
	};

	template<std::size_t Index, typename... TypeList>
	using TypeAtIndex_t = TypeAtIndex<Index, TypeList...>::Type;

	template<typename WantedType>
	constexpr bool is_in_list() noexcept
	{
		return false;
	}

	template<typename WantedType, typename Head, typename... Tail>
	constexpr bool is_in_list() noexcept
	{
		if constexpr (std::same_as<WantedType, Head>)
		{
			return true;
		}
		else
		{
			return is_in_list<WantedType, Tail...>();
		}
	}

	template<typename Callable, typename... Args>
	using ResultType = decltype(std::invoke(std::declval<Callable>(), std::declval<Args>()...));

	template<typename Callable, typename HeadResultType, typename... TailResultTypes>
	constexpr bool AllResultTypesEqual = 
		(std::same_as<ResultType<Callable, HeadResultType>, ResultType<Callable, TailResultTypes>> && ...);
}

#endif // ! CUSTOM_TYPE_TRAITS_HPP_
