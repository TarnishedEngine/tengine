/**
 * @brief A set of command line options for the tengine runtime
 * @author DIY Labs
 */

#include <string>
#include <memory>
#include <vector>
#include <cxxopts/cxxopts.hpp>

#pragma once

namespace tengine::runtime::cmdopts{

struct CMDOption{

  std::string longName;
  std::string shortName;
  std::string description;

  std::shared_ptr<cxxopts::Value> value;

};

inline const CMDOption TR_CLI_OPTION_HELP = {"help", "h", "Prints help text for the runtime's CLI", cxxopts::value<bool>()->default_value("false")};
inline const CMDOption TR_CLI_OPTION_NO_LOG = {"no-log", "n", "Disables printing engine logs to the standard output", cxxopts::value<bool>()->default_value("true")->implicit_value("false")};


inline void registerCmds(cxxopts::Options& options, const std::vector<CMDOption>& cmdOptions){

  for(const CMDOption& option : cmdOptions){

    options.add_options()
    (option.longName + "," + option.shortName, option.description, option.value);

  }

}

}