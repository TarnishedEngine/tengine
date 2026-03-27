#include <gtest/gtest.h>
#include <fstream>

TEST(Sanity, ReadFileFromData){

  std::ifstream f("data/sanity/does_this_file_exist.txt");
  EXPECT_TRUE(f.is_open());

}