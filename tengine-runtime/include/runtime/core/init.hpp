/**
 * @brief Functions used to initialize tengine and the tengine runtime
 * @author DIY Labs
 */

#pragma once

#include <runtime/core/RuntimeGlobals.hpp>


namespace truntime{

void runtimeInit(truntime::RuntimeGlobals& global);

void readValuesFromCoreConfig(truntime::RuntimeGlobals& global);

}