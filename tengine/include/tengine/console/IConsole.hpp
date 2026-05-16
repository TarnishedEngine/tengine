/**
 * @brief
 * @author DIY Labs
 */

#pragma once

#include <string>
#include <memory>

#include <tengine/console/ConVar.hpp>

namespace tengine::console{

class IConsole{

public:
  virtual ConVarErrorCode ctx_setConVar(std::string name, std::shared_ptr<ConVar> cvar) = 0;
  virtual ConVarErrorCode ctx_getConVar(std::string name, std::shared_ptr<ConVar> cvar) = 0;
  virtual void ctx_print(std::string msg) = 0;

};

}