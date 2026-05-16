/**
 * @brief
 * @author DIY Labs
 */

#pragma once

#include <vector>
#include <mutex>
#include <memory>
#include <string>

#include <tengine/console/IConsole.hpp>
#include <tengine/console/IConCommand.hpp>
#include <tengine/console/IConOutput.hpp>
#include <tengine/console/ConVar.hpp>

namespace tengine::console{

class Console : IConsole{

public:

  static Console& getInstance(){
    static Console instance;
    return instance;
  }

  Console(const Console&) = delete;
  Console& operator=(const Console&) = delete;
  Console(Console&&) = delete;
  Console& operator=(Console&&) = delete;

  void addOutput(std::shared_ptr<tengine::console::IConOutput> out);
  void addConCommand(std::shared_ptr<tengine::console::IConCommand> cmd);
  tengine::console::ConVarErrorCode addConVar(std::shared_ptr<tengine::console::ConVar> cvar);

  ConVarErrorCode ctx_setConVar(std::string name, std::shared_ptr<ConVar> cvar) override;
  ConVarErrorCode ctx_getConVar(std::string name, std::shared_ptr<ConVar> cvar) override;
  void ctx_print(std::string msg) override;

  void parse(std::string& input);

private:

  Console(){
    m_init();
  }

  bool m_initFinished = false;
  void m_init();

  std::mutex m_mutex;

  std::vector<std::shared_ptr<tengine::console::IConCommand>> m_concommands;
  std::vector<std::shared_ptr<tengine::console::IConOutput>> m_outputs;
  std::vector<std::shared_ptr<tengine::console::ConVar>> m_convars;

  void m_setupDebugCvars();

};

}