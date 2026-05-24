/**
 * @brief Functions used to initialize tengine and the tengine runtime
 * @author DIY Labs
 */

#pragma once


#include <fmt/format.h>

#include <runtime/runtime_build_details.hpp>
#include <tengine/tengine_build_details.hpp>

#include <tengine/util/logger/logger.hpp>
#include <tengine/util/logger/logger_macros.hpp>


namespace runtime{

inline void runtime_init(){

  runtime::printBuildDetails();
  tengine::build_details::printBuildDetails();
  TENGINE_LOG_INFO("runtime_init()", fmt::format("\nTarnishedEngine build details:\n{}", tengine::build_details::getFormattedBuildDetails()));
  TENGINE_LOG_INFO("runtime_init()", fmt::format("\nTarnished Runtime build details:\n{}", runtime::getFormattedBuildDetails()));

}

}