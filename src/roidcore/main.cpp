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
		w.exec_with<position, velocity>([](entity_dyn_id, position& p, velocity& v) {
			p.p += v.v;
		});
	}

	static void proc_deltaxyplain(world& w)
	{
		w.get<ship>().foreach([](entity_id<ship>, ship& s) {
			s.p.p += s.v.v;
		});
	}

	static void proc_print(world& w)
	{
		w.exec_with<position>([](entity_dyn_id const id, position& p) {
			std::printf("%hhu[%zu]: %f, %f\n", id.type, id.id, p.p.x, p.p.y);
		});
	}

	static inline void test()
	{
		world w;

		for(size_t i = 0; i < 5; ++i)
		{
			ship s;
			s.p.p = glm::vec2(0.1f, 0.1f);
			s.v.v = glm::vec2(0.1f, 0.2f);
			w.get<ship>().emplace(std::move(s));
		}
		
		for(size_t i = 0; i < 5; ++i)
		{
			station s;
			s.p.p = glm::vec2(1.0f*i, 1.0f*i);
			w.get<station>().emplace(std::move(s));
		}

		w.get<ship>().remove(0);
		w.get<ship>().remove(4);
		w.get<station>().remove(2);
		
		for(size_t i = 0; i < 5; ++i)
		{
			ship s;
			s.p.p = glm::vec2(0.1f, 0.1f);
			s.v.v = glm::vec2(0.1f, 0.2f);
			w.get<ship>().emplace(std::move(s));
		}
		
		std::cout << "plain" << std::endl;
		for(size_t i = 0; i < 5; ++i)
		{
			proc_deltaxyplain(w);
		}
		
		proc_print(w);
		
		std::cout << "awesome" << std::endl;
		for(size_t i = 0; i < 5; ++i)
		{
			proc_deltaxy(w);
		}

		proc_print(w);
	}
}

int main()
{
	roidcore::test();

	return EXIT_SUCCESS;
}
