// Side.cpp : implementation file
//

#include "stdafx.h"
#include "Viewer.h"
#include "Side.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSide

IMPLEMENT_DYNCREATE(CSide, COrthographic)

CSide::CSide()
{
}

CSide::~CSide()
{
}


BEGIN_MESSAGE_MAP(CSide, COrthographic)
	//{{AFX_MSG_MAP(CSide)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSide drawing

void CSide::OnDraw(CDC* pDC)
{
	SetContext();
	glLoadIdentity();

	// Adjust viewport for md3 models which
	// use a different coordinate system -
	// 3DSMAX format.
	// After adding the other rotations
	// necessary we are left with a single
	// rotation.
	glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );

	RenderScene();
	SwapGLBuffers();
}

/////////////////////////////////////////////////////////////////////////////
// CSide diagnostics

#ifdef _DEBUG
void CSide::AssertValid() const
{
	CView::AssertValid();
}

void CSide::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSide message handlers
