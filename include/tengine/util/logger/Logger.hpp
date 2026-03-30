/**
 * @brief Common logger utility
 * @author DIY Labs
 */

#pragma once

#include <vector>
#include <memory>
#include <mutex>
#include <tengine/util/logger/ILogSink.hpp>
#include <tengine/util/logger/LogLevel.hpp>

namespace tengine::util::logger{

class Logger{

public:

  // Meyers Singleton
  static Logger& getInstance(){
    static Logger instance;
    return instance;
  }

  void init();
  void log(tengine::util::logger::LogLevel level, const std::string& sender, const std::string& message);
  void addSink(std::shared_ptr<tengine::util::logger::ILogSink> sink);
  void clearSinks();

  // Refuse all constructors, force Logger::getInstance()
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(Logger&&) = delete;

private:
  Logger() = default;
  void safeInternalLog(tengine::util::logger::LogLevel level, const std::string& sender, const std::string& message);

  std::shared_ptr<tengine::util::logger::ILogSink> m_internalSink;
  std::vector<std::shared_ptr<tengine::util::logger::ILogSink>> m_logSinks;
  std::mutex m_mutex;

};

}