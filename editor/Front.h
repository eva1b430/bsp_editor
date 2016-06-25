#if !defined(AFX_FRONT_H__31B4FF8B_EA2A_4736_83FB_A97D9F7BE74E__INCLUDED_)
#define AFX_FRONT_H__31B4FF8B_EA2A_4736_83FB_A97D9F7BE74E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Front.h : header file
//

#include "Orthographic.h"

/////////////////////////////////////////////////////////////////////////////
// CFront view

class CFront : public COrthographic
{
protected:
	CFront();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFront)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFront)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFront();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CFront)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRONT_H__31B4FF8B_EA2A_4736_83FB_A97D9F7BE74E__INCLUDED_)
