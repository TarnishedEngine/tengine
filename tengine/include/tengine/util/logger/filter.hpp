/**
 * @brief Defines a set of structs that handle filtering
 * @note NERE!!
 * @author DIY Labs
 */

#pragma once

#include <string>
#include <vector>
#include <tengine/util/logger/log_level.hpp>

namespace tengine::util{

enum FilterMode{

  FILTER_NO_FILTER,
  FILTER_ALLOW_SENDER,
  FILTER_DISALLOW_SENDER,
  FILTER_ALLOW_LOG_LEVEL,
  FILTER_DISALLOW_LOG_LEVEL

};

struct LogFilter{

  tengine::util::FilterMode filterMode = FILTER_NO_FILTER;
  std::vector<std::string> senderList;
  std::vector<tengine::util::LogLevel> levelList;

};

}