#include "core/my_add.hpp"
#include "core/my_sub.hpp"
#include "core/my_mul.hpp"
#include "core/my_div.hpp"
#include "gtest/gtest.h"
using namespace std;
using namespace cov;
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(example, t_add)
{
    auto result = add(1, 2);
    ASSERT_EQ(result, 3);
}

TEST(example, t_sub)
{
    auto result = sub(1, 2);
    ASSERT_EQ(result, -1);
}
