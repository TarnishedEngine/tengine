#include <tengine/util/cfgparse/Parser.hpp>

#include <sstream>
#include <limits>

namespace tengine::util::cfg{

std::vector<CFGNode> CFGParser::parse(const std::string &input){

  std::stringstream ss(input);
  CFGNode parentNode;
  parseScope(ss, parentNode);
  return parentNode.children;

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