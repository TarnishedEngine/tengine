/***
 * @brief
 * @author DIY Labs
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include <tengine/util/cfgparse/cfg_node.hpp>

namespace tengine::util{

class CFGParser{

public:

  static std::vector<CFGNode> parse(const std::string& input);
  static std::vector<CFGNode> parse(std::istream& input);
  static bool parseRecursive(const std::filesystem::path &dir, std::vector<CFGNode>& nodes, const std::string &ext);

private:
  static void m_skipCommentsAndWS(std::istream& is);
  static std::string m_readValue(std::istream& is);
  static void m_parseScope(std::istream& is, CFGNode& currentNode);

};


}