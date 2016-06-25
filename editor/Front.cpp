// Front.cpp : implementation file
//

#include "stdafx.h"
#include "Viewer.h"
#include "Front.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFront

IMPLEMENT_DYNCREATE(CFront, COrthographic)

CFront::CFront()
{
}

CFront::~CFront()
{
}


BEGIN_MESSAGE_MAP(CFront, COrthographic)
	//{{AFX_MSG_MAP(CFront)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFront drawing

void CFront::OnDraw(CDC* pDC)
{
	SetContext();
	glLoadIdentity();

	// Adjust viewport for md3 models which
	// use a different coordinate system -
	// 3DSMAX format.
	glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
	glRotatef( -90.0f, 0.0f, 0.0f, 1.0f );

	// this is the front viewport no further
	// rotation is necessary.

	RenderScene();
	SwapGLBuffers();
}

/////////////////////////////////////////////////////////////////////////////
// CFront diagnostics

#ifdef _DEBUG
void CFront::AssertValid() const
{
	CView::AssertValid();
}

void CFront::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFront message handlers
