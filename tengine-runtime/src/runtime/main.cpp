#include <iostream>

#include <runtime/core/init.hpp>
#include <runtime/core/RuntimeGlobals.hpp>

#include "../../../cmake-build-demo/_deps/fmt-src/include/fmt/xchar.h"


truntime::RuntimeGlobals runtimeGlobals;



int main(int argc, char* argv[]){

  truntime::runtimeInit(runtimeGlobals);

}