#include <initializer_list> // force libstdc++ to include its config
#undef _GLIBCXX_HAVE_GETS // correct broken config

#include <benchmark/benchmark.h>

#include <roidcore/world.hpp>

static constexpr size_t number = 1024*5;
static constexpr size_t iterations = 100;

static roidcore::world init_world()
{
	using namespace roidcore;
	world w;

	w.get<ship>().reserve(number);
	for(size_t i = 0; i < number; ++i)
	{
		roidcore::ship s;
		s.p = glm::vec2(0.0f, 0.0f);
		s.v = glm::vec2(0.1f, 0.2f);
		w.get<ship>().emplace(std::move(s));
	}

	return w;
}

static void bench_init(benchmark::State &state)
{
	using namespace roidcore;
	while(state.KeepRunning())
	{
		roidcore::world w(init_world());
	}
}
BENCHMARK(bench_init);

static void bench_plain(benchmark::State &state)
{
	using namespace roidcore;
	while(state.KeepRunning())
	{
		roidcore::world w(init_world());

		for(size_t i = 0; i < iterations; ++i)
			w.get<ship>().foreach([](entity_id<ship>, ship& s) {
				s.p += s.v;
			});
	}
}
BENCHMARK(bench_plain);

static void bench_awesome(benchmark::State &state)
{
	using namespace roidcore;
	while(state.KeepRunning())
	{
		roidcore::world w(init_world());

		for(size_t i = 0; i < iterations; ++i)
			w.exec_with<position, velocity>([](entity_dyn_id, position& p, velocity& v) {
				p += v;
			});
	}
}
BENCHMARK(bench_awesome);

BENCHMARK_MAIN();
