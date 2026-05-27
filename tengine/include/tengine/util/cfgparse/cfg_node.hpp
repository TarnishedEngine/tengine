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

#include <tengine/util/logger/logger.hpp>
#include <tengine/util/logger/logger_macros.hpp>

namespace tengine::util{

struct CFGNode{

  std::string nodeName;
  std::vector<CFGNode> children;
  std::map<std::string, std::string> values;
  int nodes;

  /**
   * @param key Key whose value to search for in values
   * @return Value as string if found, nullopt if not found
   */
  std::optional<std::string> getStringValue(const std::string& key){

    auto it = values.find(key);
    if(it == values.end()) return std::nullopt;
    return it->second;

  }

  std::string getString(const std::string& key, std::string fallback = std::string()){

    auto val = getStringValue(key);
    if(!val) return fallback;
    return std::string(*val);

  }

  /***
   * @param key Key whose value to convert to an integer
   * @param fallback Fallback value in case key does not exist
   */
  std::int64_t getInteger(const std::string& key, int64_t fallback = 0){

    auto val = getStringValue(key);
    if(!val) return fallback;

    try{
      return std::stoll(*val);
    }
    catch(const std::exception& e){
      TENGINE_LOG_ERROR("CFGNode::getInt()", fmt::format("Caught exception {} when trying to parse key {}'s value {} as int64 ", e.what(), key, *val));
    }

    return fallback;

  }

  /***
   * @param key Key whose value to convert to a floating-point
   * @param fallback Fallback value in case key does not exist
   */
  long double getFloat(const std::string& key, long double fallback = 0.0l){

    auto val = getStringValue(key);
    if(!val) return fallback;

    try{
      return std::stold(*val);
    }
    catch(const std::exception& e){
      TENGINE_LOG_ERROR("CFGNode::getFloat()", fmt::format("Caught exception {} when trying to parse key {}'s value {} as long double ", e.what(), key, *val));
    }

    return fallback;

  }

  /***
 * @param key Key whose value to convert to a boolean
 * @param fallback Fallback value in case key does not exist
 */
  bool getBoolean(const std::string& key, bool fallback = false){

    auto val = getStringValue(key);
    if(!val) return fallback;

    if(*val == "true" || *val == "1") return true;
    if(*val == "false" || *val == "0") return false;

    TENGINE_LOG_WARN("CFGNode::getBoolean()", fmt::format("Attempted to convert key {}'s value {} to boolean, but {} does not match any aliases for booleans.", key, *val, *val));

    return fallback;

  }

  std::vector<CFGNode> getChildren(const std::string& key){

    std::vector<CFGNode> nodes;

    for(const auto& child : children){
      if(child.nodeName == key) nodes.push_back(child);
    }

    return nodes;

  }

  CFGNode getChild(const std::string& key){
    return getChildren(key).front();
  }

};

}