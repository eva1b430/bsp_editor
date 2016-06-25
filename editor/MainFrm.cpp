// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Viewer.h"

#include "ViewerView.h"
#include "InfoPannel.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_initSplitters = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRect cr;	// client rectangle -
				// used to calculate client sizes

	GetClientRect( &cr );

	// Setup each splitter window.
	// For more information on the individual
	// params of each member function refer to
	// the MSDN library.
	
	// Create the main splitter with 1 row and 2
	// columns.

	// This splitter seperates the viewports from
	// the information bar to the right of the
	// application. Since it's unlikely that we
	// would want to change the order or the
	// number of rows and columns for this splitter
	// we make it static.
	if ( !m_mainSplitter.CreateStatic( this, 1, 2 ) )
	{
		MessageBox( "Error setting up splitter frames!", "Init Error!",
			MB_OK | MB_ICONERROR );
		return FALSE;
	}

	// Create the views for each pane in the main
	// splitter. Static splitters must have each
	// pane filled immediately after creation before
	// they are displayed.

	// Create the information bar view with a
	// CInfoPannel class.
	if ( !m_mainSplitter.CreateView( 0, 1, RUNTIME_CLASS(CInfoPannel),
		CSize( INFOBAR_SIZE, cr.Height() ), pContext ) )
	{
		MessageBox( "Error setting up splitter frames!", "Init Error!",
			MB_OK | MB_ICONERROR );
		return FALSE;
	}

	// Setup a pointer to the viewport splitter to be
	// used later by the information bar to change
	// viewports.
	((CInfoPannel*)(m_mainSplitter.GetPane( 0, 1 )))->m_viewports = &m_viewportSplitter;

	// Create a new splitter to be nested in the first
	// row, first column of the main splitter.

	// This splitter seperates the viewports into their
	// respective frames. Again we make it static.

	if ( !m_viewportSplitter.CreateStatic( &m_mainSplitter, 2, 2, WS_CHILD | WS_VISIBLE,
		m_mainSplitter.IdFromRowCol( 0, 0 ) ) )
	{
		MessageBox( "Error setting up splitter frames!", "Init Error!",
			MB_OK | MB_ICONERROR );
		return FALSE;
	}

	// Create the views for each pane in the viewport
	// splitter.

	// Top viewport
	if ( !m_viewportSplitter.CreateView( 0, 0, RUNTIME_CLASS(CTop),
		CSize( ( cr.Width() - INFOBAR_SIZE ) / 2, cr.Height() / 2 ), pContext ) )
	{
		MessageBox( "Error setting up splitter frames!", "Init Error!",
			MB_OK | MB_ICONERROR );
		return FALSE;
	}

	// Front viewport
	if ( !m_viewportSplitter.CreateView( 0, 1, RUNTIME_CLASS(CFront),
		CSize( ( cr.Width() - INFOBAR_SIZE ) / 2, cr.Height() / 2 ), pContext ) )
	{
		MessageBox( "Error setting up splitter frames!", "Init Error!",
			MB_OK | MB_ICONERROR );
		return FALSE;
	}

	// Side viewport
	if ( !m_viewportSplitter.CreateView( 1, 0, RUNTIME_CLASS(CSide),
		CSize( ( cr.Width() - INFOBAR_SIZE ) / 2, cr.Height() / 2 ), pContext ) )
	{
		MessageBox( "Error setting up splitter frames!", "Init Error!",
			MB_OK | MB_ICONERROR );
		return FALSE;
	}

	// Perspective viewport
	if ( !m_viewportSplitter.CreateView( 1, 1, RUNTIME_CLASS(CPerspective),
		CSize( ( cr.Width() - INFOBAR_SIZE ) / 2, cr.Height() / 2 ), pContext ) )
	{
		MessageBox( "Error setting up splitter frames!", "Init Error!",
			MB_OK | MB_ICONERROR );
		return FALSE;
	}

	// The splitters have been intialized. This
	// flag is used to catch Resize messages
	// that occur before the splitters have been
	// created.
	m_initSplitters = TRUE;

	// We return TRUE rather than the parent method
	// as is suggested by the wizard. If the parent
	// method is called all our hard work is undone.

	return TRUE;
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);

	CRect cr;	// client rectangle -
				// used to calculate client sizes

	// Don't adjust the splitters if the application
	// is minimized or the splitters have not been
	// initialized.
	if ( m_initSplitters && nType != SIZE_MINIMIZED )
	{
		// Adjust the row/column info to compensate for
		// the new size

		m_mainSplitter.SetRowInfo( 0, cy, 0 );
		m_mainSplitter.SetColumnInfo( 0, cx - INFOBAR_SIZE, 0 );
		m_mainSplitter.SetColumnInfo( 1, INFOBAR_SIZE, 0 );

		// Get the client rectangle for the viewports
		m_viewportSplitter.GetClientRect( &cr );

		// Use the viewport client height rather than
		// the OnSize param cy to get an acurate look.
		m_viewportSplitter.SetRowInfo( 0, cr.Height() / 2, 0 );
		m_viewportSplitter.SetRowInfo( 1, cr.Height() / 2, 0 );
		m_viewportSplitter.SetColumnInfo( 0, ( cx - INFOBAR_SIZE ) / 2, 0 );
		m_viewportSplitter.SetColumnInfo( 1, ( cx - INFOBAR_SIZE ) / 2, 0 );

		// Apply our changes to the splitters
		m_mainSplitter.RecalcLayout();
		m_viewportSplitter.RecalcLayout();
	}
}
