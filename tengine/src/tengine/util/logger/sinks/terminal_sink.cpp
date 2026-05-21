/**
* @brief Implements TerminalSink.hpp
 * @author DIY Labs
 */

#include <iostream>
#include <tengine/util/logger/sinks/terminal_sink.hpp>
#include <termcolor/termcolor.hpp>

namespace tengine::util{

void TerminalSink::receiveLog(tengine::util::LogLevel level, const std::string &sender, const std::string &message){

   switch(level){

     case tengine::util::LogLevel::LEVEL_DEBUG:
       printFormattedMessage(level, sender, message, termcolor::blue);
       break;
     case tengine::util::LogLevel::LEVEL_INFO:
       printFormattedMessage(level, sender, message, termcolor::white);
       break;
     case tengine::util::LogLevel::LEVEL_WARN:
       printFormattedMessage(level, sender, message, termcolor::yellow);
       break;
     case tengine::util::LogLevel::LEVEL_ERROR:
       printFormattedMessage(level, sender, message, termcolor::red);
       break;
     case tengine::util::LogLevel::LEVEL_FATAL:
       printFormattedMessage(level, sender, message, termcolor::bright_red);
       break;

   }

}

void TerminalSink::printFormattedMessage(tengine::util::LogLevel level, const std::string& sender, const std::string& message, color color16){

  std::cout << "[ " << color16 << getLevelString(level) << termcolor::reset << " ] [ " << sender << " ] " << message << std::endl;

}

const char* TerminalSink::getLevelString(tengine::util::LogLevel level) {

  switch(level){

    case tengine::util::LogLevel::LEVEL_DEBUG: return "DEBUG";
    case tengine::util::LogLevel::LEVEL_INFO: return "INFO ";
    case tengine::util::LogLevel::LEVEL_WARN: return "WARN ";
    case tengine::util::LogLevel::LEVEL_ERROR: return "ERROR";
    case tengine::util::LogLevel::LEVEL_FATAL: return "FATAL";
    default: return "Unknown log level";

  }

}

}
