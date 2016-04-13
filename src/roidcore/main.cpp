#include <initializer_list> // force libstdc++ to include its config
#undef _GLIBCXX_HAVE_GETS // correct broken config

#include <vector>
#include <cstdio>

#include <roidcore/world.hpp>

namespace roidcore
{
	static void proc_deltaxy(world& w)
	{
		w.exec_with<position, velocity>([](entity_dyn_id, position& p, velocity& v) {
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

		for(size_t i = 0; i < 2; ++i)
		{
			ship s;
			s.p = glm::vec2(0.0f, 0.0f);
			s.v = glm::vec2(0.1f, 0.2f);
			w.ships.emplace(std::move(s));
		}
		
		for(size_t i = 0; i < 500; ++i)
			proc_deltaxy(w);

		proc_debug(w);
		
		for(size_t i = 0; i < 500; ++i)
			proc_deltaxyplain(w);

		proc_debug(w);
		
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
