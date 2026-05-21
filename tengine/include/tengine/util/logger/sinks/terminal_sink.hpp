/**
* @brief Defines an ILogSink that dumps logs to the terminal
 * @author DIY Labs
 */

#pragma once

#include <functional>
#include <tengine/util/logger/i_logsink.hpp>
#include <tengine/util/logger/log_level.hpp>
#include <termcolor/termcolor.hpp>

namespace tengine::util{

class [[deprecated("TerminalSink is deprecated, do not use")]] TerminalSink : public ILogSink{

public:
  TerminalSink() = default;
  ~TerminalSink() override = default;

  using color = std::ostream& (*)(std::ostream&);

  void receiveLog(tengine::util::LogLevel level, const std::string &sender, const std::string &message) override;

private:
  void printFormattedMessage(tengine::util::LogLevel level, const std::string& sender, const std::string& message, color color16);
  const char* getLevelString(tengine::util::LogLevel level);

};

}