#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <tengine/util/logger/sinks/FileSink.hpp>
#include <tengine/util/logger/Filter.hpp>
#include "tengine/util/logger/Logger.hpp"
#include <tengine/tengine_build_details.hpp>

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

    tengine::build_details::printBuildDetails();
    tengine::util::logger::Logger::getInstance().clearSinks();

  }

  void TearDown() override{
    tengine::util::logger::Logger::getInstance().clearSinks();
  }

};

TEST_F(LoggerTests, LoggerDispatchesToSinks){

  auto& logger = tengine::util::logger::Logger::getInstance();
  auto dummySink = std::make_shared<DummySink>();
  auto allowEverythingThrough = std::make_shared<tengine::util::logger::LogFilter>();
  allowEverythingThrough->filterMode = tengine::util::logger::FILTER_NO_FILTER;

  logger.addSink(dummySink, allowEverythingThrough);

  logger.log(tengine::util::logger::LogLevel::LEVEL_DEBUG, "GTest Test", "Hello, Tarnished!");

  ASSERT_EQ(dummySink->logs.size(), 1);
  ASSERT_EQ(dummySink->logs[0].level, tengine::util::logger::LogLevel::LEVEL_DEBUG);
  ASSERT_EQ(dummySink->logs[0].sender, "GTest Test");
  ASSERT_EQ(dummySink->logs[0].message, "Hello, Tarnished!");

}

TEST_F(LoggerTests, LoggerDispatchesToSinkWithDefaultFilter){

  auto& logger = tengine::util::logger::Logger::getInstance();
  auto dummySink = std::make_shared<DummySink>();

  logger.addSink(dummySink);

  logger.log(tengine::util::logger::LogLevel::LEVEL_DEBUG, "GTest Test", "Hello, Tarnished!");

  ASSERT_EQ(dummySink->logs.size(), 1);
  ASSERT_EQ(dummySink->logs[0].level, tengine::util::logger::LogLevel::LEVEL_DEBUG);
  ASSERT_EQ(dummySink->logs[0].sender, "GTest Test");
  ASSERT_EQ(dummySink->logs[0].message, "Hello, Tarnished!");

}

TEST_F(LoggerTests, MultipleSinksReceiveLogs){

  auto& logger = tengine::util::logger::Logger::getInstance();
  auto dummySinkA = std::make_shared<DummySink>();
  auto dummySinkB = std::make_shared<DummySink>();
  auto allowEverythingThrough = std::make_shared<tengine::util::logger::LogFilter>();
  allowEverythingThrough->filterMode = tengine::util::logger::FILTER_NO_FILTER;


  logger.addSink(dummySinkA, allowEverythingThrough);
  logger.addSink(dummySinkB, allowEverythingThrough);

  logger.log(tengine::util::logger::LogLevel::LEVEL_DEBUG, "GTest Test", "Hello, Tarnished!");

  ASSERT_EQ(dummySinkA->logs.size(), 1);
  ASSERT_EQ(dummySinkA->logs[0].level, tengine::util::logger::LogLevel::LEVEL_DEBUG);
  ASSERT_EQ(dummySinkA->logs[0].sender, "GTest Test");
  ASSERT_EQ(dummySinkA->logs[0].message, "Hello, Tarnished!");

  ASSERT_EQ(dummySinkB->logs.size(), 1);
  ASSERT_EQ(dummySinkB->logs[0].level, tengine::util::logger::LogLevel::LEVEL_DEBUG);
  ASSERT_EQ(dummySinkB->logs[0].sender, "GTest Test");
  ASSERT_EQ(dummySinkB->logs[0].message, "Hello, Tarnished!");

}

TEST_F(LoggerTests, SenderFilter){

  auto& logger = tengine::util::logger::Logger::getInstance();
  auto sink_NoReceiveTest = std::make_shared<DummySink>();
  auto sink_ReceiveTest = std::make_shared<DummySink>();

  auto receiveTest = std::make_shared<tengine::util::logger::LogFilter>();
  receiveTest->filterMode = tengine::util::logger::FILTER_ALLOW_SENDER;
  receiveTest->senderList.push_back("GTest");

  auto noReceiveTest = std::make_shared<tengine::util::logger::LogFilter>();
  noReceiveTest->filterMode = tengine::util::logger::FILTER_DISALLOW_SENDER;
  noReceiveTest->senderList.push_back("GTest");

  logger.addSink(sink_ReceiveTest, receiveTest);
  logger.addSink(sink_NoReceiveTest, noReceiveTest);

  logger.log(tengine::util::logger::LogLevel::LEVEL_DEBUG, "GTest", "Hello, Tarnished!");

  ASSERT_EQ(sink_NoReceiveTest->logs.size(), 0);
  ASSERT_EQ(sink_ReceiveTest->logs.size(), 1);

}

TEST_F(LoggerTests, LevelFilter){

  auto& logger = tengine::util::logger::Logger::getInstance();
  auto sink_NoReceiveTest = std::make_shared<DummySink>();
  auto sink_ReceiveTest = std::make_shared<DummySink>();

  auto receiveTest = std::make_shared<tengine::util::logger::LogFilter>();
  receiveTest->filterMode = tengine::util::logger::FILTER_ALLOW_SENDER;
  receiveTest->senderList.push_back("GTest");

  auto noReceiveTest = std::make_shared<tengine::util::logger::LogFilter>();
  noReceiveTest->filterMode = tengine::util::logger::FILTER_DISALLOW_SENDER;
  noReceiveTest->senderList.push_back("GTest");

  logger.addSink(sink_ReceiveTest, receiveTest);
  logger.addSink(sink_NoReceiveTest, noReceiveTest);

  logger.log(tengine::util::logger::LogLevel::LEVEL_DEBUG, "GTest", "Hello, Tarnished!");

  ASSERT_EQ(sink_NoReceiveTest->logs.size(), 0);
  ASSERT_EQ(sink_ReceiveTest->logs.size(), 1);

}


