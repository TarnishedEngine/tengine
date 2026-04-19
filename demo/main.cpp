#include <iostream>

#include <tengine/tengine_build_details.hpp>
#include <tengine/util/logger/Logger.hpp>
#include <tengine/util/logger/sinks/TerminalSink.hpp>
#include <tengine/util/logger/sinks/FileSink.hpp>
#include "tengine/util/logger/LoggerMacros.hpp"
#include <tengine/util/cfgparse/CFGNode.hpp>

auto terminalSink = std::make_shared<tengine::util::logger::TerminalSink>();
auto fileSink = std::make_shared<tengine::util::logger::FileSink>("demo-log.log");

int main(){

    tengine::build_details::printBuildDetails();

    tengine::util::logger::LogFilter allowEverythingThrough;

    TENGINE_GET_LOGGER.addSink(terminalSink, allowEverythingThrough);
    TENGINE_GET_LOGGER.addSink(fileSink, allowEverythingThrough);
    TENGINE_LOG_DEBUG("main()", "Debug Log!");
    TENGINE_LOG_INFO("main()", "Info Log!");
    TENGINE_LOG_WARN("main()", "Warn Log!");
    TENGINE_LOG_ERROR("main()", "Error Log!");
    TENGINE_LOG_FATAL("main()", "Fatal Log!");

    return 0;

}
