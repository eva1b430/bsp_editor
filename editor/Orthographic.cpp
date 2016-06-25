// Orthographic.cpp : implementation file
//

#include "stdafx.h"
#include "Viewer.h"
#include "Orthographic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrthographic

IMPLEMENT_DYNCREATE(COrthographic, COpenGLWnd)

COrthographic::COrthographic()
{
	m_zoom = 5.0f;
	m_xpos = 0.0f;
	m_ypos = 0.0f;
}

COrthographic::~COrthographic()
{
}


BEGIN_MESSAGE_MAP(COrthographic, COpenGLWnd)
	//{{AFX_MSG_MAP(COrthographic)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrthographic diagnostics

#ifdef _DEBUG
void COrthographic::AssertValid() const
{
	CView::AssertValid();
}

void COrthographic::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COrthographic message handlers

void COrthographic::OnSize(UINT nType, int cx, int cy) 
{
	COpenGLWnd::OnSize(nType, cx, cy);
	
	if ( 0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED )
		return;

	// Change the orthographic viewing volume to
	// reflect the new dimensions of the window
	// and the zoom and position of the viewport.
	SetContext();
	glViewport( 0, 0, cx, cy );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( (float)(cx)/(float)(cy)*-m_zoom-m_xpos, (float)(cx)/(float)(cy)*m_zoom-m_xpos,
		-m_zoom+m_ypos, m_zoom+m_ypos, -200.0f, 200.0f );
	glMatrixMode( GL_MODELVIEW );
}

void COrthographic::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Move the camera if control is being
	// pressed and the apropriate mouse
	// button is being held down.

	CRect cr;

	GetClientRect( &cr );
	if ( nFlags & MK_CONTROL )
	{
		if ( nFlags & MK_MBUTTON )
		{
			// Middle mouse button is being
			// pressed. Zoom the camera.
			if ( m_lastMouseY != -1 )
			{
				m_zoom += (point.y - m_lastMouseY) * 0.25f;
				// Apply the position changes to
				// the viewport.
				OnSize( SIZE_MAXIMIZED, cr.Width(), cr.Height() );
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
				m_xpos += (point.x - m_lastMouseX) * 0.25f;
				m_ypos += (point.y - m_lastMouseY) * 0.25f;
				// Apply the position changes to
				// the viewport.
				OnSize( SIZE_MAXIMIZED, cr.Width(), cr.Height() );
				OnDraw( NULL );
			}
			m_lastMouseX = point.x;
			m_lastMouseY = point.y;
		}
		else
		{
			// No mouse button was pressed.
			// Mark the mouse flags to indicate
			// the camera did not move last
			// message.
			m_lastMouseX = -1;
			m_lastMouseY = -1;
		}
	}
	else
	{
		// Control was not pressed.
		// Mark the mouse flags to indicate
		// the camera did not move last
		// message.
		m_lastMouseX = -1;
		m_lastMouseY = -1;
	}

	COpenGLWnd::OnMouseMove(nFlags, point);
}
