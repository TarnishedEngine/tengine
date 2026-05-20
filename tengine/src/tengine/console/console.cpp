#include <fmt/format.h>

#include <tengine/console/console.hpp>
#include <tengine/util/logger/logger.hpp>
#include <tengine/util/logger/logger_macros.hpp>

#include <tengine/util/logger/logger.hpp>
#include <tengine/util/logger/logger_macros.hpp>

namespace tengine::console{

void Console::addOutput(std::shared_ptr<tengine::console::IConOutput> out) {

  if(!out){
    TENGINE_LOG_ERROR("Console::addOutput", "Passed a null IConOutput, cannot add to output list");
    return;
  }

  m_outputs.push_back(out);

}

void Console::addConCommand(std::shared_ptr<tengine::console::IConCommand> cmd){

  if(!cmd){
    TENGINE_LOG_ERROR("Console::addConCommand", "Passed a null IConCommand, cannot add to command list");
    return;
  }

  m_concommands.push_back(cmd);

}

tengine::console::ConVarErrorCode Console::addConVar(std::shared_ptr<tengine::console::ConVar> cvar){

  // Is cvar null?
  if(!cvar){
    TENGINE_LOG_ERROR("Console::addConVar", "Passed a null ConVar, cannot add to convar list");
    return CVAR_ERR_NULL_CVAR;
  }

  // Does cvar have a name?
  if(cvar->name.empty()){
    TENGINE_LOG_ERROR("Console::addConVar", "ConVar passed has no name set, cannot add to convar list");
    return CVAR_ERR_NO_NAME;
  }

  // Cvar holds an int
  if(std::holds_alternative<int64_t>(cvar->value)){

    int64_t val = std::get<int64_t>(cvar->value);

    // Cvar has a lower limit
    if(cvar->lowerLimit){

      // Cvar's lower limit is not an int
      if(!std::holds_alternative<int64_t>(*cvar->lowerLimit)){
        TENGINE_LOG_ERROR("Console::addConVar", "ConVar passed has mismatch between value and limit's type: value is int64, limit is not");
        return CVAR_ERR_LIMIT_VALUE_TYPE_MISMATCH;
      }

      // Cvar's value is lower than the limit specifies
      if(val < std::get<int64_t>(*cvar->lowerLimit)){
        TENGINE_LOG_ERROR("Console::addConVar", fmt::format("ConVar passed's value {} is lower than lower limit {}", val, std::get<int64_t>(*cvar->lowerLimit)));
        return CVAR_ERR_INPUT_LOWER_THAN_LIMIT;
      }

    }

    // Cvar has an upper limit
    if(cvar->upperLimit){

      // Cvar's upper limit is not an int
      if(!std::holds_alternative<int64_t>(*cvar->upperLimit)){
        TENGINE_LOG_ERROR("Console::addConVar", "ConVar passed has mismatch between value and limit's type: value is int64, limit is not");
        return CVAR_ERR_LIMIT_VALUE_TYPE_MISMATCH;
      }

      // Cvar's value is higher than the limit specifies
      if(val > std::get<int64_t>(*cvar->upperLimit)){
        TENGINE_LOG_ERROR("Console::addConVar", fmt::format("ConVar passed's value {} is higher than upper limit {}", val, std::get<int64_t>(*cvar->upperLimit)));
        return CVAR_ERR_INPUT_GREATER_THAN_LIMIT;
      }

    }

  }

  // Cvar holds a double
  if(std::holds_alternative<double>(cvar->value)){

    double val = std::get<double>(cvar->value);

    // Cvar has a lower limit
    if(cvar->lowerLimit){

      // Cvar's lower limit is not a double
      if(!std::holds_alternative<double>(*cvar->lowerLimit)){
        TENGINE_LOG_ERROR("Console::addConVar", "ConVar passed has mismatch between value and limit's type: value is double, limit is not");
        return CVAR_ERR_LIMIT_VALUE_TYPE_MISMATCH;
      }

      // Cvar's value is lower than the limit specifies
      if(val < std::get<double>(*cvar->lowerLimit)){
        TENGINE_LOG_ERROR("Console::addConVar", fmt::format("ConVar passed's value {} is lower than lower limit {}", val, std::get<double>(*cvar->lowerLimit)));
        return CVAR_ERR_INPUT_LOWER_THAN_LIMIT;
      }

    }

    // Cvar has an upper limit
    if(cvar->upperLimit){

      // Cvar's upper limit is not a double
      if(!std::holds_alternative<double>(*cvar->upperLimit)){
        TENGINE_LOG_ERROR("Console::addConVar", "ConVar passed has mismatch between value and limit's type: value is double, limit is not");
        return CVAR_ERR_LIMIT_VALUE_TYPE_MISMATCH;
      }

      // Cvar's value is higher than the limit specifies
      if(val > std::get<double>(*cvar->upperLimit)){
        TENGINE_LOG_ERROR("Console::addConVar", fmt::format("ConVar passed's value {} is higher than upper limit {}", val, std::get<double>(*cvar->upperLimit)));
        return CVAR_ERR_INPUT_GREATER_THAN_LIMIT;
      }

    }

  }

  m_convars.push_back(cvar);
  return CVAR_ERR_OK;

}

void Console::m_init(){

  m_setupDebugCvars();

  TENGINE_LOG_INFO("Console::m_init()", "Console initalized.");

}

void Console::m_setupDebugCvars(){

  std::shared_ptr<ConVar> debug_int = std::make_shared<ConVar>();
  debug_int->name = "debug_int";
  debug_int->helpText = "A friendly little cvar containing an integer.";
  debug_int->value = 617;

  addConVar(debug_int);

}

}
