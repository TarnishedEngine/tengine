/**
 * @brief Defines an enum to indicate importance of log
 * @author DIY Labs
 */

#pragma once

namespace tengine::util{

enum class LogLevel{

  LEVEL_DEBUG,
  LEVEL_INFO,
  LEVEL_WARN,
  LEVEL_ERROR,
  LEVEL_FATAL

};

// TODO: consider adding a level-to-string converter

}