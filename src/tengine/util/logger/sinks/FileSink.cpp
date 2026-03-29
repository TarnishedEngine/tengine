/**
 * @brief Implements FileSink.hpp
 * @author DIY Labs
 */

#include <chrono>
#include <iomanip>
#include <sstream>
#include <tengine/util/logger/sinks/FileSink.hpp>

namespace tengine::util::logger{

FileSink::~FileSink() {

  if(m_logFile.is_open()) {

    m_logFile.flush();
    m_logFile.close();

  }

}

FileSink::FileSink(const std::string &path){
  m_logFile.open(path, std::ios::out | std::ios::trunc);
}

void FileSink::receiveLog(const tengine::util::logger::LogLevel level, const std::string &sender, const std::string &message){

  std::lock_guard<std::mutex> lock(m_fileMutex);

  if(m_logFile.is_open()) {

    m_logFile << "[ " << getTimestamp() << " ] "
              << "[ " << getLevelString(level) << " ] "
              << "[ " << sender << " ] "
              << message << "\n";
    m_logFile.flush();

  }

}

const char* FileSink::getLevelString(tengine::util::logger::LogLevel level) {

  switch(level){

    case tengine::util::logger::LogLevel::INFO: return "INFO";
    case tengine::util::logger::LogLevel::WARN: return "WARN";
    case tengine::util::logger::LogLevel::ERROR: return "ERROR";
    case tengine::util::logger::LogLevel::FATAL: return "FATAL";
    default: return "Unknown log level";

  }

}

std::string FileSink::getTimestamp() {

  auto now = std::chrono::system_clock::now();
  time_t time = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");

  return ss.str();

}

}
