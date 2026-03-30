/**
 * @brief Defines macros to make logging easier
 * @author DIY Labs
 */

#pragma once

#define TENGINE_LOGLEVEL_DEBUG tengine::util::logger::LogLevel::DEBUG
#define TENGINE_LOGLEVEL_INFO tengine::util::logger::LogLevel::INFO
#define TENGINE_LOGLEVEL_WARN tengine::util::logger::LogLevel::WARN
#define TENGINE_LOGLEVEL_ERROR tengine::util::logger::LogLevel::ERROR
#define TENGINE_LOGLEVEL_FATAL tengine::util::logger::LogLevel::FATAL

#define TENGINE_LOG_DEBUG(sender, msg) tengine::util::logger::Logger::getInstance().log(tengine::util::logger::LogLevel::DEBUG, sender, msg)
#define TENGINE_LOG_INFO(sender, msg) tengine::util::logger::Logger::getInstance().log(tengine::util::logger::LogLevel::INFO, sender, msg)
#define TENGINE_LOG_WARN(sender, msg) tengine::util::logger::Logger::getInstance().log(tengine::util::logger::LogLevel::WARN, sender, msg)
#define TENGINE_LOG_ERROR(sender, msg) tengine::util::logger::Logger::getInstance().log(tengine::util::logger::LogLevel::ERROR, sender, msg)
#define TENGINE_LOG_FATAL(sender, msg) tengine::util::logger::Logger::getInstance().log(tengine::util::logger::LogLevel::FATAL, sender, msg)

#define TENGINE_LOG(level, sender, msg) tengine::util::logger::Logger::getInstance().log(level, sender, msg)

#define TENGINE_GET_LOGGER tengine::util::logger::Logger::getInstance()

