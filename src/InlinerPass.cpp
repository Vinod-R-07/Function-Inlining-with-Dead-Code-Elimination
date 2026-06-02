//=============================================================================
// FILE:
//    HelloWorld.cpp
//
// DESCRIPTION:
//    Visits all functions in a module, prints their names and the number of
//    arguments via stderr. Strictly speaking, this is an analysis pass (i.e.
//    the functions are not modified). However, in order to keep things simple
//    there's no 'print' method here (every analysis pass should implement it).
//
// USAGE:
//    New PM
//      opt -load-pass-plugin=libHelloWorld.dylib -passes="hello-world" `\`
//        -disable-output <input-llvm-file>
//
//
// License: MIT
//=============================================================================

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/IR/Instructions.h"
#include <vector>
#include "llvm/Transforms/Utils/Local.h"

using namespace llvm;

//-----------------------------------------------------------------------------
// HelloWorld implementation
//-----------------------------------------------------------------------------
// No need to expose the internals of the pass to the outside world - keep
// everything in an anonymous namespace.
namespace {

// This method implements what the pass does
void visitor(Function &F) {

    bool isRecursive = false;

    for (auto &BB : F) {
        for (auto &I : BB) {
            if (auto *CB = dyn_cast<CallBase>(&I)) {
                if (CB->getCalledFunction() == &F) {
                    isRecursive = true;
                }
            }
        }
    }

    int instructionCount = 0;

    for (auto &BB : F) {
        for (auto &I : BB) {
            instructionCount++;
        }
    }

    bool isDead = true;

    for (auto *User : F.users()) {
        if (isa<CallInst>(User)) {
            isDead = false;
            break;
        }
    }

    if (F.getName() == "main")
        isDead = false;

    errs() << "Function: " << F.getName() << "\n";
    errs() << "Arguments: " << F.arg_size() << "\n";
    errs() << "Instructions: " << instructionCount << "\n";
	int inlineCost = instructionCount;

	errs() << "Inlining Cost: "
       		<< inlineCost
       		<< "\n";
	
    errs() << "Recursive: "
           << (isRecursive ? "YES" : "NO")
           << "\n";

    errs() << "Dead Function: "
           << (isDead ? "YES" : "NO")
           << "\n";

    if (isRecursive)
        errs() << "Decision: SKIP\n\n";
    else if (instructionCount < 10)
        errs() << "Decision: INLINE\n\n";
    else
        errs() << "Decision: SKIP\n\n";
}
// New PM implementation
struct HelloWorld : PassInfoMixin<HelloWorld> {

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {

  std::vector<CallBase*> InlineCandidates;

  for (Function &F : M) {

    if (F.isDeclaration())
      continue;

    visitor(F);

    for (auto &BB : F) {
      for (auto &I : BB) {

        if (auto *CB = dyn_cast<CallBase>(&I)) {

          Function *Callee = CB->getCalledFunction();

          if (!Callee)
            continue;

          errs() << "CALL SITE: "
                 << F.getName()
                 << " -> "
                 << Callee->getName()
                 << "\n";

          if (!Callee->isDeclaration() &&
              Callee != &F) {

            int calleeCost = 0;

            for (auto &CBB : *Callee)
              for (auto &CI : CBB)
                calleeCost++;

            if (calleeCost < 10) {

              errs() << "INLINE CANDIDATE: "
                     << Callee->getName()
                     << "\n";

              InlineCandidates.push_back(CB);
            }
          }
        }
      }
    }
  }

  errs() << "\n=== PERFORMING INLINING ===\n";

  for (auto *CB : InlineCandidates) {

    if (!CB)
      continue;

    InlineFunctionInfo IFI;

    auto Result = InlineFunction(*CB, IFI);

    if (Result.isSuccess()) {
      errs() << "INLINE SUCCESS\n";
    } else {
      errs() << "INLINE FAILED\n";
    }
  }

std::vector<Function*> DeadFunctions;

for (Function &F : M) {

  if (F.isDeclaration())
    continue;

  if (F.getName() == "main")
    continue;

  if (F.use_empty()) {
    DeadFunctions.push_back(&F);
  }
}

errs() << "\n=== REMOVING DEAD FUNCTIONS ===\n";

for (Function *F : DeadFunctions) {

  errs() << "REMOVING: "
         << F->getName()
         << "\n";

  F->eraseFromParent();
}

errs() << "\n=== REMOVING UNREACHABLE BLOCKS ===\n";

for (Function &F : M) {

  if (F.isDeclaration())
    continue;

  bool Changed = removeUnreachableBlocks(F);

  if (Changed) {
    errs() << "CLEANED CFG: "
           << F.getName()
           << "\n";
  }
}

  return PreservedAnalyses::none();
}

  static bool isRequired() { return true; }
};
} // namespace

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getHelloWorldPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "HelloWorld", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
   			ArrayRef<PassBuilder::PipelineElement>) {
			  if (Name == "hello-world"){
			    MPM.addPass(HelloWorld());
			    return true;
  				}
  				return false;
				});
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize HelloWorld when added to the pass pipeline on the
// command line, i.e. via '-passes=hello-world'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getHelloWorldPluginInfo();
}
