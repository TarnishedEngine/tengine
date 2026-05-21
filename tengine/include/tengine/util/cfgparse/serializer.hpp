/***
 *
 * @author DIY Labs
 */

#pragma once

#include <string>
#include <ostream>

#include <tengine/util/cfgparse/cfg_node.hpp>

namespace tengine::util{

class CFGSerializer{

public:
  static std::string serialize(const CFGNode& node);
  static void serialize(const CFGNode& node, std::ostream& os);

private:
  static void m_serializeNode(const CFGNode& node, std::ostream& os, int level);
  static void m_indent(std::ostream& os, int level);
  static std::string m_formatValue(const std::string& value);

};

}