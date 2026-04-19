/**
 * @brief Defines a common struct for config file parsing
 * @author DIY Labs
*/

#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <optional>
#include <fmt/format.h>

#include <tengine/util/logger/Logger.hpp>
#include <tengine/util/logger/LoggerMacros.hpp>

namespace tengine::util::cfg{

struct CFGNode{

  std::vector<CFGNode> children;
  std::map<std::string, std::string> values;

  /**
   * @param key Key whose value to search for in values
   * @return Value as string if found, nullopt if not found
   */
  std::optional<std::string> getStringValue(const std::string& key){

    auto it = values.find(key);
    if(it == values.end()) return std::nullopt;
    return it->second;

  }

  std::int64_t getInteger(const std::string& key, int64_t fallback = 0){

    auto val = getStringValue(key);
    if(!val) return fallback;

    try{
      return std::stoll(*val);
    }
    catch(const std::exception e){
      TENGINE_LOG_ERROR("CFGNode::getInt()", fmt::format("Caught exception {} when trying to parse key {}'s value {} as int64 ", key, *val, e.what()));
    }

    return fallback;

  }

  long double getFloat(const std::string& key, long double fallback = 0.0f){

    auto val = getStringValue(key);
    if(!val) return fallback;

    try{
      return std::stold(*val);
    }
    catch(const std::exception e){
      TENGINE_LOG_ERROR("CFGNode::getFloat()", fmt::format("Caught exception {} when trying to parse key {}'s value {} as long double ", key, *val, e.what()));
    }

    return fallback;

  }

  bool getBoolean(const std::string& key, bool fallback = false){

    auto val = getStringValue(key);
    if(!val) return fallback;

    if(*val == "true" || *val == "1") return true;
    if(*val == "false" || *val == "0") return false;

    TENGINE_LOG_WARN("CFGNode::getBoolean()", fmt::format("Attempted to convert key {}'s value {} to boolean, but {} does not match any aliases for booleans.", key, *val));

    return fallback;

  }

};

}