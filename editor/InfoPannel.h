#if !defined(AFX_INFOPANNEL_H__B751A131_7D75_45BF_8B0F_2EC630B0DA27__INCLUDED_)
#define AFX_INFOPANNEL_H__B751A131_7D75_45BF_8B0F_2EC630B0DA27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoPannel.h : header file
//

// Some constants for the dropdown lists used to
// change views.

#define FRONTVIEWPORT 0
#define TOPVIEWPORT 1
#define SIDEVIEWPORT 2
#define PERSPVIEWPORT 3

/////////////////////////////////////////////////////////////////////////////
// CInfoPannel form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CInfoPannel : public CFormView
{
protected:
	CInfoPannel();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CInfoPannel)

// Form Data
public:
	//{{AFX_DATA(CInfoPannel)
	enum { IDD = IDD_INFOPANNEL };
	int		m_lowerLeft;
	int		m_lowerRight;
	int		m_upperLeft;
	int		m_upperRight;
	//}}AFX_DATA

// Attributes
public:
	// A pointer to the viewport splitter window. Used
	// to change the different views in each frame with
	// controlls in the CFormView.
	CSplitterWnd *m_viewports;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoPannel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInfoPannel();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CInfoPannel)
	afx_msg void OnEditchangeUpperleft();
	afx_msg void OnEditchangeUpperright();
	afx_msg void OnEditchangeLowerleft();
	afx_msg void OnEditchangeLowerright();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOPANNEL_H__B751A131_7D75_45BF_8B0F_2EC630B0DA27__INCLUDED_)
