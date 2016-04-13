#pragma once

#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/struct.hpp>

#include <type_traits>
#include <cstdlib>

#include <roidcore/entities.hpp>

namespace roidcore
{
	namespace detail
	{
		template<typename T, typename N>
		using name_t = boost::fusion::extension::struct_member_name<T, N::value>;

		template<typename T, typename N>
		using type_t = typename boost::fusion::result_of::value_at<T, N>::type;

		template<typename N>
		using next_t = typename boost::mpl::next<N>::type;

		template<typename T>
		using size_t = typename boost::fusion::result_of::size<T>::type;

		template<typename E, typename C, typename N>
		struct has_component
		{
			static const bool value = (
				std::is_same<C, type_t<E, N>>::value ||
				detail::has_component<E, C, next_t<N>>::value
			);
		};

		template<typename E, typename C>
		struct has_component<E, C, size_t<E>>
		{
			static const bool value = false;
		};

		template<typename E, typename C, typename N>
		struct get_first_index
		{
			static const std::size_t value =
				std::is_same<C, type_t<E, N>>::value ?
				N::value :
				get_first_index<E, C, next_t<N>>::value;
		};
		
		template<typename E, typename C>
		struct get_first_index<E, C, size_t<E>>
		{
			static const std::size_t value = size_t<E>::value;
		};
	}

	template<typename E, typename C>
	static constexpr bool has_component()
	{
		return detail::has_component<E, C, boost::mpl::int_<0>>::value;
	}

	template<typename E, typename C>
	struct get_first_index
	{
		static_assert(has_component<E, C>());
		static const std::size_t value = detail::get_first_index<E, C, boost::mpl::int_<0>>::value;
	};

	template<typename E, typename C>
	static inline C& get_first_component_ref(E& e)
	{
		static_assert(has_component<E, C>());
		return boost::fusion::at<
			boost::mpl::int_<
				detail::get_first_index<E, C, boost::mpl::int_<0>>::value
		>>(e);
	}

	template<typename E, typename F, typename... ARGS>
	static inline void exec_with_components(E& e, F f)
	{
		f( get_first_component_ref<E, ARGS>(e)... );
	}
}
