// ***********************************************************************
// Code Created by James Michael Armstrong (https://github.com/BlazesRus)
// Latest Code Release at https://github.com/BlazesRus/MFCApp under MIT licease
// (MainProject this is submodule to at https://github.com/BlazesRus/BlazesRusSharedCode)
// ***********************************************************************
#pragma once
#ifdef BlazesMFCApp_EnableOutputWindow
#include "OutputWnd.h"
#endif

#include "../OtherFunctions/MFCMacrosV3.h"

class MFCFrame
#ifdef BlazesMFCApp_UseSDI
: public CFrameWnd
#else
: public CMDIFrameWndEx
#endif
{
protected: // create from serialization only
    MFCFrame() noexcept;
/*
#ifdef BlazesMFCApp_UseSDI
protected: // create from serialization only
    MFCFrame() noexcept;
    DECLARE_DYNCREATE(MFCFrame)
#else
    DECLARE_DYNAMIC(MFCFrame)
public:
    MFCFrame() noexcept;
#endif
*/
// Attributes
public:

// Operations
public:

// Overrides
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
    virtual ~MFCFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
    CToolBar          m_wndToolBar;
    CStatusBar        m_wndStatusBar;
    CReBar            m_wndReBar;
    CDialogBar        m_wndDlgBar;
#ifdef BlazesMFCApp_EnableOutputWindow
    OutputWnd        m_wndOutput;
#endif

#ifdef BlazesMFCApp_EnableOutputWindow
    BOOL CreateOutputWindows();
#endif

// Generated message map functions
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

#ifdef BlazesMFCApp_UseSDI
    MFC_RuntimeExtPart01(MFCFrame, CFrameWnd)
    //Any message map messages here
    MFC_RuntimeExtPart02()
    MFC_RuntimeExtClassName(MFCFrame)
#else
    MFC_RuntimeExtPart01(AppProcesser, CMDIFrameWndEx)
    //Any message map messages here
    MFC_RuntimeExtPart02()
    MFC_RuntimeExtClassName(AppProcesser)
#endif
};

MFC_RuntimeImplimentation(MFCFrame)
MFC_RuntimeClassImplimentation(MFCFrame)

