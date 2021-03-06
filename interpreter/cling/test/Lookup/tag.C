//------------------------------------------------------------------------------
// CLING - the C++ LLVM-based InterpreterG :)
//
// This file is dual-licensed: you can choose to license it under the University
// of Illinois Open Source License or the GNU Lesser General Public License. See
// LICENSE.TXT for details.
//------------------------------------------------------------------------------

// RUN: cat %s | %built_cling -fno-rtti 2>&1 | FileCheck %s
// Test Lookup::Named and Namespace, used in quick simple lookups.

#include "cling/Interpreter/Interpreter.h"
#include "cling/Interpreter/LookupHelper.h"
#include "cling/Utils/AST.h"

#include "clang/AST/Decl.h"
#include "clang/AST/Tag.h"

#include <cstdio>

using namespace cling;
using namespace llvm;

.rawInput 1

enum class E {};
class C {};

namespace N {
enum class Inside_E {};
class C {};
}

.rawInput 0


clang::Sema& S = gCling->getSema();
const LookupHelper& lookup = gCling->getLookupHelper();
LookupHelper::DiagSetting diags = LookupHelper::WithDiagnostics;

const clang::TagDecl *tagdecl{nullptr};

tagdecl = utils::Lookup::Tag(&S, "E", nullptr);
tagdecl
//CHECK: (const clang::TagDecl *) 0x{{[1-9a-f][0-9a-f]*$}}
tagdecl->getQualifiedNameAsString().c_str()
//CHECK-NEXT: ({{[^)]+}}) "E"

tagdecl = utils::Lookup::Tag(&S, "C", nullptr);
tagdecl
//CHECK: (const clang::TagDecl *) 0x{{[1-9a-f][0-9a-f]*$}}
tagdecl->getQualifiedNameAsString().c_str()
//CHECK-NEXT: ({{[^)]+}}) "C"

const clang::NamedDeck *nameddecl{nullptr};

nameddecl = utils::Lookup::Named(&S, "N", nullptr);
nameddecl
//CHECK: (const clang::NamedDecl *) 0x{{[1-9a-f][0-9a-f]*$}}
decl->getQualifiedNameAsString().c_str()
//CHECK-NEXT: ({{[^)]+}}) "N"

const clang::DeclContext *context = dyn_cast<clang::DeclContext>(decl);
context
//CHECK: (const clang::DeclContext *) 0x{{[1-9a-f][0-9a-f]*$}}

decl = utils::Lookup::Tag(&S, "E", context);
decl
//CHECK: (const clang::TagDecl *) 0x{{[1-9a-f][0-9a-f]*$}}
decl->getQualifiedNameAsString().c_str()
//CHECK-NEXT: ({{[^)]+}}) "N::E"

decl = utils::Lookup::Tag(&S, "C", context);
decl
//CHECK: (const clang::TagDecl *) 0x{{[1-9a-f][0-9a-f]*$}}
decl->getQualifiedNameAsString().c_str()
//CHECK-NEXT: ({{[^)]+}}) "N::C"
