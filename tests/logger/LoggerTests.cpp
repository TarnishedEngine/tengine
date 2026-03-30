#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <tengine/util/logger/sinks/FileSink.hpp>

#include "tengine/util/logger/Logger.hpp"

struct CapturedLog{

  tengine::util::logger::LogLevel level;
  std::string sender;
  std::string message;

};

class DummySink : public tengine::util::logger::ILogSink{

public:

  void receiveLog(tengine::util::logger::LogLevel level, const std::string &sender, const std::string &message) override {
    logs.push_back({level, sender, message});
  }

  std::vector<CapturedLog> logs;

private:

};

class LoggerTests : public ::testing::Test{

protected:

  void SetUp() override{
    tengine::util::logger::Logger::getInstance().clearSinks();
    tengine::util::logger::Logger::getInstance().init();
  }

  void TearDown() override{
    tengine::util::logger::Logger::getInstance().clearSinks();
  }

};

TEST_F(LoggerTests, LoggerDispatchesToSinks){

  auto& logger = tengine::util::logger::Logger::getInstance();
  auto dummySink = std::make_shared<DummySink>();

  logger.addSink(dummySink);

  logger.log(tengine::util::logger::LogLevel::LevelDebug, "GTest Test", "Hello, Tarnished!");

  ASSERT_EQ(dummySink->logs.size(), 1);
  ASSERT_EQ(dummySink->logs[0].level, tengine::util::logger::LogLevel::LevelDebug);
  ASSERT_EQ(dummySink->logs[0].sender, "GTest Test");
  ASSERT_EQ(dummySink->logs[0].message, "Hello, Tarnished!");

}

TEST_F(LoggerTests, MultipleSinksReceiveLogs){

  auto& logger = tengine::util::logger::Logger::getInstance();
  auto dummySinkA = std::make_shared<DummySink>();
  auto dummySinkB = std::make_shared<DummySink>();

  logger.addSink(dummySinkA);
  logger.addSink(dummySinkB);

  logger.log(tengine::util::logger::LogLevel::LevelDebug, "GTest Test", "Hello, Tarnished!");

  ASSERT_EQ(dummySinkA->logs.size(), 1);
  ASSERT_EQ(dummySinkA->logs[0].level, tengine::util::logger::LogLevel::LevelDebug);
  ASSERT_EQ(dummySinkA->logs[0].sender, "GTest Test");
  ASSERT_EQ(dummySinkA->logs[0].message, "Hello, Tarnished!");

  ASSERT_EQ(dummySinkB->logs.size(), 1);
  ASSERT_EQ(dummySinkB->logs[0].level, tengine::util::logger::LogLevel::LevelDebug);
  ASSERT_EQ(dummySinkB->logs[0].sender, "GTest Test");
  ASSERT_EQ(dummySinkB->logs[0].message, "Hello, Tarnished!");

}


