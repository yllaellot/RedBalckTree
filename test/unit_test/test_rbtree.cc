#include <gtest/gtest.h>
#include "test_imp.h"

TEST(RedBlackTreeTest, RedBlackTreeRangeElem0)
{
    test_rbt::run_test("test_00");
}

TEST(RedBlackTreeTest, RedBlackTreeRangeElem1)
{
    test_rbt::run_test("test_01");
}

TEST(RedBlackTreeTest, RedBlackTreeRangeElem2)
{
    test_rbt::run_test("test_02");
}

TEST(RedBlackTreeTest, RedBlackTreeRangeElem3)
{
    test_rbt::run_test("test_03");
}

TEST(RedBlackTreeTest, RedBlackTreeRangeElem4)
{
    test_rbt::run_test("test_04");
}

TEST(RedBlackTreeTest, RedBlackTreeRangeElem5)
{
    test_rbt::run_test("test_05");
}

TEST(RedBlackTreeTest, RedBlackTreeRangeElem6)
{
    test_rbt::run_test("test_06");
}

TEST(RedBlackTreeTest, RedBlackTreeRangeElem7)
{
    test_rbt::run_test("test_07");
}

TEST(RedBlackTreeTest, RedBlackTreeRangeElem8)
{
    test_rbt::run_test("test_08");
}
\
TEST(RedBlackTreeTest, RedBlackTreeRangeElem9)
{
    test_rbt::run_test("test_09");
}

TEST(RedBlackTreeTest, RedBlackTreeRangeElem10)
{
    test_rbt::run_test("test_10");
}

TEST(RedBlackTreeTest, RedBlackTreeMoveAssign1)
{
    test_rbt::run_move_assign_test("test_tree_01");
}

TEST(RedBlackTreeTest, RedBlackTreeMove1)
{
    test_rbt::run_move_test("test_tree_01");
}

TEST(RedBlackTreeTest, RedBlackTreeAssign1)
{
    test_rbt::run_assign_test("test_tree_01");
}

TEST(RedBlackTreeTest, RedBlackTreeRangeBased1)
{
    test_rbt::run_range_based("test_tree_01");
}

TEST(RedBlackTreeTest, RedBlackTreeUpperBound1)
{
    test_rbt::run_upper_bound("test_tree_01");
}