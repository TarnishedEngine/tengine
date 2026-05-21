#include <sstream>
#include <limits>
#include <fstream>

#include <tengine/util/cfgparse/parser.hpp>
#include <tengine/util/logger/logger_macros.hpp>
#include <fmt/format.h>

namespace tengine::util{

std::vector<CFGNode> CFGParser::parse(const std::string &input){

  std::stringstream ss(input);
  CFGNode parentNode;
  parseScope(ss, parentNode);
  return parentNode.children;

}

std::vector<CFGNode> CFGParser::parse(std::istream &input){

  CFGNode parentNode;
  parseScope(input, parentNode);
  return parentNode.children;

}

bool CFGParser::parseRecursive(const std::filesystem::path& dir, std::vector<CFGNode>& nodes, const std::string& ext){

  TENGINE_LOG_INFO("CFGParser::parseRecursive()", fmt::format("Recursively parsing config files in: {}", dir.string()));


  if(!std::filesystem::exists(dir)){
    TENGINE_LOG_ERROR("CFGParser::parseRecursive()", fmt::format("Path {} passed does not exist!", dir.string()));
    return false;
  }
  if(!std::filesystem::is_directory(dir)){
    TENGINE_LOG_ERROR("CFGParser::parseRecursive()", fmt::format("Path {} passed is not a directory!", dir.string()));
    return false;
  }

  for(const auto& entry : std::filesystem::recursive_directory_iterator(dir)) {

    if(entry.is_regular_file() && entry.path().extension() == ext){

      TENGINE_LOG_DEBUG("CFGParser::parseRecursive()", fmt::format("Found tengine config file at: {}", entry.path().string()));

      std::ifstream file(entry.path());

      if(!file){
        TENGINE_LOG_ERROR("CFGParser::parseRecursive()", fmt::format("Unable to open config file at: {}", entry.path().string()));
        continue;
      }

      auto n = parse(file);
      nodes.insert(nodes.end(), n.begin(), n.end());

      TENGINE_LOG_DEBUG("CFGParser::parseRecursive()", fmt::format("Parsed tengine config file at: {}", entry.path().string()));

    }

  }

  return true;

}

void CFGParser::skipCommentsAndWS(std::istream &is){

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

std::string CFGParser::readValue(std::istream& is){

  skipCommentsAndWS(is);

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

void CFGParser::parseScope(std::istream& is, CFGNode& currentNode){

  std::string token;

  while(true){

    skipCommentsAndWS(is);

    if(is.peek() == '}'){
      is.get();
      break;
    }

    if(!(is >> token)) break;

    if(token.back() == '{'){

      CFGNode child;
      child.nodeName = token.substr(0, token.size() - 1);
      parseScope(is, child);
      currentNode.children.push_back(std::move(child));
      continue;

    }

    skipCommentsAndWS(is);

    char nextChar = is.peek();

    if(nextChar == '{'){

      is.get();
      CFGNode child;
      child.nodeName = token;
      parseScope(is, child);
      currentNode.children.push_back(std::move(child));

    }
    else if(nextChar == '='){

      is.get();
      currentNode.values[token] = readValue(is);

    }

  }

}

}