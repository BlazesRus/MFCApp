#ifndef MFCHeader_H
#define MFCHeader_H

//Generating Precompiled header name based on Macro based on code from
//https://stackoverflow.com/questions/30438911/how-to-get-a-visual-studio-macro-value-into-a-pre-processor-directive
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define MfcPrecompileFile   TOSTRING(MfcPCHFile)//Referencing "MFCpch.h" file

#endif