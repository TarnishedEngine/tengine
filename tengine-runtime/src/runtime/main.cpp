#include <iostream>

#include <runtime/core/init.hpp>
#include <runtime/core/RuntimeGlobals.hpp>


truntime::RuntimeGlobalVariables runtimeGlobalVariables;
truntime::RuntimeGlobalConstants runtimeGlobalConstants;


int main(int argc, char* argv[]){

  truntime::runtimeInit(runtimeGlobalVariables, runtimeGlobalConstants);

}