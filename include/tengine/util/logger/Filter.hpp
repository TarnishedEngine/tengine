/**
 * @brief Defines a set of structs that handle filtering
 * @author DIY Labs
 */

#pragma once

#include <string>
#include <vector>
#include <tengine/util/logger/LogLevel.hpp>

namespace tengine::util::logger{

enum FilterMode{

  FILTER_NO_FILTER,
  FILTER_ALLOW_SENDER,
  FILTER_DISALLOW_SENDER,
  FILTER_ALLOW_LOG_LEVEL,
  FILTER_DISALLOW_LOG_LEVEL

};

struct LogFilter{

  tengine::util::logger::FilterMode filterMode = FILTER_NO_FILTER;
  std::vector<std::string> senderList;
  std::vector<tengine::util::logger::LogLevel> levelList;

};

}