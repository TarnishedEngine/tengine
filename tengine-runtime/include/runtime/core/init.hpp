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

inline void runtimeInit(truntime::RuntimeGlobals& global){

  // Print headers
  truntime::printBuildDetails();
  tengine::build_details::printBuildDetails();
  TENGINE_LOG_INFO("runtime_init()", fmt::format("\n\nTarnishedEngine build details:\n{}", tengine::build_details::getFormattedBuildDetails()));
  TENGINE_LOG_INFO("runtime_init()", fmt::format("\n\nTarnished Runtime build details:\n{}", truntime::getFormattedBuildDetails()));


  // Core config
  std::ifstream coreConfigFile(global.consts.TR_CORE_CFG_PATH);

  if(!coreConfigFile){
    TENGINE_LOG_FATAL("runtime_init()", fmt::format("Core config file at {} failed to open.", global.consts.TR_CORE_CFG_PATH));
    std::abort();
  }

  tengine::util::CFGNode coreCFGNode = tengine::util::CFGParser::parse(coreConfigFile).front();

  global.vars.TR_FILE_ASSOCIATION_CONFIG = coreCFGNode.getChild("file_extensions").getString("configFile", ".tcfg");

  for(auto spNode : coreCFGNode.getChildren("search_path")){

    std::string pathstr = spNode.getString("path");
    std::filesystem::path path(pathstr);

    if(!std::filesystem::exists(path)){
      TENGINE_LOG_ERROR("runtimeInit()", fmt::format("Search path {} does not exist!", pathstr));
      continue;
    }
    if(!std::filesystem::is_directory(path)){
      TENGINE_LOG_ERROR("runtimeInit()", fmt::format("Search path {} is not a directory!", pathstr));
      continue;
    }

    TENGINE_LOG_DEBUG("runtimeInit()", fmt::format("Search path {} added", pathstr));

    global.vars.configSearchDir.push_back(pathstr);

  }

}

}