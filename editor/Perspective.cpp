// Perspective.cpp : implementation file
//

#include "stdafx.h"
#include "Viewer.h"
#include "Perspective.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPerspective

IMPLEMENT_DYNCREATE(CPerspective, COpenGLWnd)

CPerspective::CPerspective()
{
	m_xpos = 0.0f;
	m_ypos = 0.0f;
	m_zoom = 10.0f;
	m_xrot = 0.0f;
	m_yrot = 0.0f;
}

CPerspective::~CPerspective()
{
}

/////////////////////////////////////////////////////////////////////////////
// CPerspective drawing

void CPerspective::OnDraw(CDC* pDC)
{
	SetContext();
	glLoadIdentity();

	// Position the camera
	glTranslatef( m_xpos, -m_ypos, -m_zoom );

	// Adjust viewport for md3 models which
	// use a different coordinate system -
	// 3DSMAX format.
	glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
	glRotatef( -90.0f, 0.0f, 0.0f, 1.0f );

	// Rotate the camera
	glRotatef( m_xrot, 0.0f, 0.0f, 1.0f );
	glRotatef( m_yrot, 0.0f, 1.0f, 0.0f );
	RenderScene();
	SwapGLBuffers();
}

BEGIN_MESSAGE_MAP(CPerspective, COpenGLWnd)
	//{{AFX_MSG_MAP(CPerspective)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPerspective diagnostics

#ifdef _DEBUG
void CPerspective::AssertValid() const
{
	CView::AssertValid();
}

void CPerspective::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPerspective message handlers

// Adjust the viewport after a window sizing.
void CPerspective::OnSize(UINT nType, int cx, int cy) 
{
	COpenGLWnd::OnSize(nType, cx, cy);

	if ( 0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED )
		return;

	// Change the perspective viewing volume to
	// reflect the new dimensions of the window.
	SetContext();
	glViewport( 0, 0, cx, cy );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(45.0f, (float)(cx)/(float)(cy), 0.01f, 1000.0f);
	glMatrixMode( GL_MODELVIEW );
}

void CPerspective::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Move the camera if control is being
	// pressed and the apropriate mouse
	// button is being held down.

	if ( nFlags & MK_CONTROL )
	{
		if ( nFlags & MK_LBUTTON )
		{
			// Left mouse button is being
			// pressed. Rotate the camera.
			if ( m_lastMouseX != -1 )
			{
				m_yrot += point.y - m_lastMouseY;
				m_xrot += point.x - m_lastMouseX;
				// Redraw the viewport.
				OnDraw( NULL );
			}
			m_lastMouseX = point.x;
			m_lastMouseY = point.y;
		}
		else if ( nFlags & MK_MBUTTON )
		{
			// Middle mouse button is being
			// pressed. Zoom the camera.
			if ( m_lastMouseY != -1 )
			{
				m_zoom += point.y - m_lastMouseY;
				// Redraw the viewport.
				OnDraw( NULL );
			}
			m_lastMouseY = point.y;
		}
		else if ( nFlags & MK_RBUTTON )
		{
			// Right mouse button is being
			// pressed. Pan the camera.
			if ( m_lastMouseX != -1 )
			{
				m_xpos += (point.x - m_lastMouseX) * 0.15f;
				m_ypos += (point.y - m_lastMouseY) * 0.15f;
				// Redraw the viewport.
				OnDraw( NULL );
			}
			m_lastMouseX = point.x;
			m_lastMouseY = point.y;
		}
		else
		{
			m_lastMouseX = -1;
			m_lastMouseY = -1;
		}
	}
	else
	{
		m_lastMouseX = -1;
		m_lastMouseY = -1;
	}

	COpenGLWnd::OnMouseMove(nFlags, point);
}
