/**
 * @brief Functions used to initialize tengine and the tengine runtime
 * @author DIY Labs
 */

#pragma once


#include <fmt/format.h>

#include <fstream>

#include <runtime/runtime_build_details.hpp>
#include <tengine/tengine_build_details.hpp>

#include <tengine/util/logger/logger.hpp>
#include <tengine/util/logger/logger_macros.hpp>

#include <tengine/util/cfgparse/cfg_node.hpp>
#include <tengine/util/cfgparse/parser.hpp>


#include <runtime/core/RuntimeGlobals.hpp>


namespace truntime{

inline void runtimeInit(truntime::RuntimeGlobalVariables& globalVars, truntime::RuntimeGlobalConstants& globalConstants){

  truntime::printBuildDetails();
  tengine::build_details::printBuildDetails();
  TENGINE_LOG_INFO("runtime_init()", fmt::format("\n\nTarnishedEngine build details:\n{}", tengine::build_details::getFormattedBuildDetails()));
  TENGINE_LOG_INFO("runtime_init()", fmt::format("\n\nTarnished Runtime build details:\n{}", truntime::getFormattedBuildDetails()));


  std::ifstream coreConfigFile(globalConstants.TR_CORE_CFG_PATH);

  if(!coreConfigFile){
    TENGINE_LOG_FATAL("runtime_init()", fmt::format("Core config file at {} failed to open.", globalConstants.TR_CORE_CFG_PATH));
    std::abort();
  }

}

}