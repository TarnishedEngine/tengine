/**
 * @brief Defines an enum to indicate importance of log
 * @author DIY Labs
 */

#pragma once

namespace tengine::util::logger{

enum class LogLevel{

  DEBUG,
  INFO,
  WARN,
  ERROR,
  FATAL

};

}