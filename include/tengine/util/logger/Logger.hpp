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
#include <tengine/util/logger/Filter.hpp>

namespace tengine::util::logger{

class Logger{

public:

  // Meyers Singleton
  static Logger& getInstance(){
    static Logger instance;
    return instance;
  }

  void init(); // TODO: getInstance().log() calls before init() are allowed and not properly dealt with. TODO: Automatically call init() when instance is requested, and don' re-add internal sink if init() is called multiple times
  void log(tengine::util::logger::LogLevel level, const std::string& sender, const std::string& message);
  void addSink(const std::shared_ptr<tengine::util::logger::ILogSink> sink, const tengine::util::logger::LogFilter filter);
  void addSink(const std::shared_ptr<tengine::util::logger::ILogSink> sink);
  void clearSinks();

  // Refuse all constructors, force Logger::getInstance()
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(Logger&&) = delete;

private:
  Logger() = default;
  void m_safeInternalLog(tengine::util::logger::LogLevel level, const std::string& sender, const std::string& message);
  bool m_FilterBySender(std::string sender, tengine::util::logger::LogFilter filter);
  bool m_filterByLevel(tengine::util::logger::LogLevel level, tengine::util::logger::LogFilter filter);

  void m_checkInit();
  bool m_initComplete = false;

  std::shared_ptr<tengine::util::logger::ILogSink> m_internalSink;
  std::vector<std::shared_ptr<tengine::util::logger::ILogSink>> m_logSinks;
  std::vector<tengine::util::logger::LogFilter> m_logFilters;
  std::mutex m_mutex;

  const tengine::util::logger::LogFilter m_defaultFilter = {FILTER_NO_FILTER};  // let everything through

};

}