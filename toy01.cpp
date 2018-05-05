#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
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

    // adding a block to a function "foo"
    BasicBlock *entry = BasicBlock::Create(Context,"entry",fooFunc);
    Builder.SetInsertPoint(entry);
    verifyFunction(*fooFunc);

    // emit a global variable i32 "x"
    ModuleOb->getOrInsertGlobal("x", Builder.getInt32Ty());
    GlobalVariable *gVar = ModuleOb->getNamedGlobal("x");
    gVar->setLinkage(GlobalValue::CommonLinkage);
    gVar->setAlignment(4);

    ModuleOb->dump();
    return 0;
}
