#include <gtest/gtest.h>

TEST(MyArbitraryCategoryName, MyArbitraryTestName)
{
    int i = 7;
    int j = 10;
    int result = i * j;

    EXPECT_EQ(70, result);
    EXPECT_TRUE( result == 70);
}
  
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
