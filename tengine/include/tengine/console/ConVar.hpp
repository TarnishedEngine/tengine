/**
 * @brief Defines a type for console variables
 * @author DIY Labs
 */

#pragma once

#include <string>
#include <cstdint>

namespace tengine::console{

enum ConVarType{

  CONVAR_UNSET,
  CONVAR_STRING,
  CONVAR_INT,
  CONVAR_FLOAT,
  CONVAR_BOOL

};

union ConVarValue{

  std::string str;
  std::int64_t int;
  double fp;
  bool b;

};

union ConVarLimit{

  std::int64_t intLimit;
  double fpLimit;

};

struct ConVar{

  ConVarType type = CONVAR_UNSET;

  ConVarValue value;
  ConVarLimit lowerLimit, upperLimit;

  std::string name;
  std::string helpText;

};

}