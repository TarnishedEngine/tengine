#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <tengine/util/logger/sinks/file_sink.hpp>
#include <tengine/tengine_build_details.hpp>

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

  tengine::build_details::printBuildDetails();

  {
    tengine::util::logger::FileSink sink(testFileName);
    sink.receiveLog(tengine::util::logger::LogLevel::LEVEL_INFO, "GTest Test Sender", "Hello, World!");
  }

  std::ifstream file(testFileName);
  ASSERT_TRUE(file.is_open());          // verify file exists

  std::string line, lastLine;

  while(std::getline(file, line)){
    if(!line.empty()){
      lastLine = line;
    }
  }

  EXPECT_NE(lastLine.find("INFO"), std::string::npos);
  EXPECT_NE(lastLine.find("GTest Test Sender"), std::string::npos);
  EXPECT_NE(lastLine.find("Hello, World!"), std::string::npos);

}