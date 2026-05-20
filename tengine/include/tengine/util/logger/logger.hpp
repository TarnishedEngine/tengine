/**
 * @brief Common logger utility
 * @author DIY Labs
 */

#pragma once

#include <vector>
#include <memory>
#include <mutex>
#include <tengine/util/logger/i_logsink.hpp>
#include <tengine/util/logger/log_level.hpp>
#include <tengine/util/logger/filter.hpp>

namespace tengine::util::logger{

class Logger{

public:

  // Meyers Singleton
  static Logger& getInstance(){
    static Logger instance;
    return instance;
  }

  void log(tengine::util::logger::LogLevel level, const std::string& sender, const std::string& message);
  void addSink(const std::shared_ptr<tengine::util::logger::ILogSink> sink, const std::shared_ptr<tengine::util::logger::LogFilter> filter);
  void addSink(const std::shared_ptr<tengine::util::logger::ILogSink> sink);
  void clearSinks();

  // Refuse all constructors, force Logger::getInstance()
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(Logger&&) = delete;

private:
  Logger(){
    m_init();
  }
  void m_safeInternalLog(tengine::util::logger::LogLevel level, const std::string& sender, const std::string& message);
  bool m_FilterBySender(std::string sender, std::shared_ptr<tengine::util::logger::LogFilter> filter);
  bool m_filterByLevel(tengine::util::logger::LogLevel level, std::shared_ptr<tengine::util::logger::LogFilter> filter);
  void m_init();

  void m_checkInit();
  bool m_initComplete = false;

  std::shared_ptr<tengine::util::logger::ILogSink> m_internalSink;
  std::vector<std::shared_ptr<tengine::util::logger::ILogSink>> m_logSinks;
  std::vector<std::shared_ptr<tengine::util::logger::LogFilter>> m_logFilters;
  std::mutex m_mutex;

  const std::shared_ptr<tengine::util::logger::LogFilter> m_defaultFilter = std::make_shared<tengine::util::logger::LogFilter>();

};

}