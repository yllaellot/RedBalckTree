#pragma once

#include <benchmark/benchmark.h>
#include <ctime>
#include <fstream>
#include <set>
#include <string>
#include <filesystem>
#include "RedBlackTree.h"
#include "set_func.h"

namespace bencht
{
    inline void init_rbt (RedBlackTree<int64_t>& rbt, std::ifstream& set_file)
    {
        int elem = 0;
        while (set_file >> elem)
        {
            rbt.insert(elem);
        }
    }

    inline void init_set (std::set<int64_t>& set, std::ifstream& set_file)
    {
        int elem = 0;
        while (set_file >> elem)
        {
            set.insert(elem);
        }
    }

    inline std::string bench_path (std::string bench_name)
    {
        std::filesystem::path bench_path = std::filesystem::current_path().parent_path().parent_path();

        bench_path /= "benchmark/bench_data/" + bench_name + ".dat";

        return bench_path;
    }

    inline int run_rbt (std::ifstream& set_file)
    {
        enum Requests
        {
            KEY = 'k',
            QUERY = 'q'
        };

        RedBlackTree<int> rb_tree;

        char request;

        int key;
        int key1, key2;

        volatile int64_t ans;

        try{
            while(set_file >> request)
            {
                switch(request)
                {
                    
                    case KEY: 
                        if (!(set_file >> key)) throw "Error reading from input stream\n";

                        rb_tree.insert(key);
                        break;

                    case QUERY:
                        if (!(set_file >> key1 >> key2)) throw "Error reading from input stream\n";

                        ans = rb_tree.range_queries(key1, key2);
                        break;

                    default :
                        throw "Error reading from input stream\n";
                }

            }
        }
        catch (const char* error){ std::cerr<< error << "\n"; }

        return 0;
    }
    
    int run_set (std::ifstream& set_file)
    {
        std::set<int> rb_tree;

        char request;

        int key;
        int key1, key2;
        volatile int64_t ans;

        try{
            while(set_file >> request)
            {
                switch(request)
                {
                    case setf::KEY : 
                        if (!(set_file >> key)) throw "Error reading from input stream\n";

                        rb_tree.insert(key);
                                    
                        break;

                    case setf::QUERY :
                        if (!(set_file >> key1 >> key2)) throw "Error reading from input stream\n";

                        ans = setf::range_queries(rb_tree, key1, key2);

                        break;

                    default :
                        throw "Error reading from input stream\n";
                }
            }
        } catch (const char* error){ std::cerr<< error << "\n"; }

        return 0;
    }

    void run_bench_rbt_range_q (benchmark::State& state, std::string bench_name)
    {
        RedBlackTree<int64_t> rbt;

        std::ifstream set_file(bench_path(bench_name));

        int range;

        try
        {
            if (!set_file) throw std::runtime_error("Error reading from file");

            if (!(set_file >> range)) throw std::runtime_error("Error reading from file");

            init_rbt(rbt, set_file);

            while(state.KeepRunning())
            {
                for(int i = -range; i < range + 4; i++)
                {
                    for(int j = -range; j < range + 4; j++)
                    {
                        volatile auto res = rbt.range_queries(i, j);
                    }
                }
            }

        } catch (const std::exception& error) {std::cerr << error.what() << '\n';}
    }

    void run_bench_set_range_q (benchmark::State& state, std::string bench_name)
    {
        std::set<int64_t> set;
        std::ifstream set_file(bench_path(bench_name));

        int range;

        try
        {
            if (!set_file) throw std::runtime_error("Error reading from file");

            if (!(set_file >> range)) throw std::runtime_error("Error reading from file");

            init_set(set, set_file);

            while(state.KeepRunning())
            {
                for(int i = -range; i < range + 4; i++)
                {
                    for(int j = -range; j < range + 4; j++)
                    {
                        volatile auto res = setf::range_queries(set, i, j);
                    }
                }
            }

        } catch (const std::exception& error) {std::cerr << error.what() << '\n';}
    }

    inline void run_bench_set (benchmark::State& state, std::string bench_name)
    {
        std::set<int64_t> set;
        std::ifstream set_file (bench_path(bench_name));

        volatile int res;

        while (state.KeepRunning())
        {
            res = run_set(set_file);
        }
    }

    inline void run_bench_rbt (benchmark::State& state, std::string bench_name)
    {
        std::set<int64_t> set;
        std::ifstream set_file (bench_path(bench_name));

        volatile int res;

        while (state.KeepRunning())
        {
            res = run_rbt(set_file);
        }
    }
}