#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <vector>

using namespace llvm;
static LLVMContext Context;
static Module *ModuleOb = new Module("My compiler",Context);

int main(int argc, char *argv[]) {
    static IRBuilder<> Builder = IRBuilder<>(Context);

    // create a function "foo" that returns int result with two int32 named arguments "a" and "b"
    Function *fooFunc;

    std::vector<Type *> PTypes;
    PTypes.push_back(Builder.getInt32Ty());
    PTypes.push_back(Builder.getInt32Ty());

    FunctionType *fooFuncType = FunctionType::get(Builder.getInt32Ty(), PTypes, false);
    fooFunc = Function::Create(fooFuncType, Function::ExternalLinkage, "foo", ModuleOb);

    std::vector<std::string> Params;
    Params.push_back("a");
    Params.push_back("b");
    int index = 0;
    for (auto it = fooFunc->arg_begin(); it != fooFunc->arg_end(); ++it, ++index) {
        it->setName(Params[index]);
    }

    // adding a block to a function "foo"
    BasicBlock *entry = BasicBlock::Create(Context,"entry",fooFunc);
    verifyFunction(*fooFunc);

    // emit a global variable i32 "x"
    ModuleOb->getOrInsertGlobal("x", Builder.getInt32Ty());
    GlobalVariable *gVar = ModuleOb->getNamedGlobal("x");
    gVar->setLinkage(GlobalValue::CommonLinkage);
    gVar->setAlignment(4);

    // emit a return statement to function foo
    Builder.SetInsertPoint(entry);
    Builder.CreateRet(Builder.getInt32(0));
    ModuleOb->dump();


    return 0;
}
