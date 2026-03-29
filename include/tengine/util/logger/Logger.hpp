/**
 * @brief Common logger utility
 * @author DIY Labs
 */

#pragma once

#include <vector>
#include <memory>
#include <tengine/util/logger/ILogSink.hpp>
#include <tengine/util/logger/LogLevel.hpp>

namespace tengine::util::logger{

class Logger{

public:
  static void init();
  static void log(tengine::util::logger::LogLevel level, const std::string& message);
  static void addSink(std::shared_ptr<tengine::util::logger::ILogSink> sink);
  static void clearSinks();

private:
  Logger() = default;
  static Logger& getInstance();

  std::shared_ptr<tengine::util::logger::ILogSink> m_internalSink;
  std::vector<std::shared_ptr<tengine::util::logger::ILogSink>> m_logSinks;

};

}