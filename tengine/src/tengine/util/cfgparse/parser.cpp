#include <sstream>
#include <limits>
#include <fstream>

#include <fmt/format.h>

#include <tengine/util/cfgparse/parser.hpp>
#include <tengine/util/logger/logger_macros.hpp>
#include <tengine/util/filesystem/recur_file_by_ext.hpp>

namespace tengine::util{

std::vector<CFGNode> CFGParser::parse(const std::string &input){

  std::stringstream ss(input);
  CFGNode parentNode;
  m_parseScope(ss, parentNode);
  return parentNode.children;

}

std::vector<CFGNode> CFGParser::parse(std::istream &input){

  CFGNode parentNode;
  m_parseScope(input, parentNode);
  return parentNode.children;

}

bool CFGParser::parseRecursive(const std::filesystem::path& dir, std::vector<CFGNode>& nodes, const std::string& ext){

  TENGINE_LOG_INFO("CFGParser::parseRecursive()", fmt::format("Recursively parsing config files in: {}", dir.string()));

  std::vector<std::filesystem::path> cfgFilePaths;

  switch(tengine::util::recursiveFileByExtension(dir, cfgFilePaths, ext)){

    case ERR_OK:
      break;

    case ERR_PATH_DOES_NOT_EXIST:
      TENGINE_LOG_ERROR("CFGParser::parseRecursive()", fmt::format("Path {} passed does not exist!", dir.string()));
      return false;

    case ERR_PATH_NOT_DIR:
      TENGINE_LOG_ERROR("CFGParser::parseRecursive()", fmt::format("Path {} passed is not a directory!", dir.string()));
      return false;

    default:
      TENGINE_LOG_ERROR("CFGParser::parseRecursive()", "Unhandled case in switch-case");

  }

  for(const auto& entry : cfgFilePaths){

    std::ifstream file(entry);

    if(!file){
      TENGINE_LOG_ERROR("CFGParser::parseRecursive()", fmt::format("Unable to open config file at: {}", entry.string()));
      continue;
    }

    auto n = parse(file);
    nodes.insert(nodes.end(), n.begin(), n.end());
    TENGINE_LOG_DEBUG("CFGParser::parseRecursive()", fmt::format("Parsed tengine config file at: {}", entry.string()));

  }

  return true;

}

void CFGParser::m_skipCommentsAndWS(std::istream &is){

  while(true){

    is >> std::ws;

    if(is.peek() == '/'){

      is.get();

      if(is.peek() == '/'){
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      else{
        is.putback('/');
        break;
      }

    }
    else{
      break;
    }

  }

}

std::string CFGParser::m_readValue(std::istream& is){

  m_skipCommentsAndWS(is);

  if(is.peek() == '"'){

    is.get();
    std::string s;
    std::getline(is, s, '"');
    return s;

  }

  std::string s;
  is >> s;
  return s;

}

void CFGParser::m_parseScope(std::istream& is, CFGNode& currentNode){

  std::string token;

  while(true){

    m_skipCommentsAndWS(is);

    if(is.peek() == '}'){
      is.get();
      break;
    }

    if(!(is >> token)) break;

    if(token.back() == '{'){

      CFGNode child;
      child.nodeName = token.substr(0, token.size() - 1);
      m_parseScope(is, child);
      currentNode.children.push_back(std::move(child));
      continue;

    }

    m_skipCommentsAndWS(is);

    char nextChar = is.peek();

    if(nextChar == '{'){

      is.get();
      CFGNode child;
      child.nodeName = token;
      m_parseScope(is, child);
      currentNode.children.push_back(std::move(child));

    }
    else if(nextChar == '='){

      is.get();
      currentNode.values[token] = m_readValue(is);

    }

  }

}

}