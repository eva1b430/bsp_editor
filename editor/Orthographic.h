#if !defined(AFX_ORTHOGRAPHIC_H__89B35520_EA7E_4AF2_9E2F_3E6CE6E3347B__INCLUDED_)
#define AFX_ORTHOGRAPHIC_H__89B35520_EA7E_4AF2_9E2F_3E6CE6E3347B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Orthographic.h : header file
//

#include "OpenGLWnd.h"

/////////////////////////////////////////////////////////////////////////////
// COrthographic view

class COrthographic : public COpenGLWnd
{
protected:
	COrthographic();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COrthographic)

// Attributes
public:
	int	  m_lastMouseX,
		  m_lastMouseY;
	float m_zoom,
		  m_xpos,
		  m_ypos;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrthographic)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COrthographic();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COrthographic)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORTHOGRAPHIC_H__89B35520_EA7E_4AF2_9E2F_3E6CE6E3347B__INCLUDED_)
