/**
 * @brief Defines an ILogSink that dumps logs to a file
 * @author DIY Labs
 */

#pragma once

#include <fstream>
#include <mutex>
#include <string>
#include <tengine/util/logger/i_logsink.hpp>

namespace tengine::util{

class FileSink : public ILogSink{

public:
  explicit FileSink(const std::string& path);
  ~FileSink() override;
  void receiveLog(const tengine::util::LogLevel level, const std::string &sender, const std::string &message) override;

private:
  std::ofstream m_logFile;
  std::mutex m_fileMutex;
  const char* getLevelString(tengine::util::LogLevel level);
  std::string getTimestamp();

};

}
