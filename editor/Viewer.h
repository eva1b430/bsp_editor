// Viewer.h : main header file for the VIEWER application
//

#if !defined(AFX_VIEWER_H__35728A09_C613_4988_A628_A09B0293B851__INCLUDED_)
#define AFX_VIEWER_H__35728A09_C613_4988_A628_A09B0293B851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CViewerApp:
// See Viewer.cpp for the implementation of this class
//

class CViewerApp : public CWinApp
{
public:
	CViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CViewerApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWER_H__35728A09_C613_4988_A628_A09B0293B851__INCLUDED_)
