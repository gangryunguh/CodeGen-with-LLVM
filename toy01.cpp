#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

using namespace llvm;
static LLVMContext Context;
static Module *ModuleOb = new Module("My compiler",Context);

int main(int argc, char *argv[]) {
    static IRBuilder<> Builder = IRBuilder<>(Context);

    // create a function "foo" that returns int result
    Function *fooFunc;
    FunctionType *fooFuncType = FunctionType::get(Builder.getInt32Ty(),false);
    fooFunc = Function::Create(fooFuncType, Function::ExternalLinkage, "foo", ModuleOb);


    ModuleOb->dump();
    return 0;
}
