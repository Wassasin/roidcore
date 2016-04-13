#include <initializer_list> // force libstdc++ to include its config
#undef _GLIBCXX_HAVE_GETS // correct broken config

#include <vector>
#include <cstdio>

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
				es.foreach([f](entity_id<E>, E& e) {
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
	
	static void proc_deltaxy(world& w)
	{
		w.exec_with<position, velocity>([](position& p, velocity& v) {
			p += v;
		});
	}

	static void proc_deltaxyplain(world& w)
	{
		w.ships.foreach([](entity_id<ship>, ship& s) {
			s.p += s.v;
		});
	}

	static void proc_debug(world const& w)
	{
		w.ships.foreach([](entity_id<ship>, ship const& s) {
			std::printf("%f, %f\n", s.p.x, s.p.y);
		});
	}

	static inline void test()
	{
		world w;

		for(size_t i = 0; i < 1024*1024; ++i)
		{
			ship s;
			s.p = glm::vec2(0.0f, 0.0f);
			s.v = glm::vec2(0.1f, 0.2f);
			w.ships.emplace(std::move(s));
		}
		
		for(size_t i = 0; i < 500; ++i)
			proc_deltaxy(w);
		
		for(size_t i = 0; i < 500; ++i)
			proc_deltaxyplain(w);
		
		for(size_t i = 0; i < 500; ++i)
			proc_deltaxy(w);
		
		for(size_t i = 0; i < 500; ++i)
			proc_deltaxyplain(w);
	}
}

int main()
{
	roidcore::test();

	return EXIT_SUCCESS;
}
