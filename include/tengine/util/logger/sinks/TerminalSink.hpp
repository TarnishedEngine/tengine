/**
* @brief Defines an ILogSink that dumps logs to the terminal
 * @author DIY Labs
 */

#pragma once

#include <functional>
#include <tengine/util/logger/ILogSink.hpp>
#include <tengine/util/logger/LogLevel.hpp>
#include <termcolor/termcolor.hpp>

namespace tengine::util::logger{

class [[deprecated("TerminalSink is deprecated, do not use")]] TerminalSink : public ILogSink{

public:
  TerminalSink() = default;
  ~TerminalSink() override = default;

  using color = std::ostream& (*)(std::ostream&);

  void receiveLog(tengine::util::logger::LogLevel level, const std::string &sender, const std::string &message) override;

private:
  void printFormattedMessage(tengine::util::logger::LogLevel level, const std::string& sender, const std::string& message, color color16);
  const char* getLevelString(tengine::util::logger::LogLevel level);

};

}