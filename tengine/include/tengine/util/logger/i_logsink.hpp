/**
 * @brief Defines an interface that receives log messages
 * @author DIY Labs
 */

#pragma once

#include <string>
#include "tengine/util/logger/log_level.hpp"

namespace tengine::util{

class ILogSink{

public:
  virtual ~ILogSink() = default;

  /**
   *
   * @param level Log level provided by the caller
   * @param sender String identifying the caller
   * @param message Log message provided by the caller
   */
  virtual void receiveLog(tengine::util::LogLevel level, const std::string& sender, const std::string& message) = 0;

};

};