#include <iostream>
#include <cstdlib>
#include <tengine/util/logger/Logger.hpp>
#include <tengine/util/logger/sinks/FileSink.hpp>

namespace tengine::util::logger{

void Logger::init(){

  if(m_initComplete) return;

  std::lock_guard<std::mutex> lock(m_mutex);
  m_internalSink = std::make_shared<FileSink>("tengine-internal.log");

  // If m_internalSink is null for any reason, give up
  // TODO: Rework with UI message?
  if(!m_internalSink){
    std::cerr << "TENGINE FATAL ERROR: Logger's internal FileSink init failed." << std::endl;
    std::abort();
  }

}

void Logger::log(tengine::util::logger::LogLevel level, const std::string& sender, const std::string& message) {

  m_checkInit();
  m_safeInternalLog(level, sender, message);

  std::lock_guard<std::mutex> lock(m_mutex);

  for(int i = 0; i < m_logSinks.size(); i++){

    auto& sink = m_logSinks[i];
    auto& filter = m_logFilters[i];

    if(!sink){  m_safeInternalLog(tengine::util::logger::LogLevel::LEVEL_ERROR, "Logger", "Null sink at position " + std::to_string(i) + " when attempting to log");  }
    else{

      switch(filter.filterMode){

        case FILTER_NO_FILTER:
          sink->receiveLog(level, sender, message);
          break;

        case FILTER_ALLOW_SENDER:
        case FILTER_DISALLOW_SENDER:
          if(m_FilterBySender(sender, filter)){  sink->receiveLog(level, sender, message); }
          break;

        case FILTER_ALLOW_LOG_LEVEL:
        case FILTER_DISALLOW_LOG_LEVEL:
          if(m_filterByLevel(level, filter)){  sink->receiveLog(level, sender, message); }
          break;

        default:
          sink->receiveLog(level, sender, message);
          break;

      }

    }

  }

}

void Logger::addSink(const std::shared_ptr<tengine::util::logger::ILogSink> sink, const tengine::util::logger::LogFilter filter){

  m_checkInit();

  if(!sink){
    m_safeInternalLog(tengine::util::logger::LogLevel::LEVEL_ERROR, "Logger", "Attempted to add null sink");
  }

  std::lock_guard<std::mutex> lock(m_mutex);
  m_logSinks.push_back(sink);
  m_logFilters.push_back(filter);

}

void Logger::addSink(const std::shared_ptr<tengine::util::logger::ILogSink> sink){

  m_checkInit();

  if(!sink){
    m_safeInternalLog(tengine::util::logger::LogLevel::LEVEL_ERROR, "Logger", "Attempted to add null sink");
  }

  std::lock_guard<std::mutex> lock(m_mutex);
  m_logSinks.push_back(sink);
  m_logFilters.push_back(m_defaultFilter);

}

void Logger::clearSinks(){

  m_checkInit();

  std::lock_guard<std::mutex> lock(m_mutex);
  m_logSinks.clear();

}

void Logger::m_safeInternalLog(tengine::util::logger::LogLevel level, const std::string &sender, const std::string &message){

  if(m_internalSink){
    m_internalSink->receiveLog(level, sender, message);
  }
  else{
    std::cerr << "TENGINE FATAL ERROR: Logger's internal FileSink init is null when attempting to log." << std::endl;
    std::abort();
  }

}

bool Logger::m_FilterBySender(std::string sender, tengine::util::logger::LogFilter filter){

  if(filter.senderList.empty()){
    m_safeInternalLog(LogLevel::LEVEL_WARN, "Logger", "m_FilterBySender received a filter with an empty sender list");
    return true;  // Pass on message through anyway
  }

  bool found = false;
  for(std::string s : filter.senderList){

    if(s == sender) {
      found = true;
      break;
    }

  }

  if(filter.filterMode == FILTER_ALLOW_SENDER){  return found; }
  else if(filter.filterMode == FILTER_DISALLOW_SENDER){  return !found; }

  return true;

}

bool Logger::m_filterByLevel(tengine::util::logger::LogLevel level, tengine::util::logger::LogFilter filter){

  if(filter.levelList.empty()){
    m_safeInternalLog(LogLevel::LEVEL_WARN, "Logger", "m_filterByLevel received a filter with an empty level list");
    return true;  // Pass on message through anyway
  }

  bool found = false;
  for(tengine::util::logger::LogLevel l : filter.levelList){

    if(l == level) {
      found = true;
      break;
    }

  }

  if(filter.filterMode == FILTER_ALLOW_LOG_LEVEL){  return found; }
  else if(filter.filterMode == FILTER_DISALLOW_LOG_LEVEL){  return !found; }

  return true;

}

void Logger::m_checkInit(){

  if(!m_initComplete) init();

}
}
