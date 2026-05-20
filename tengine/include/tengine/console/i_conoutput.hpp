/**
 * @brief
 * @author DIY Labs
 */

#pragma once

#include <string>

namespace tengine::console{

class IConOutput{

public:
  virtual ~IConOutput() = default;
  virtual void receiveOutput(std::string out);

};

}