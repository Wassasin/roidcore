#pragma once

#include <roidcore/entities.hpp>
#include <roidcore/entity_storage.hpp>

#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/mpl/transform.hpp>

namespace roidcore
{
	struct world
	{
		typedef typename boost::mpl::transform<entities_list, entity_storage<boost::mpl::_1>>::type storage_t;
		
		storage_t storage;

		template<bool enable, typename E, typename F, typename... ARGS>
		struct call_if;

		template<typename E, typename F, typename... ARGS>
		struct call_if<true, E, F, ARGS...>
		{
			static inline void exec(entity_storage<E>& es, F f)
			{
				es.foreach([f](entity_id<E> id, E& e) {
					auto f_new = [f, id](ARGS&... args) { f(id.get_dyn_id(), args...); };
					exec_with_components<E, decltype(f_new), ARGS...>(e, f_new);
				});
			}
		};
		
		template<typename E, typename F, typename... ARGS>
		struct call_if<false, E, F, ARGS...>
		{
			static inline void exec(entity_storage<E>&, F)
			{
				// Do nothing
			}
		};

		template<typename E, typename... CS>
		struct has_components;

		template<typename E, typename C, typename... CS>
		struct has_components<E, C, CS...>
		{
			static constexpr bool value = has_component<E, C>() && has_components<E, CS...>::value;
		};
		
		template<typename E, typename C>
		struct has_components<E, C>
		{
			static constexpr bool value = has_component<E, C>();
		};

		template<typename T>
		inline entity_storage<T>& get()
		{
			return boost::fusion::at<get_first_index<entities_list, T>>(storage);
		}
		
		template<typename T>
		inline entity_storage<T>& get() const
		{
			return boost::fusion::at_c<get_first_index<entities_list, T>>(storage);
		}
		
		template<typename... ARGS, typename F>
		inline void exec_with(F f)
		{
			boost::fusion::for_each(storage, [&](auto& st) {
				using entity_t = typename std::remove_reference<decltype(st)>::type::entity_t;
				call_if<has_components<entity_t, ARGS...>::value, entity_t, F, ARGS...>::exec(st, f);
			});
		}
	};
}
