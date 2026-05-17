#include <iostream>
#include <tengine/tengine_build_details.hpp>
#include <cxxopts/cxxopts.hpp>

#include <tengine/runtime/CmdOpts.hpp>

#include "tengine/util/logger/sinks/TerminalSink.hpp"

cxxopts::Options cliOptions("tengine_runtime", "TarnishedEngine runtime");


int main(int argc, char* argv[]){

  bool nolog;

  tengine::build_details::printBuildDetails();

  std::vector<tengine::runtime::cmdopts::CMDOption> cmdOptions;
  cmdOptions.push_back(tengine::runtime::cmdopts::TR_CLI_OPTION_HELP);
  cmdOptions.push_back(tengine::runtime::cmdopts::TR_CLI_OPTION_NO_LOG);

  tengine::runtime::cmdopts::registerCmds(cliOptions, cmdOptions);

  cxxopts::ParseResult result;

  try{
    result = cliOptions.parse(argc, argv);
  }
  catch(const cxxopts::exceptions::exception& e){
    std::cerr << "cxxopts command line parsing threw an exception: " << e.what() << "\n"
              << "Run with -h to see CLI help";
    return 1;

  }

  if(result.count(tengine::runtime::cmdopts::TR_CLI_OPTION_HELP.longName)){
    std::cout << cliOptions.help() << std::endl;
  }
  nolog = result[tengine::runtime::cmdopts::TR_CLI_OPTION_NO_LOG.longName].as<bool>();

  std::cout << nolog << std::endl;
  return 0;

}