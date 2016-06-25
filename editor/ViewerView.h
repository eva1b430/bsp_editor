// ViewerView.h : interface of the CViewerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWERVIEW_H__C2F26A25_A563_40EF_8C66_74B05D4A7FC9__INCLUDED_)
#define AFX_VIEWERVIEW_H__C2F26A25_A563_40EF_8C66_74B05D4A7FC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ViewerDoc.h"

class CViewerView : public CView
{
protected: // create from serialization only
	CViewerView();
	DECLARE_DYNCREATE(CViewerView)

// Attributes
public:
	CViewerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CViewerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ViewerView.cpp
inline CViewerDoc* CViewerView::GetDocument()
   { return (CViewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWERVIEW_H__C2F26A25_A563_40EF_8C66_74B05D4A7FC9__INCLUDED_)
