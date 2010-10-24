#ifndef EXTERNCOMPILATIONENVIRONMENT_H
#define EXTERNCOMPILATIONENVIRONMENT_H

#include "CompilationEnvironment.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma need_compilation_environment
#endif

namespace Metil {

CompilationEnvironment &compilation_environment();

} // namespace Metil

#endif // EXTERNCOMPILATIONENVIRONMENT_H
