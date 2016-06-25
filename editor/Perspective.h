#if !defined(AFX_PERSPECTIVE_H__433761F5_5AAF_4EBF_B3BB_F2CD2E20F500__INCLUDED_)
#define AFX_PERSPECTIVE_H__433761F5_5AAF_4EBF_B3BB_F2CD2E20F500__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Perspective.h : header file
//

#include "OpenGLWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CPerspective view

// Implements COpenGLWnd to create a perspective
// viewport.

class CPerspective : public COpenGLWnd
{
protected:
	CPerspective();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPerspective)

// Attributes
public:
	float m_zoom,
		  m_xpos,
		  m_ypos,
		  m_xrot,
		  m_yrot;
	int	  m_lastMouseX,
		  m_lastMouseY;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPerspective)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPerspective();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPerspective)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSPECTIVE_H__433761F5_5AAF_4EBF_B3BB_F2CD2E20F500__INCLUDED_)
