#include <gtest/gtest.h>
#include <test_utils.hpp>
#include <2knighs.hpp>

using namespace TwoKnights;

TEST(YAxisPathCheck, Case85) {

    auto solution = Solution(3, 2, 11, 7);
    solution.Get();

    std::vector<int> expect{1, 1, -1, 2, 2};
    std::vector<int> test = *solution.getYAxiPath();
    EXPECT_TRUE(areVectorsEqual(expect, test));
}