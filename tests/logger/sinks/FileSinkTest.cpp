#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <tengine/util/logger/sinks/FileSink.hpp>

class FileSinkTest : public ::testing::Test{

protected:
  const std::string testFileName = "filesinktest.log";

  void TearDown() override{

    if(std::filesystem::exists(testFileName)) {
      std::filesystem::remove(testFileName);
    }

  }

};

TEST_F(FileSinkTest, WritesLogToFile){

  {
    tengine::util::logger::FileSink sink(testFileName);
    sink.receiveLog(tengine::util::logger::LogLevel::LEVEL_INFO, "GTest Test Sender", "Hello, World!");
  }

  std::ifstream file(testFileName);
  ASSERT_TRUE(file.is_open());          // verify file exists

  std::string line;
  std::getline(file, line);

  EXPECT_NE(line.find("LEVEL_INFO"), std::string::npos);
  EXPECT_NE(line.find("GTest Test Sender"), std::string::npos);
  EXPECT_NE(line.find("Hello, World!"), std::string::npos);

}