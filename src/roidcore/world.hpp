#pragma once

#include <roidcore/entities.hpp>
#include <roidcore/entity_storage.hpp>

namespace roidcore
{
	struct world
	{
		entity_storage<ship> ships;
		entity_storage<station> stations;

		template<bool enable, typename E, typename F, typename... ARGS>
		struct call_if;

		template<typename E, typename F, typename... ARGS>
		struct call_if<true, E, F, ARGS...>
		{
			static inline void exec(entity_storage<E>& es, F f)
			{
				es.foreach([f](entity_id<E> id, E& e) {
//					auto f_new = [f, id](ARGS... args) { f(id.get_dyn_id(), args...); };
//					exec_with_components<E, decltype(f_new), ARGS...>(e, f_new);
					exec_with_components<E, F, ARGS...>(e, f);
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

		template<typename... ARGS, typename F>
		inline void exec_with(F f)
		{
			call_if<has_components<ship, ARGS...>::value, ship, F, ARGS...>::exec(ships, f);
			call_if<has_components<station, ARGS...>::value, station, F, ARGS...>::exec(stations, f);
		}
	};
}
