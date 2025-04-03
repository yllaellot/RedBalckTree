#pragma once

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "RedBlackTree.h"

enum Requests
{
    KEY = 'k',
    QUERY = 'q'
};

enum PathTypes
{
    ANSWER = 'a',
    TASK = 't'
};

namespace test_rbt
{
    const std::string get_path (const std::string& test_name, PathTypes test_type)
    {
        std::filesystem::path path = std::filesystem::current_path().parent_path();


        switch(test_type)
        {
            case TASK :
                path /= "data/tasks/" + test_name + ".dat";
                break;

            case ANSWER :
                path /= "data/answers/" + test_name + ".ans";
                break;

            default :
                throw "Error incorrect path type\n";
        }

        return path;
    }

    int answer (std::ifstream& answer_file)
    {
        int answer;
        answer_file >> answer;

        return answer;
    }

    inline void init_rbt (RedBlackTree<int64_t>& rbt, const std::string& test_name)
    {
        std::ifstream set_file(get_path(test_name, TASK));

        int64_t elem = 0;
        while (set_file >> elem)
        {
            rbt.insert(elem);
        }
    }

    inline void init_set (std::set<int64_t>& set, std::ifstream& set_file)
    {
        int64_t elem = 0;
        while (set_file >> elem)
        {
            set.insert(elem);
        }
    }

    void run_test (const std::string& test_name)
    {
        RedBlackTree<int> rb_tree;

        char request;

        int key;
        int key1, key2;
        int res;
        int ans;

        std::ifstream task_file(get_path(test_name, TASK));
        std::ifstream answer_file(get_path(test_name, ANSWER));

        while(task_file >> request)
        {
            switch(request)
            {
                case KEY : 
                    if (!(std::cin >> key)) throw "Error reading from input stream\n";

                    rb_tree.insert(key);

                    break;

                case QUERY :
                    if (!(std::cin >> key1 >> key2))  throw "Error reading from input stream\n"; 

                    res = rb_tree.range_queries(key1, key2);
                    ans = answer(answer_file);

                    EXPECT_EQ(res, ans);

                    break;

                default :
                    throw "Error reading from input stream\n"; 
            }
        }
    }

    inline void run_move_test (const std::string& test_name)
    {
        RedBlackTree<int64_t> rbt{};

        init_rbt (rbt, test_name);

        RedBlackTree<int64_t> rbt_lhs = std::move(rbt);

        EXPECT_TRUE(rbt_lhs.size() == rbt.size());

        auto rbt_lhs_it = rbt_lhs.begin();
        std::for_each(rbt.begin(), rbt.end(), [&](auto& node)
        {
            EXPECT_EQ(node, *rbt_lhs_it);
            ++rbt_lhs_it;
        });
    }

    inline void run_move_assign_test (const std::string& test_name)
    {
        RedBlackTree<int64_t> rbt{};

        init_rbt(rbt, test_name);

        RedBlackTree<int64_t> rbt_lhs{};

        rbt_lhs = std::move(rbt);

        EXPECT_TRUE(rbt_lhs.size() == rbt.size());

        auto rbt_lhs_it = rbt_lhs.begin();
        std::for_each(rbt.begin(), rbt.end(), [&](auto& node)
        {
            EXPECT_EQ(node, *rbt_lhs_it);
            ++rbt_lhs_it;
        });
    }

    inline void run_assign_test (const std::string& test_name)
    {
        RedBlackTree<int64_t> rbt{};

        init_rbt(rbt, test_name);

        RedBlackTree<int64_t> rbt_lhs{};

        rbt_lhs = rbt;

        EXPECT_TRUE(rbt_lhs.size() == rbt.size());

        auto rbt_lhs_it = rbt_lhs.begin();
        std::for_each(rbt.begin(), rbt.end(), [&](auto& node)
        {
            EXPECT_EQ(node, *rbt_lhs_it);
            ++rbt_lhs_it;
        });
    }

    inline void run_range_based (const std::string& test_name)
    {
        RedBlackTree<int64_t> rbt{};

        init_rbt(rbt, test_name);

        std::vector<int>buff{};

        std::for_each(rbt.begin(), rbt.end(), [&](auto& node)
        {
            buff.push_back(node);
        });

        auto buff_it = buff.begin();
        std::for_each(rbt.begin(), rbt.end(), [&](auto& node)
        {
            EXPECT_EQ(node, *buff_it);
            ++buff_it;
        });
    }

    inline void run_upper_bound (const std::string& test_name)
    {
        RedBlackTree<int64_t> rbt{};

        init_rbt(rbt, test_name);

        std::for_each(rbt.begin(), rbt.end(), [&](auto& node)
        {
            EXPECT_EQ(std::upper_bound(rbt.begin(), rbt.end(), node, std::less{}), 
                    rbt.upper_bound(node));
        });
    }
}
