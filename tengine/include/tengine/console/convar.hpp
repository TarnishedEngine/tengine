/**
 * @brief Defines a type for console variables
 * @author DIY Labs
 */

#pragma once

#include <string>
#include <cstdint>
#include <variant>
#include <optional>

namespace tengine::console{

using ConVarValue = std::variant<std::string, std::int64_t, double, bool>;
using ConVarLimit = std::variant<std::int64_t, double>;

enum ConVarType{

  CONVAR_UNSET,
  CONVAR_STRING,
  CONVAR_INT,
  CONVAR_FLOAT,
  CONVAR_BOOL

};

enum ConVarErrorCode{

  CVAR_ERR_OK,
  CVAR_ERR_INPUT_GREATER_THAN_LIMIT,
  CVAR_ERR_INPUT_LOWER_THAN_LIMIT,
  CVAR_ERR_LIMIT_VALUE_TYPE_MISMATCH,
  CVAR_ERR_NO_NAME,
  CVAR_ERR_NULL_CVAR,
  CVAR_ERR_NOT_FEELING_LIKE_IT

};

/*
union ConVarValue{

  std::string str;
  std::int64_t i;
  double fp;
  bool b;

};

union ConVarLimit{

  std::int64_t intLimit;
  double fpLimit;

};
*/

struct ConVar{

  ConVarValue value;
  std::optional<ConVarLimit> lowerLimit, upperLimit;

  std::string name;
  std::string helpText;

};

}