// Top.cpp : implementation file
//

#include "stdafx.h"
#include "Viewer.h"
#include "Top.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTop

IMPLEMENT_DYNCREATE(CTop, COrthographic)

CTop::CTop()
{
}

CTop::~CTop()
{
}


BEGIN_MESSAGE_MAP(CTop, COrthographic)
	//{{AFX_MSG_MAP(CTop)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTop drawing

void CTop::OnDraw(CDC* pDC)
{
	SetContext();
	glLoadIdentity();

	// Adjust viewport for md3 models which
	// use a different coordinate system -
	// 3DSMAX format.
	// After adding the other rotations
	// necessary we are left with a single
	// rotation.
	glRotatef( -90.0f, 45.0f, 45.0f, 1.0f );

	RenderScene();
	SwapGLBuffers();
}

/////////////////////////////////////////////////////////////////////////////
// CTop diagnostics

#ifdef _DEBUG
void CTop::AssertValid() const
{
	CView::AssertValid();
}

void CTop::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTop message handlers
