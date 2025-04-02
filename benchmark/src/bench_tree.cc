#include <benchmark/benchmark.h>
#include "../include/bench_tree_imp.h"

static void BM_Set_1(benchmark::State& state)
{
    bencht::run_bench_set(state, "bench13");
}
BENCHMARK(BM_Set_1)->Unit(benchmark::kMicrosecond);

static void BM_RBT_1(benchmark::State& state)
{
    bencht::run_bench_rbt(state, "bench13");
}
BENCHMARK(BM_RBT_1)->Unit(benchmark::kMicrosecond);

static void BM_Set_2(benchmark::State& state)
{
    bencht::run_bench_set(state, "bench11");
}
BENCHMARK(BM_Set_2)->Unit(benchmark::kMillisecond);

static void BM_RBT_2(benchmark::State& state)
{
    bencht::run_bench_rbt(state, "bench11");
}
BENCHMARK(BM_RBT_2)->Unit(benchmark::kMicrosecond);

static void BM_Set_3(benchmark::State& state)
{
    bencht::run_bench_set(state, "bench9");
}
BENCHMARK(BM_Set_3)->Unit(benchmark::kMillisecond);

static void BM_RBT_3(benchmark::State& state)
{
    bencht::run_bench_rbt(state, "bench9");
}
BENCHMARK(BM_RBT_3)->Unit(benchmark::kMicrosecond);

static void BM_RBT_range_q_1(benchmark::State& state)
{
    bencht::run_bench_rbt_range_q(state, "bench5");
}

BENCHMARK(BM_RBT_range_q_1)->Unit(benchmark::kMillisecond);

static void BM_Set_range_q_1(benchmark::State& state)
{
    bencht::run_bench_set_range_q(state, "bench5");
}

BENCHMARK(BM_Set_range_q_1)->Unit(benchmark::kMillisecond);

static void BM_RBT_range_q_2(benchmark::State& state)
{
    bencht::run_bench_rbt_range_q(state, "bench4");
}

BENCHMARK(BM_RBT_range_q_2)->Unit(benchmark::kMillisecond);

static void BM_Set_range_q_2(benchmark::State& state)
{
    bencht::run_bench_set_range_q(state, "bench4");
}

BENCHMARK(BM_Set_range_q_2)->Unit(benchmark::kMillisecond);

static void BM_RBT_range_q_3(benchmark::State& state)
{
    bencht::run_bench_rbt_range_q(state, "bench6");
}

BENCHMARK(BM_RBT_range_q_3)->Unit(benchmark::kMillisecond);

static void BM_Set_range_q_3(benchmark::State& state)
{
    bencht::run_bench_set_range_q(state, "bench6");
}
BENCHMARK(BM_Set_range_q_3)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();