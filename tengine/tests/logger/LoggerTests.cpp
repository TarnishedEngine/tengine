#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <tengine/util/logger/sinks/file_sink.hpp>
#include <tengine/util/logger/filter.hpp>
#include "tengine/util/logger/logger.hpp"
#include <tengine/tengine_build_details.hpp>

struct CapturedLog{

  tengine::util::LogLevel level;
  std::string sender;
  std::string message;

};

class DummySink : public tengine::util::ILogSink{

public:

  void receiveLog(tengine::util::LogLevel level, const std::string &sender, const std::string &message) override {
    logs.push_back({level, sender, message});
  }

  std::vector<CapturedLog> logs;

private:

};

class LoggerTests : public ::testing::Test{

protected:

  void SetUp() override{

    tengine::build_details::printBuildDetails();
    tengine::util::Logger::getInstance().clearSinks();

  }

  void TearDown() override{
    tengine::util::Logger::getInstance().clearSinks();
  }

};

TEST_F(LoggerTests, LoggerDispatchesToSinks){

  auto& logger = tengine::util::Logger::getInstance();
  auto dummySink = std::make_shared<DummySink>();
  auto allowEverythingThrough = std::make_shared<tengine::util::LogFilter>();
  allowEverythingThrough->filterMode = tengine::util::FILTER_NO_FILTER;

  logger.addSink(dummySink, allowEverythingThrough);

  logger.log(tengine::util::LogLevel::LEVEL_DEBUG, "GTest Test", "Hello, Tarnished!");

  ASSERT_EQ(dummySink->logs.size(), 1);
  ASSERT_EQ(dummySink->logs[0].level, tengine::util::LogLevel::LEVEL_DEBUG);
  ASSERT_EQ(dummySink->logs[0].sender, "GTest Test");
  ASSERT_EQ(dummySink->logs[0].message, "Hello, Tarnished!");

}

TEST_F(LoggerTests, LoggerDispatchesToSinkWithDefaultFilter){

  auto& logger = tengine::util::Logger::getInstance();
  auto dummySink = std::make_shared<DummySink>();

  logger.addSink(dummySink);

  logger.log(tengine::util::LogLevel::LEVEL_DEBUG, "GTest Test", "Hello, Tarnished!");

  ASSERT_EQ(dummySink->logs.size(), 1);
  ASSERT_EQ(dummySink->logs[0].level, tengine::util::LogLevel::LEVEL_DEBUG);
  ASSERT_EQ(dummySink->logs[0].sender, "GTest Test");
  ASSERT_EQ(dummySink->logs[0].message, "Hello, Tarnished!");

}

TEST_F(LoggerTests, MultipleSinksReceiveLogs){

  auto& logger = tengine::util::Logger::getInstance();
  auto dummySinkA = std::make_shared<DummySink>();
  auto dummySinkB = std::make_shared<DummySink>();
  auto allowEverythingThrough = std::make_shared<tengine::util::LogFilter>();
  allowEverythingThrough->filterMode = tengine::util::FILTER_NO_FILTER;


  logger.addSink(dummySinkA, allowEverythingThrough);
  logger.addSink(dummySinkB, allowEverythingThrough);

  logger.log(tengine::util::LogLevel::LEVEL_DEBUG, "GTest Test", "Hello, Tarnished!");

  ASSERT_EQ(dummySinkA->logs.size(), 1);
  ASSERT_EQ(dummySinkA->logs[0].level, tengine::util::LogLevel::LEVEL_DEBUG);
  ASSERT_EQ(dummySinkA->logs[0].sender, "GTest Test");
  ASSERT_EQ(dummySinkA->logs[0].message, "Hello, Tarnished!");

  ASSERT_EQ(dummySinkB->logs.size(), 1);
  ASSERT_EQ(dummySinkB->logs[0].level, tengine::util::LogLevel::LEVEL_DEBUG);
  ASSERT_EQ(dummySinkB->logs[0].sender, "GTest Test");
  ASSERT_EQ(dummySinkB->logs[0].message, "Hello, Tarnished!");

}

TEST_F(LoggerTests, SenderFilter){

  auto& logger = tengine::util::Logger::getInstance();
  auto sink_NoReceiveTest = std::make_shared<DummySink>();
  auto sink_ReceiveTest = std::make_shared<DummySink>();

  auto receiveTest = std::make_shared<tengine::util::LogFilter>();
  receiveTest->filterMode = tengine::util::FILTER_ALLOW_SENDER;
  receiveTest->senderList.push_back("GTest");

  auto noReceiveTest = std::make_shared<tengine::util::LogFilter>();
  noReceiveTest->filterMode = tengine::util::FILTER_DISALLOW_SENDER;
  noReceiveTest->senderList.push_back("GTest");

  logger.addSink(sink_ReceiveTest, receiveTest);
  logger.addSink(sink_NoReceiveTest, noReceiveTest);

  logger.log(tengine::util::LogLevel::LEVEL_DEBUG, "GTest", "Hello, Tarnished!");

  ASSERT_EQ(sink_NoReceiveTest->logs.size(), 0);
  ASSERT_EQ(sink_ReceiveTest->logs.size(), 1);

}

TEST_F(LoggerTests, LevelFilter){

  auto& logger = tengine::util::Logger::getInstance();
  auto sink_NoReceiveTest = std::make_shared<DummySink>();
  auto sink_ReceiveTest = std::make_shared<DummySink>();

  auto receiveTest = std::make_shared<tengine::util::LogFilter>();
  receiveTest->filterMode = tengine::util::FILTER_ALLOW_SENDER;
  receiveTest->senderList.push_back("GTest");

  auto noReceiveTest = std::make_shared<tengine::util::LogFilter>();
  noReceiveTest->filterMode = tengine::util::FILTER_DISALLOW_SENDER;
  noReceiveTest->senderList.push_back("GTest");

  logger.addSink(sink_ReceiveTest, receiveTest);
  logger.addSink(sink_NoReceiveTest, noReceiveTest);

  logger.log(tengine::util::LogLevel::LEVEL_DEBUG, "GTest", "Hello, Tarnished!");

  ASSERT_EQ(sink_NoReceiveTest->logs.size(), 0);
  ASSERT_EQ(sink_ReceiveTest->logs.size(), 1);

}

TEST_F(LoggerTests, HandlesNullSink){

  auto& logger = tengine::util::Logger::getInstance();
  logger.addSink(nullptr);
  logger.log(tengine::util::LogLevel::LEVEL_DEBUG, "GTest", "Hello, Null!");

}

TEST_F(LoggerTests, HandlesNullFilter){

  auto& logger = tengine::util::Logger::getInstance();
  auto sink_ReceiveTest = std::make_shared<DummySink>();
  logger.addSink(sink_ReceiveTest, nullptr);
  logger.log(tengine::util::LogLevel::LEVEL_DEBUG, "GTest", "Hello, Null!");

  ASSERT_EQ(sink_ReceiveTest->logs.size(), 1);
  ASSERT_EQ(sink_ReceiveTest->logs[0].sender, "GTest");
  ASSERT_EQ(sink_ReceiveTest->logs[0].message, "Hello, Null!");

}

TEST_F(LoggerTests, HandlesNullSinkAndFilter){

  auto& logger = tengine::util::Logger::getInstance();
  logger.addSink(nullptr, nullptr);
  logger.log(tengine::util::LogLevel::LEVEL_DEBUG, "GTest", "Hello, Null!");

}
