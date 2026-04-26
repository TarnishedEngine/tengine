/***
 * @brief
 * @author DIY Labs
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <tengine/util/cfgparse/CFGNode.hpp>

namespace tengine::util::cfg{

class CFGParser{

public:

  static std::vector<CFGNode> parse(const std::string& input);

private:
  static void skipCommentsAndWS(std::istream& is);
  static std::string readValue(std::istream& is);
  static void parseScope(std::istream& is, CFGNode& currentNode);

};


}