// This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

//Generating Precompiled header name based on Macro based on code from
//https://stackoverflow.com/questions/30438911/how-to-get-a-visual-studio-macro-value-into-a-pre-processor-directive
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define MfcPrecompileFile   TOSTRING(MfcPCHFile)//Referencing MFCpch.h file

// add headers that you want to be precompiled here
#include "MFCFramework.h"

#endif //PCH_H
