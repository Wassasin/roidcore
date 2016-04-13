#include <initializer_list> // force libstdc++ to include its config
#undef _GLIBCXX_HAVE_GETS // correct broken config

#include <vector>
#include <cstdio>
#include <iostream>

#include <roidcore/world.hpp>

namespace roidcore
{
	static void proc_deltaxy(world& w)
	{
		w.exec_with<position, velocity>([](position& p, velocity& v) {
			p.p += v.v;
			std::printf("%f, %f +(%f, %f)\n", p.p.x, p.p.y, v.v.x, v.v.y);
		});
	}

	static void proc_deltaxyplain(world& w)
	{
		w.ships.foreach([](entity_id<ship>, ship& s) {
			s.p.p += s.v.v;
			std::printf("%f, %f +(%f, %f)\n", s.p.p.x, s.p.p.y, s.v.v.x, s.v.v.y);
		});
	}

	static inline void test()
	{
		world w;

		for(size_t i = 0; i < 1; ++i)
		{
			ship s;
			s.p.p = glm::vec2(0.1f, 0.1f);
			s.v.v = glm::vec2(0.1f, 0.2f);
			w.ships.emplace(std::move(s));
		}
		
		std::cout << "plain" << std::endl;
		for(size_t i = 0; i < 5; ++i)
			proc_deltaxyplain(w);
		
		std::cout << "awesome" << std::endl;
		for(size_t i = 0; i < 5; ++i)
			proc_deltaxy(w);
	}
}

int main()
{
	roidcore::test();

	return EXIT_SUCCESS;
}
