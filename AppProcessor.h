// ***********************************************************************
// Code Created by James Michael Armstrong (https://github.com/BlazesRus)
// Latest Code Release at https://github.com/BlazesRus/MFCApp under MIT licease
// (MainProject this is submodule to at https://github.com/BlazesRus/BlazesRusSharedCode)
// ***********************************************************************
#pragma once

#include "MFCApp.h"
#include "MFCView.h"

#include "../OtherFunctions/MFCMacrosV3.h"
#include "../OtherFunctions/MFCBaseTwoMacros.h"

#include "AppSettings.h"

class AppProcessor : public MFCApp<MFCView, AppSettings>
{
    MFC_RuntimeExtPart01Base02(AppProcessor, MFCApp, MFCView, AppSettings)
    //Any message map messages here
    MFC_RuntimeExtPart02()
    MFC_RuntimeExtClassName(AppProcessor)
};

MFC_RuntimeImplimentation(AppProcessor)
MFC_RuntimeClassImplimentation(AppProcessor)

extern AppProcessor theApp;