#if !defined(AFX_TOP_H__9301A394_2026_41A2_AA67_C4D217B0B412__INCLUDED_)
#define AFX_TOP_H__9301A394_2026_41A2_AA67_C4D217B0B412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Top.h : header file
//

#include "Orthographic.h"

/////////////////////////////////////////////////////////////////////////////
// CTop view

class CTop : public COrthographic
{
protected:
	CTop();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTop)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTop)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTop();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTop)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOP_H__9301A394_2026_41A2_AA67_C4D217B0B412__INCLUDED_)
