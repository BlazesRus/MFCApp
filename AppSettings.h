// ***********************************************************************
// Code Created by James Michael Armstrong (https://github.com/BlazesRus)
// Latest Code Release at https://github.com/BlazesRus/MFCApp under MIT licease
// (MainProject this is submodule to at https://github.com/BlazesRus/BlazesRusSharedCode)
// IniDataV2 variant with specific settings only stored and searched
// with addition of mapped elements stored inside containers if BlazesRusAppSetting_EnableListFocusedAppSettings or BlazesRusAppSetting_EnableMapFocusedAppSettings enabled
// ***********************************************************************
/* Preprocessor settings for file:
- BlazesRusAppSetting_EnableListFocusedAppSettings = Dynamically stores other non-hard defined elements for App with data inside VariableLists
- BlazesRusAppSetting_EnableMapFocusedAppSettings =  Dynamically stores other non-hard defined elements inside maps (Current variant of code unfinished,Old variant of this code caused errors of LNK2005 from static elements)
- BlazesRusAppSetting_UseIniElementV3Alternative = Use alternative element map for BlazesRusAppSetting_EnableMapFocusedAppSettings elements(none of code implemented yet)
- BlazesMFCAppIni_EnableFloat = Adds storage of float Elements
- BlazesMFCAppIni_EnableAltNum = Adds storage of MediumDec Elements
- BlazesMFCAppIni_EnableVoid = Adds storage of void Elements
- BlazesMFCAppIni_StoreAllSettingsAsString = Only include string settings for dynamic settings(Not Implemented)
- BlazesRusAppSetting_RetainIniOrder
- MFCApp_UseOldIniDataFormatForSettings
- MFCApp_UseIniTesterSettings = Adds hard coded Test Element for testing App settings(for testing AppSettings functionality)
(MFCApp_UseIniTesterSettings blocks of code can be replaced with hard-coded Variables inside derived/inherited classes from AppSettings)
*/
#pragma once
#ifndef AppSettings_IncludeGuard
#define AppSettings_IncludeGuard

#ifndef DLL_API
#ifdef UsingBlazesSharedCodeDLL
#define DLL_API __declspec(dllimport)
#elif defined(BLAZESSharedCode_LIBRARY)
#define DLL_API __declspec(dllexport)
#else
#define DLL_API
#endif
#endif

#include <string>

#include "..\VariableLists\StringVectorList.h"
#include "..\OtherFunctions\VariableConversionFunctions.h"

#ifdef BlazesMFCAppIni_EnableAltNum
   #include "..\AltNum\MediumDec.hpp"
#endif

#ifdef BlazesRusAppSetting_EnableListFocusedAppSettings
//#include "..\VariableLists\VariableList.h"//Already included inside VariableTypeLists and StringVectorList
#include "..\VariableLists\VariableTypeLists.h"
#include "..\VariableLists\StringVectorList.h"

#endif
#if defined(BlazesRusAppSetting_EnableListFocusedAppSettings) || defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)
#if defined(BlazesRusAppSetting_RetainIniOrder)
#include "..\Databases\CustomOrderedDictionary.h"
#else
#include "..\Databases\CustomDictionary.h"
#endif
#endif

#include "..\OtherFunctions\FileOps.hpp"

#if defined(BlazesRusAppSetting_EnableListFocusedAppSettings) || defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)
#ifdef BlazesRusAppSetting_UseIniElementV3Alternative
#else
class DLL_API IniElementV3
{
public:
    //0 = String Value Stored, 1 = Bool, 2 = Int, 3 = MediumDec(if BlazesMFCAppIni_EnableAltNum enabled), 4 = float(if BlazesMFCAppIni_EnableFloat enabled), 5 = Void(No Parameters), 6=AltDec
    //-1 = Not Found(if searching values)
    __int8 IniTypeStored;
    //If -1, then IniIndex not set yet
    __int8 IniIndex;
    IniElementV3(__int8 typeStored, __int8 index)
    {
        IniTypeStored = typeStored; IniIndex = index;
    }
    IniElementV3(__int8 typeStored)
    {
        IniTypeStored = typeStored; IniIndex = -1;
    }
    IniElementV3()//Defaults to void type if no values set
    {
        IniTypeStored = 5; IniIndex = -1;
    }
};
#endif
#endif

/* MFCApp_UseIniTesterSettings blocks of code can be replaced with hard-coded Variables inside derived/inherited classes from AppSettings */

/// <summary>
/// Class named AppSettings for settings Registry like data for app(without storing data inside registry).
/// </summary>
class DLL_API AppSettings
{
public:
    std::string IniFilePath="";
#if defined(BlazesRusAppSetting_EnableListFocusedAppSettings) || (defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)&&!defined(BlazesRusAppSetting_UseIniElementV3Alternative))
    const IniElementV3 NewBoolVal = 1;
    const IniElementV3 NewIntVal = 2;
    const IniElementV3 NewMediumDecVal = 3;
#ifdef BlazesMFCAppIni_EnableFloat
    const IniElementV3 NewFloatVal = 4;
#endif
    const IniElementV3 NewVoidVal = 5;
    const IniElementV3 BlankStringVal = 0;
#endif
#ifdef BlazesRusAppSetting_EnableListFocusedAppSettings
    /// <summary>
    /// The IniSettings with Int Values
    /// </summary>
    IntegerList IntSettings;

#ifdef BlazesMFCAppIni_EnableFloat
   /// <summary>
    /// The IniSettings with Float Values
    /// </summary>
    VariableList<float> FloatSettings = {};
#endif

    /// <summary>
    /// The bool settings
    /// </summary>
    BoolList BoolSettings = {};

#ifdef BlazesMFCAppIni_EnableAltNum
    /// <summary>
    /// The IniSettings with MediumDec Values
    /// </summary>
    VariableList<MediumDec> MediumDecSettings = {};
#endif

    StringVectorList StringSettings = {};

#elif BlazesRusAppSetting_EnableMapFocusedAppSettings
/*  //LNK2005 error causes by these static definitions when used in MFC Applications

    /// <summary>
    /// The int declaration
    /// </summary>
    const static std::string IntDeclaration;
#ifdef BlazesMFCAppIni_EnableAltNum
    /// <summary>
    /// The medium decimal declaration
    /// </summary>
    const static std::string MediumDecDeclaration;
#endif
    /// <summary>
    /// The bool declaration
    /// </summary>
    const static std::string BoolDeclaration;
    /// <summary>
    /// The Void declaration(No Parameter Value)
    /// </summary>
    const static std::string VoidDeclaration;
#ifdef BlazesMFCAppIni_EnableFloat
    /// <summary>
    /// The float declaration
    /// </summary>
    const static std::string FloatDeclaration;
#endif

//Below Declarations inside header file
//const std::string AppSettings::BoolDeclaration = "#Bool";
//const std::string AppSettings::IntDeclaration = "#Int";
//const std::string AppSettings::VoidDeclaration = "#Void";
//#ifdef BlazesMFCAppIni_EnableAltNum
//const std::string AppSettings::MediumDecDeclaration = "#MediumDec";
//#endif
//#ifdef BlazesMFCAppIni_EnableFloat
//const std::string AppSettings::FloatDeclaration = "#Float";
*/

    /// <summary>
    /// The IniSettings with Int Values
    /// </summary>
    CustomDictionary<std::string, int> IntSettings = {};

#ifdef BlazesMFCAppIni_EnableFloat
   /// <summary>
    /// The IniSettings with Float Values
    /// </summary>
    CustomDictionary<std::string, float> FloatSettings = {};
#endif

    /// <summary>
    /// The bool settings
    /// </summary>
    CustomDictionary<std::string, bool> BoolSettings = {};

#ifdef BlazesMFCAppIni_EnableAltNum
    /// <summary>
    /// The IniSettings with MediumDec Values
    /// </summary>
    CustomDictionary<std::string, MediumDec> MediumDecSettings = {};
#endif

    CustomDictionary<std::string, MediumDec> StringSettings = {};
#endif
#if defined(BlazesRusAppSetting_EnableListFocusedAppSettings) || defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)
    /// <summary>
    /// IniSettings with string values and key linkage to IniSettings
    /// </summary>
#ifdef BlazesRusAppSetting_UseIniElementV3Alternative
#else
#if defined(BlazesRusAppSetting_RetainIniOrder)
    CustomOrderedDictionary<std::string, IniElementV3> self = {};
#else
    CustomDictionary<std::string, IniElementV3> self = {};
#endif
#endif

    /// <summary>
    /// Checks if element exists.
    /// </summary>
    /// <param name="Value">The value.</param>
    /// <returns>bool.</returns>
    bool CheckIfElementExists(std::string Value)
    {
        return self.find(Value) != self.end();
    }
    
#ifndef BlazesRusAppSetting_UseIniElementV3Alternative
    /// <summary>
    /// Checks if element exists.
    /// </summary>
    /// <param name="Value">The value.</param>
    /// <returns>bool.</returns>
    IniElementV3 ReturnIndexIfElementExists(std::string Value)
    {
//#if defined(BlazesRusAppSetting_RetainIniOrder)
//        iterator::CustomOrderedDictionary<std::string, IniElementV3> elementInfo;
//#else
//        //iterator::CustomDictionary<std::string, IniElementV3> elementInfo;
//#endif
        auto elementInfo = self.find(Value);
        if(self.find(Value) == self.end())
            return IniElementV3();
        else
            return elementInfo->second;
    }
#endif
    
    /// <summary>
    /// Returns number of dynamically stored INI elements contained within.
    /// </summary>
    /// <returns>size_t.</returns>
    size_t Size()
    {
        return self.size();
    }
    
    void clear()
    {
        IntSettings.clear();
        BoolSettings.clear();
#ifdef BlazesMFCAppIni_EnableFloat
        FloatSettings.clear();
#endif
#ifdef BlazesMFCAppIni_EnableAltDec
        MediumDecSettings.clear();
#endif
        StringSettings.clear();
        self.clear();
    }
#endif

    void SetToDefaultSettings()
    {
#ifdef MFCApp_UseIniTesterSettings
        AppSetting01 = true;
#endif
#ifdef MFCApp_StoreDynamicAppSettings
        clear();
#endif
    }

    /// <summary>
    /// Initializes a new instance of the <see cref="AppSettings" /> class.
    /// </summary>
    AppSettings()
    {
#ifdef MFCApp_UseIniTesterSettings
        AppSetting01 = true;
#endif
#if defined(BlazesRusAppSetting_EnableListFocusedAppSettings)
        IntSettings = IntegerList{};
        BoolSettings = BoolList{};
#ifdef BlazesMFCAppIni_EnableFloat

#endif
#ifdef BlazesMFCAppIni_EnableAltNum

#endif
        StringSettings = StringVectorList{};
#elif defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)
        IntSettings = CustomDictionary<std::string, int>({});
        BoolSettings = CustomDictionary<std::string, bool>({});
#ifdef BlazesMFCAppIni_EnableFloat
        FloatSettings = CustomDictionary<std::string, float>({});
#endif
#ifdef BlazesMFCAppIni_EnableAltNum
        MediumDecSettings = CustomDictionary<std::string, MediumDec>({});
#endif
        StringSettings = CustomDictionary<std::string, std::string>({});
#endif
#if defined(BlazesRusAppSetting_EnableListFocusedAppSettings) || defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)
#if defined(BlazesRusAppSetting_RetainIniOrder)
    self = CustomOrderedDictionary<std::string, IniElementV3>({});
#else
    self = CustomDictionary<std::string, IniElementV3>({});
#endif
#endif
    };

    /// <summary>
    /// Finalizes an instance of the <see cref="AppSettings" /> class.
    /// </summary>
    ~AppSettings() {};

    /// <summary>
    /// Adds the boolean setting. Returns true if adds new setting; otherwise changes current matching Ini Setting and returns false.
    /// </summary>
    /// <param name="IniSetting">The ini setting.</param>
    /// <param name="IniValue">The ini value.</param>
    /// <returns>bool.</returns>
    bool AddBoolSetting(std::string IniSetting, std::string IniValue)
    {
        IniElementV3 elementFound = ReturnIndexIfElementExists(IniSetting);
    }

    /// <summary>
    /// Adds the Integer setting. Returns true if adds new setting; otherwise changes current matching Ini Setting and returns false.
    /// </summary>
    /// <param name="IniSetting">The ini setting.</param>
    /// <param name="IniValue">The ini value.</param>
    /// <returns>bool.</returns>
    bool AddIntSetting(std::string IniSetting, std::string IniValue)
    {
        IniElementV3 elementFound = ReturnIndexIfElementExists(IniSetting);
    }

    /// <summary>
    /// Adds the float setting. Returns true if adds new setting; otherwise changes current matching Ini Setting and returns false.
    /// </summary>
    /// <param name="IniSetting">The ini setting.</param>
    /// <param name="IniValue">The ini value.</param>
    /// <returns>bool.</returns>
    bool AddFloatSetting(std::string IniSetting, std::string IniValue)
    {
        IniElementV3 elementFound = ReturnIndexIfElementExists(IniSetting);
    }

    /// <summary>
    /// Adds the MediumDec setting. Returns true if adds new setting; otherwise changes current matching Ini Setting and returns false.
    /// </summary>
    /// <param name="IniSetting">The ini setting.</param>
    /// <param name="IniValue">The ini value.</param>
    /// <returns>bool.</returns>
    bool AddAltNumSetting(std::string IniSetting, std::string IniValue)
    {
        IniElementV3 elementFound = ReturnIndexIfElementExists(IniSetting);
    }

    /// <summary>
    /// Adds the boolean setting. Returns true if adds new setting; otherwise changes current matching Ini Setting and returns false.
    /// </summary>
    /// <param name="IniSetting">The ini setting.</param>
    /// <param name="IniValue">The ini value.</param>
    /// <returns>bool.</returns>
    bool AddVoidSetting(std::string IniSetting, std::string IniValue)
    {
        IniElementV3 elementFound = ReturnIndexIfElementExists(IniSetting);
    }

    /// <summary>
    /// Adds the boolean setting. Returns true if adds new setting; otherwise changes current matching Ini Setting and returns false.
    /// </summary>
    /// <param name="IniSetting">The ini setting.</param>
    /// <param name="IniValue">The ini value.</param>
    /// <returns>bool.</returns>
    bool AddStringSetting(std::string IniSetting, std::string IniValue)
    {
        IniElementV3 elementFound = ReturnIndexIfElementExists(IniSetting);
    }

#ifdef BlazesRusAppSetting_EnableListFocusedAppSettings
#elif BlazesRusAppSetting_EnableMapFocusedAppSettings
    /// <summary>
    /// Adds the specified key.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    /// <returns>bool</returns>
    bool Add(std::string Key, bool Value)
    {
        if (self.AddOnlyNew(Key, BoolDeclaration)) { BoolSettings.AddOnlyNew(Key, Value); return true; }
        else { return false; }
    }


    /// <summary>
    /// Adds the specified key.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    /// <returns>bool</returns>
    bool Add(std::string Key, int Value)
    {
        if (self.AddOnlyNew(Key, IntDeclaration)) { return IntSettings.AddOnlyNew(Key, Value); return true; }
        else { return false; }
    }

    /// <summary>
    /// Adds the specified key.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    /// <returns>bool</returns>
    bool Add(std::string Key, std::string Value)
    {
        return self.AddOnlyNew(Key, Value);
    }

/// <summary>
/// Gets the element data.
/// </summary>
/// <param name="Value">The value.</param>
/// <returns>std::string</returns>
    std::string GetElementData(std::string Value)
    {
        tsl::ordered_map<std::string, std::string>::iterator ValueInfo = self.find(Value);
        if (ValueInfo == self.end())
        {
            return "";
        }
        else
        {
            std::string ElementValue = ValueInfo->second;
            if (ElementValue == IntDeclaration)
            {
                return BlazesRusCode::VariableConversionFunctions::IntToStringConversion(IntSettings[Value]);
            }
            else if (ElementValue == BoolDeclaration)
            {
                if(BoolSettings[Value]==true)
                {
                    return "true";
                }
                else
                {
                    return "false";
                }
            }
#ifdef BlazesMFCAppIni_EnableFloat
            else if (ElementValue == FloatDeclaration)
            {
                return BlazesRusCode::VariableConversionFunctions::FloatToStringConversion(FloatSettings[Value]);
            }
#endif
#ifdef BlazesMFCAppIni_EnableAltDec
            else if (ElementValue == MediumDecDeclaration)
            {
                return MediumDecSettings[Value].ToFullString();
            }
#endif
            else
            {
                return ElementValue;
            }
        }
    }


    /// <summary>
    /// Sets the string element data.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    void SetStringElementData(std::string Key, std::string Value)
    {
        self.Add(Key, Value);
    }


/*
    /// <summary>
    /// Sets the string element data.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">if set to <c>true</c> then [value] is "true" otherwise "false".</param>
    void SetBoolElementDataToStringElement(std::string Key, bool Value)
    {
        if(Value==true){ self.Add(Key, "true"); }
        else { self.Add(Key, "false"); }
    }
*/

    /// <summary>
    /// Gets the int element data.
    /// </summary>
    /// <param name="Value">The value.</param>
    /// <returns>int.</returns>
    int GetIntElementData(std::string Value)
    {
        return IntSettings[Value];
    }

    /// <summary>
    /// Sets the int element data.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    void SetIntElementData(std::string Key, int Value)
    {
/*
        if (Add(Key, Value) == false) {//Only set Int Element setting if key already exists
            std::unordered_map<std::string, int>::iterator ValueInfo = IntSettings.find(Key);
            if (ValueInfo != IntSettings.end())
            {
                IntSettings.Add(Key, Value);
            }
        }
*/
    }

    /// <summary>
    /// Adds the value to the element data.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    void AddIntElementData(std::string Key, int Value)
    {
        IntSettings[Key] += Value;
    }

#ifdef BlazesMFCAppIni_EnableFloat
    /// <summary>
    /// Adds the specified key.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    /// <returns>bool</returns>
    bool Add(std::string Key, float Value)
    {
#ifdef BlazesRusAppSetting_UseIniElementV3Alternative
/*
        if (self.AddOnlyNew(Key, FloatDeclaration)) { return FloatSettings.AddOnlyNew(Key, Value); return true; }
        else { return false; }
*/
#else
        if (self.AddOnlyNew(Key, NewFloatVal)) { return FloatSettings.AddOnlyNew(Key, Value); return true; }
        else { return false; }
#endif
    }

    /// <summary>
    /// Gets the float element data.
    /// </summary>
    /// <param name="Value">The value.</param>
    /// <returns>float</returns>
    float GetFloatElementData(std::string Value){return FloatSettings[Value];}


    /// <summary>
    /// Sets the float element data.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    void SetFloatElementData(std::string Key, int Value)
    {
        FloatSettings.Add(Key, Value);
    }
#endif


    /// <summary>
    /// Gets the element data.
    /// </summary>
    /// <param name="Value">The value.</param>
    /// <returns>bool</returns>
    bool GetBoolElementData(std::string Value)
    {
        return BoolSettings[Value];
    }


    /// <summary>
    /// Sets the element data.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    void SetBoolElementData(std::string Key, bool Value)
    {
        BoolSettings.Add(Key, Value);
    }


    /// <summary>
    /// Toggle the element data.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <returns>bool</returns>
    bool ToggleBoolElementData(std::string Key)
    {
        bool Value = !this->BoolSettings[Key];
        BoolSettings[Key] = Value;
        return Value;
    }

#ifdef BlazesMFCAppIni_EnableAltDec
    /// <summary>
    /// Adds the specified key.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    /// <returns>bool</returns>
    bool Add(std::string Key, MediumDec Value)
    {
#ifdef BlazesRusAppSetting_UseIniElementV3Alternative
/*        
        if (self.AddOnlyNew(Key, MediumDecDeclaration)) { return MediumDecSettings.AddOnlyNew(Key, Value); return true; }
        else { return false; }
*/
#else
        if (self.AddOnlyNew(Key, MediumDecDeclaration)) { return MediumDecSettings.AddOnlyNew(Key, Value); return true; }
        else { return false; }
#endif
    }


    /// <summary>
    /// Adds the medium decimal element data.(No Checks for if Element already exists)
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    void AddMediumDecElementData(std::string Key, MediumDec Value)
    {
        MediumDecSettings[Key] += Value;
    }


    /// <summary>
    /// Gets the medium decimal element data.
    /// </summary>
    /// <param name="Value">The value.</param>
    /// <returns>MediumDec.</returns>
    MediumDec GetMediumDecElementData(std::string Value)
    {
        return MediumDecSettings[Value];
    }


    /// <summary>
    /// Sets the medium decimal element data.
    /// </summary>
    /// <param name="Key">The key.</param>
    /// <param name="Value">The value.</param>
    void SetMediumDecElementData(std::string Key, MediumDec Value)
    {
        if (Add(Key, Value) == false) {//Only set Int Element setting if key already exists
            std::unordered_map<std::string, MediumDec>::iterator ValueInfo = MediumDecSettings.find(Key);
            if (ValueInfo != MediumDecSettings.end())
            {
                MediumDecSettings.Add(Key, Value);
            }
        }
    }
#endif

#endif

#endif
public:
#ifdef MFCApp_UseIniTesterSettings
    bool AppSetting01;
#endif
    /// <summary>
    /// Loads the INI data.
    /// </summary>
    /// <param name="FileName">Name of the file.</param>
    /// <param name="IniFormat">The ini storage format.
    /// (TypeDeclaration) + Other Formating
    /// IniSetting:IniValue; format is (Default)</param>
    /// if(MFCApp_UseOldIniDataFormatForSettings) enabled, then [IniSetting=IniValue] format (based on my old C++ code)</param>
    /// <returns>bool.</returns>
    bool Load()
    {
        StringVectorList FileData;
        bool FileLoaded = FileData.LoadFileDataV2(IniFilePath, 1);
        if (FileLoaded == false)
        { 
            SetToDefaultSettings(); return false;
        }
        std::string LineData;
        std::string IniSetting = "";
        std::string IniValue = "";
        //byte InsideComment = 0;
#if defined(BlazesRusAppSetting_EnableListFocusedAppSettings) || defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)
        std::string TypeName = "";
        bool InsideTypeDeclaration = false;
#endif
        std::string builder = "";
#ifdef MFCApp_UseOldIniDataFormatForSettings
        bool InsideParenthesis = false;
        int CommandStage = 0;
#endif
        for (int Index = 0; Index < FileData.length(); ++Index)
        {
            LineData = FileData[Index];
            for (const char LineChar : LineData)
            {
#ifdef MFCApp_UseOldIniDataFormatForSettings
                if (LineChar == '"') { InsideParenthesis = !InsideParenthesis; }
                else if (LineChar == '[')
                {
                    IniSetting = "";
                    CommandStage = 1;
                }
#if defined(BlazesRusAppSetting_EnableListFocusedAppSettings) || defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)
                else if (InsideTypeDeclaration)
                {
                    if (LineChar == ')')
                    {
                        TypeName = builder;
                        InsideTypeDeclaration = false;
                    }
                    else
                    {
                        builder.append(&LineChar);//builder += LineChar;
                    }
                }
                else if (LineChar == '(')
                {
                    builder.clear(); InsideTypeDeclaration = true;
                }
#endif
                else if (CommandStage > 0)
                {
                    if (InsideParenthesis == false && (LineChar == '=' || LineChar == ':'))
                    {
                        CommandStage = 2;
                    }
                    else if (CommandStage == 2)
                    {
                        if (LineChar == ']')
                        {
                            CommandStage = 0;
#ifdef MFCApp_UseIniTesterSettings
                            if (IniSetting == "AppSetting01")
                                AppSetting01 = IniValue == "true" ? true : false;
#if !defined(BlazesRusAppSetting_EnableListFocusedAppSettings) && !defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)
                            else
                                std::cout << "Unknown setting named " + IniSetting + " not loaded from AppSettings.ini." << std::endl;
#endif
#endif

#if defined(BlazesRusAppSetting_EnableListFocusedAppSettings) || defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)
                            if (TypeName == "Bool")
                                AddBoolSetting(IniSetting, IniValue);
                            else if (TypeName == "Int")
                                AddIntSetting(IniSetting, IniValue);
#ifdef BlazesMFCAppIni_EnableAltNum
                            else if (TypeName == "MediumDec")
                                AddAltNumSetting(IniSetting, IniValue);
#endif
#ifdef BlazesMFCAppIni_EnableFloat
                            else if (TypeName == "Float")
                                AddFloatSetting(IniSetting, IniValue);
#endif
#ifdef BlazesMFCAppIni_EnableVoid
                            else if (TypeName == "Void")
                                AddVoidSetting(IniSetting);
#endif                    
                            else//StringSetting
                                AddStringSetting(IniSetting, IniValue);
#endif
                            IniValue = "";
                            IniSetting = "";
                        }
                        else
                        {
                            IniValue += LineChar;
                        }
                    }
                    else
                    {
                        IniSetting += LineChar;
                    }
                }
#else
                if (LineChar == ':')
                {
                    IniSetting = builder;
                    builder.clear();
                }
#ifdef MFCApp_StoreDynamicAppSettings
                else if (InsideTypeDeclaration)
                {
                    if (LineChar == ')')
                    {
                        TypeName = builder;
                        InsideTypeDeclaration = false;
                    }
                    else
                    {
                        builder.append(&LineChar);
                    }
                }
                else if (LineChar == '(')
                {
                    builder.clear(); InsideTypeDeclaration = true;
                }
#endif
                else if (LineChar == ';')
                {
                    IniValue = builder;
                    builder.clear();
#ifdef MFCApp_UseIniTesterSettings
                    if (IniSetting == "AppSetting01")
                        AppSetting01 = IniValue == "true" ? true : false;
#if !defined(BlazesRusAppSetting_EnableListFocusedAppSettings) && !defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)
                    else
                        std::cout << "Unknown setting named " + IniSetting + " not loaded from AppSettings.ini." << std::endl;
#endif
#endif
#if defined(BlazesRusAppSetting_EnableListFocusedAppSettings) || defined(BlazesRusAppSetting_EnableMapFocusedAppSettings)
                    if (TypeName == "Bool")
                        AddBoolSetting(IniSetting, IniValue);
                    else if (TypeName == "Int")
                        AddIntSetting(IniSetting, IniValue);
#ifdef BlazesMFCAppIni_EnableAltNum
                    else if (TypeName == "MediumDec")
                        AddAltNumSetting(IniSetting, IniValue);
#endif
#ifdef BlazesMFCAppIni_EnableFloat
                    else if (TypeName == "Float")
                        AddFloatSetting(IniSetting, IniValue);
#endif
#ifdef BlazesMFCAppIni_EnableVoid
                    else if (TypeName == "Void")
                        AddVoidSetting(IniSetting);
#endif                    
                    else//StringSetting
                        AddStringSetting(IniSetting, IniValue);
#endif
                }
                else if (LineChar == '/')//Start of line comment detected so skip rest of line
                {
                    if (builder == "/")
                    {
                        builder.clear();
                        break;
                    }
                    else//False alarm on line comment detection
                    {
                        builder.append(&LineChar);
                    }
                }
                else
                {
                    if (builder.length() == 0)
                    {
                        continue;
                    }
                    else
                    {
                        builder.append(&LineChar);
                        continue;
                    }
                }
            }
#endif
        }
        return true;
    }

    /// <summary>
    /// Saves the INI data.
    /// </summary>
    /// <param name="FileName">Name of the file.</param>
    /// <param name="IniFormat">The INI format.</param>
    /// <returns>bool.</returns>
    bool Save()
    {
#if defined(BlazesRusAppSetting_EnableListFocusedAppSettings)//C4101 Warning Fix
        size_t StringLength;
        char LineChar;
#endif
        std::string LineString;
        std::fstream LoadedFileStream;
#ifndef MFCApp_SaveFreshConfigFile
        bool LoadingExistingFile =
#endif
            BlazesRusCode::FileOps::CreateFileIfDoesntExist(IniFilePath);
#ifdef MFCApp_SaveFreshConfigFile
        LoadedFileStream.open(IniFilePath.c_str(), std::fstream::out | std::fstream::trunc);
#else
        LoadedFileStream.open(IniFilePath.c_str(), std::fstream::out | std::fstream::in);
#endif
        std::string IniSetting = "";
        std::string IniValue = "";
#ifdef BlazesRusAppSetting_EnableListFocusedAppSettings
        std::string TypeName = "";
        bool InsideTypeDeclaration = false;
#endif
        if (LoadedFileStream.is_open())
        {
            if (LoadedFileStream.good())
            {//Saving to file now
#ifndef MFCApp_SaveFreshConfigFile
                if (LoadingExistingFile)
                {
#ifdef MFCApp_StoreDynamicAppSettings

#endif

                }
                else//Otherwise CreatingFreshFile
                {
#endif
#ifdef MFCApp_UseOldIniDataFormatForSettings//[IniSetting=IniValue]
#ifdef MFCApp_UseIniTesterSettings
                    LoadedFileStream << "[AppSetting01=";
                    if (AppSetting01)
                        LoadedFileStream << "true";
                    else
                        LoadedFileStream << "false";
                    LoadedFileStream << "]\n";
#endif
#else//IniSetting:IniValue;
#ifdef MFCApp_UseIniTesterSettings
                    LoadedFileStream << "AppSetting01:";
                    if (AppSetting01)
                        LoadedFileStream << "true";
                    else
                        LoadedFileStream << "false";
                    LoadedFileStream << ";\n";
#endif
#endif
#ifdef MFCApp_StoreDynamicAppSettings
                    if (!self.empty())
                    {
#if defined(BlazesRusAppSetting_StoreDynamicSettingsInList)
#else
/*                      //To-Do Fix this code later
                        LineString = self.ElementAt(0);
                        StringLength = LineString.length();
                        for (size_t StringIndex = 0; StringIndex < StringLength; ++StringIndex)
                        {
                            LineChar = LineString.at(StringIndex);
                            LoadedFileStream << LineChar;
                        }
                        for (size_t i = 1; i < DataSize; ++i)
                        {
                            //Carriage Return to next line
                            LoadedFileStream << "\n";
                            LineString = self.ElementAt(i);
                            StringLength = LineString.length();
                            for (size_t StringIndex = 0; StringIndex < StringLength; ++StringIndex)
                            {
                                LineChar = LineString.at(StringIndex);
                                LoadedFileStream << LineChar;
                            }
                        }
*/
#endif
                    }
#endif
#ifndef MFCApp_SaveFreshConfigFile
                }
#endif
    }
            else
            {
                if (LoadedFileStream.bad()) { std::cout << "Failed Read/Write operation Error!\n"; }
                else if (LoadedFileStream.fail()) { std::cout << "Failed format based Error!\n"; }
                else if (LoadedFileStream.bad()) { std::cout << "Failed Read/Write operation Error!\n"; }
                else if (LoadedFileStream.eof()) {/*Send debug message of reaching end of file?*/ }
            }
            LoadedFileStream.close();
        }
        else
        {
            std::cout << "Failed to open " << IniFilePath << ".\n";
        }
        return false;
    }
};