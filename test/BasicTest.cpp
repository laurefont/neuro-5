	#include <gtest/gtest.h>

TEST(MyArbitraryCategoryName, MyArbitraryTestName)
{
	int i = 7;
	int j = 10:
	int result = i * j;

	EXPECT_EQ(70, result);
	EXPECT_TRUE( result == 70);
}
  
  void main(int argc, char* argv[])
  {
 		::testing::InitGoogleTest(&argc, argv);
  		RUN_ALL_TESTS(); 
  
  }
