// ***********************************************************************
// Code Created by James Michael Armstrong (https://github.com/BlazesRus)
// Latest Code Release at https://github.com/BlazesRus/MFCApp under MIT licease
// (MainProject this is submodule to at https://github.com/BlazesRus/BlazesRusSharedCode)
// ***********************************************************************
#pragma once

#include "MFCpch.h"

#include "AboutDlg.hpp"

#ifndef __AFXWIN_H__
    #error "include 'MFCpch.h' before including this file for PCH"
#endif

#include "MFCRes.h"       // main symbols

#include "afxwinappex.h"
#include "afxdialogex.h"

#include "MFCFramework.h"
#include "MFCFrame.h"
#include "MFCDoc.h"

#ifndef BlazesMFCApp_UseSDI
#include "MFCSubFrame.h"
#endif

#include "../OtherFunctions/MFCMacrosV3.h"
#if defined(BlazesMFCApp_UseDefaultAppSettings) || defined(BlazesMFCApp_DisableAppSettings) || defined(BlazesMFCApp_UseRegistryStorage)
#include "../OtherFunctions/MFCOneArgMacros.h"
#else
#include "../OtherFunctions/MFCTwoArgMacros.h"
#endif

#ifdef BlazesMFCApp_UseDefaultAppSettings
#include "AppSettings.h"
#endif

/// <summary>
/// MFC based template for generating applications with a single view (Use AppProcessor.h to generate Application with default generic view type)
/// </summary>
#if defined(BlazesMFCApp_UseDefaultAppSettings) || defined(BlazesMFCApp_DisableAppSettings) || defined(BlazesMFCApp_UseRegistryStorage)
template <typename ViewType>
#else
template <typename ViewType,typename AppSettingsType>
#endif
class MFCApp : public CWinApp
{
protected:
    std::string RetrieveAppDirectoryLocation()
    {
        //GetApplicationDirectory();
        return "C:\\UserFiles\\GitHub\\BlazesRusSharedCode\\SharedCode\\MFCApp\\AppSettings\\";//Placeholder
    }
#ifdef BlazesMFCApp_UseRegistryStorage
    virtual std::string AppRegistryName;
#endif
public:
#ifndef BlazesMFCApp_UseRegistryStorage
    /// <summary>
    /// The application directory
    /// </summary>
    std::string AppDirectory;

#ifndef BlazesMFCApp_DisableAppSettings
    /// <summary>
    /// The local Application INI Storage
    /// </summary>
#ifdef BlazesMFCApp_UseDefaultAppSettings
    AppSettings
#else
    AppSettingsType
#endif
    AppSettingsData;
#endif

    /// <summary>
    /// Storages string for other local App based data(instead of storing window information in registry etc)
    /// </summary>
    CString AppIniProfile;
#endif

    MFCApp() noexcept
    {
        // TODO: replace application ID string below with unique ID string; recommended
        // format for string is CompanyName.ProductName.SubProduct.VersionInformation
        SetAppID(_T("MFCApp.AppID.NoVersion"));
        //m_bSaveState = FALSE;//Turns off some registry saving (only from CWinAppEx derived class)
        AppDirectory = RetrieveAppDirectoryLocation();
#ifdef BlazesMFCApp_UseRegistryStorage
        AppRegistryName = "MFCApp";
#else
#ifndef BlazesMFCApp_DisableAppSettings
        AppSettingsData.IniFilePath = AppDirectory + "AppSettings.ini";
#endif
#endif
    }

// Overrides
public:
/*
#ifndef BlazesMFCApp_UseRegistryStorage
    virtual BOOL SaveState(LPCTSTR lpszSectionName = NULL, CFrameImpl* pFrameImpl = NULL)
    {
        AppSettingsData.Save();
        return CWinApp::SaveState(&lpszSectionName, &pFrameImpl); //Debug Assertion Failure here(MFC/afxregpath.cpp line 33)
    }
    virtual BOOL LoadState(LPCTSTR lpszSectionName = NULL, CFrameImpl* pFrameImpl = NULL)
    {
        AppSettingsData.Load();
        return CWinAppEx::LoadState(&lpszSectionName, &pFrameImpl);//Unhandled exception on CWinAppEx::LoadState
    }
    virtual BOOL LoadWindowPlacement(CRect& rectNormalPosition, int& nFflags, int& nShowCmd)
    {
        return CWinApp::LoadWindowPlacement(rectNormalPosition, nFflags, nShowCmd);
    }
    virtual BOOL StoreWindowPlacement(const CRect& rectNormalPosition, int nFflags, int nShowCmd)
    {
        return CWinApp::StoreWindowPlacement(rectNormalPosition, &nFflags, &nShowCmd);
    }
#endif
*/
    /// <summary>
    /// MFCApp initialization Code
    /// </summary>
    virtual BOOL InitInstance()
    {
        // InitCommonControlsEx() is required on Windows XP if an application
        // manifest specifies use of ComCtl32.dll version 6 or later to enable
        // visual styles.  Otherwise, any window creation will fail.
        INITCOMMONCONTROLSEX InitCtrls;
        InitCtrls.dwSize = sizeof(InitCtrls);
        // Set this to include all the common control classes you want to use
        // in your application.
        InitCtrls.dwICC = ICC_WIN95_CLASSES;
        InitCommonControlsEx(&InitCtrls);

        CWinApp::InitInstance();

#ifdef BlazesMFCApp_UseSDI
        EnableTaskbarInteraction(FALSE);
#else
        EnableTaskbarInteraction();
#endif

        // AfxInitRichEdit2();// AfxInitRichEdit2() is required to use RichEdit control

        // Standard initialization
        // If you are not using these features and wish to reduce the size
        // of your final executable, you should remove from the following
        // the specific initialization routines you do not need
#ifdef BlazesMFCApp_UseRegistryStorage
    // Change the registry key under which our settings are stored
        SetRegistryKey(_T(AppRegistryName));// TODO: You should modify this string to be something appropriate(such as the name of your company or organization)
        LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
#else//Portable non-registry storage variant(localOnly Profile settings including last file storage)
#ifndef BlazesMFCApp_DisableAppSettings
        AppSettingsData.Load();
#endif
        //Fix for forcing to not use registry based on https://forums.codeguru.com/showthread.php?458625-MFC-How-to-NOT-use-the-registry
        AppIniProfile = AppDirectory.c_str();
        AppIniProfile += _T("\\AppProfile.ini");
        free((void*)m_pszProfileName);
        m_pszProfileName = _tcsdup(AppIniProfile);
#endif

    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views
#ifdef BlazesMFCApp_UseSDI//Single
    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views
        CSingleDocTemplate* pDocTemplate;
        pDocTemplate = new CSingleDocTemplate(
            IDR_MAINFRAME,
            RUNTIME_CLASS(MFCDoc),
            RUNTIME_CLASS(MFCFrame),       // main SDI frame window
            RUNTIME_CLASS(ViewType));//Replace MFCView with custom view derived from MFCView/CView
#else
        CMultiDocTemplate* pDocTemplate;
        pDocTemplate = new CMultiDocTemplate(IDR_MFCAppTYPE,
            RUNTIME_CLASS(MFCDoc),
            RUNTIME_CLASS(MFCSubFrame), // custom MDI child frame
            RUNTIME_CLASS(ViewType));
#endif
        if (!pDocTemplate)
            return FALSE;
        AddDocTemplate(pDocTemplate);

#ifndef BlazesMFCApp_UseSDI
        // create main MDI Frame window
        MFCFrame* pMainFrame = new MFCFrame;
        if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))//Debug Assertion Failure here(MFC/afxregpath.cpp line 33)
        {
            delete pMainFrame;
            return FALSE;
        }
        m_pMainWnd = pMainFrame;
#endif

        // Parse command line for standard shell commands, DDE, file open
        CCommandLineInfo cmdInfo;
        ParseCommandLine(cmdInfo);

        // Dispatch commands specified on the command line.  Will return FALSE if
        // app was launched with /RegServer, /Register, /Unregserver or /Unregister.
        if (!ProcessShellCommand(cmdInfo))
            return FALSE;

#ifdef BlazesMFCApp_UseSDI
        // The one and only window has been initialized, so show and update it
        m_pMainWnd->ShowWindow(SW_SHOW);
        m_pMainWnd->UpdateWindow();
#else
        // The main window has been initialized, so show and update it
        pMainFrame->ShowWindow(m_nCmdShow);
        pMainFrame->UpdateWindow();
#endif
        return TRUE;
    }

#ifndef BlazesMFCApp_UseSDI
    virtual int ExitInstance()
    {
        //TODO: handle additional resources you may have added
        return CWinApp::ExitInstance();//Or CWinAppEx::ExitInstance();
    }
#endif

// Implementation
    /// <summary>
    /// App command to run the (About Application) dialog
    /// </summary>
    afx_msg void OnAppAbout()
    {
        AboutDlg aboutDlg;
        aboutDlg.DoModal();
    }

#if defined(BlazesMFCApp_UseDefaultAppSettings) || defined(BlazesMFCApp_DisableAppSettings) || defined(BlazesMFCApp_UseRegistryStorage)
    MFC_RuntimeExtPart01With01Args(MFCApp, ViewType, CWinApp)
#else
    MFC_RuntimeExtPart01With02Args(MFCApp, ViewType, AppSettingsType, CWinApp)
#endif
    ON_COMMAND(ID_APP_ABOUT, &MFCApp::OnAppAbout)
    // Standard file based document commands
    ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
#ifndef BlazesMFCApp_DisablePrinter
    // Standard print setup command
    ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
#endif
    MFC_RuntimeExtPart02()
#if defined(BlazesMFCApp_UseDefaultAppSettings) || defined(BlazesMFCApp_DisableAppSettings) || defined(BlazesMFCApp_UseRegistryStorage)
    MFC_RuntimeExtClassNameWith01Args(MFCApp, ViewType)
#else
    MFC_RuntimeExtClassNameWith02Args(MFCApp, ViewType, AppSettingsType)
#endif
};

#if defined(BlazesMFCApp_UseDefaultAppSettings) || defined(BlazesMFCApp_DisableAppSettings) || defined(BlazesMFCApp_UseRegistryStorage)
MFC_RuntimeImplimentationWith01Args(MFCApp, ViewType)
MFC_RuntimeClassImplimentationWith01Args(MFCApp, ViewType)
#else
MFC_RuntimeImplimentationWith02Args(MFCApp, ViewType, AppSettingsType)
MFC_RuntimeClassImplimentationWith02Args(MFCApp, ViewType, AppSettingsType)
#endif