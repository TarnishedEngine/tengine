#include <tengine/util/cfgparse/serializer.hpp>

#include <sstream>

namespace tengine::util{

std::string CFGSerializer::serialize(const CFGNode &node){

  std::ostringstream oss;
  m_serializeNode(node, oss, 0);
  return oss.str();

}

void CFGSerializer::serialize(const CFGNode &node, std::ostream &os){

  m_serializeNode(node, os, 0);

}

void CFGSerializer::m_indent(std::ostream& os, int level){

  for(int i = 0; i < level; i++){
    os << "  ";
  }

}

std::string CFGSerializer::m_formatValue(const std::string &value){

  if(value.find_first_of(" \t\n\"") != std::string::npos){
    return "\"" + value + "\"";
  }

  return value;

}

void CFGSerializer::m_serializeNode(const CFGNode &node, std::ostream &os, int level){

  if(!node.nodeName.empty()){
    m_indent(os, level);
    os << node.nodeName << "{\n";
  }

  int nextLevel = node.nodeName.empty() ? level : level + 1;

  for(const auto& [key, value] : node.values){
    m_indent(os, nextLevel);
    os << key << " = " << m_formatValue(value) << "\n";
  }

  for(const auto& child : node.children){
    m_serializeNode(child, os, nextLevel);
  }

  if(!node.nodeName.empty()){
    m_indent(os, level);
    os << "}\n";
  }

}

}
