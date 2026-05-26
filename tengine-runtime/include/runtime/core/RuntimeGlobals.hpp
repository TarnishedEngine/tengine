/**
 * @brief Defines structs for global constants and variables
 * @author DIY Labs
 */

#pragma once

#include <string>
#include <vector>

#include <tengine/util/cfgparse/cfg_node.hpp>


namespace truntime{

struct RuntimeGlobalConstants{

  const std::string TR_CORE_CFG_PATH = "tengine-runtime-assets/core.tcfg";

};

struct RuntimeGlobalVariables{

  std::vector<tengine::util::CFGNode> configNodes;

  std::string TR_FILE_ASSOCIATION_CONFIG;

};

}