#include <gtest/gtest.h>

TEST(Sanity, OnePlusOneEqualsTwo){

  EXPECT_EQ(1 + 1, 2);

}

TEST(Sanity, OnePlusOneNotEqualsThree){

  EXPECT_NE(1 + 1, 3);

}