#include <iostream>

#include <runtime/core/init.hpp>
#include <runtime/core/RuntimeGlobals.hpp>


truntime::RuntimeGlobals runtimeGlobals;


int main(int argc, char* argv[]){

  truntime::runtimeInit(runtimeGlobals);

}