#if !defined(AFX_SIDE_H__3421E0E0_728A_49E0_93A4_DA48D5862EDD__INCLUDED_)
#define AFX_SIDE_H__3421E0E0_728A_49E0_93A4_DA48D5862EDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Side.h : header file
//

#include "Orthographic.h"

/////////////////////////////////////////////////////////////////////////////
// CSide view

class CSide : public COrthographic
{
protected:
	CSide();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSide)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSide)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSide();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSide)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIDE_H__3421E0E0_728A_49E0_93A4_DA48D5862EDD__INCLUDED_)
