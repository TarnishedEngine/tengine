/**
 * @brief Defines macros to make logging easier
 * @author DIY Labs
 */

#pragma once

#define TENGINE_LOGLEVEL_DEBUG tengine::util::LogLevel::LevelDebug
#define TENGINE_LOGLEVEL_INFO tengine::util::LogLevel::LEVEL_INFO
#define TENGINE_LOGLEVEL_WARN tengine::util::LogLevel::LEVEL_WARN
#define TENGINE_LOGLEVEL_ERROR tengine::util::LogLevel::LEVEL_ERROR
#define TENGINE_LOGLEVEL_FATAL tengine::util::LogLevel::LEVEL_FATAL

#define TENGINE_LOG_DEBUG(sender, msg) tengine::util::Logger::getInstance().log(tengine::util::LogLevel::LEVEL_DEBUG, sender, msg)
#define TENGINE_LOG_INFO(sender, msg) tengine::util::Logger::getInstance().log(tengine::util::LogLevel::LEVEL_INFO, sender, msg)
#define TENGINE_LOG_WARN(sender, msg) tengine::util::Logger::getInstance().log(tengine::util::LogLevel::LEVEL_WARN, sender, msg)
#define TENGINE_LOG_ERROR(sender, msg) tengine::util::Logger::getInstance().log(tengine::util::LogLevel::LEVEL_ERROR, sender, msg)
#define TENGINE_LOG_FATAL(sender, msg) tengine::util::Logger::getInstance().log(tengine::util::LogLevel::LEVEL_FATAL, sender, msg)

#define TENGINE_LOG(level, sender, msg) tengine::util::Logger::getInstance().log(level, sender, msg)

#define TENGINE_GET_LOGGER tengine::util::Logger::getInstance()

