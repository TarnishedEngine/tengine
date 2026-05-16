/**
 * @brief Defines a virtual class for a console command
 * @author DIY Labs
 */

#pragma once

#include <vector>
#include <string>
#include <tengine/console/IConsole.hpp>

namespace tengine::console{

class IConCommand{

public:
  virtual ~IConCommand() = default;
  virtual bool execute(std::vector<std::string> args, tengine::console::IConsole& ctx) = 0;
  std::string name;

};

}