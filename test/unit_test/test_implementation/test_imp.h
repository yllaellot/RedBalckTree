#pragma once

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
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
    int answer ( std::ifstream& answer_file )
    {
        int answer;
        answer_file >> answer;

        return answer;
    }

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
                case KEY   : 
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
}
