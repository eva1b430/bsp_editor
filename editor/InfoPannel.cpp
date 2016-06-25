// InfoPannel.cpp : implementation file
//

#include "stdafx.h"
#include "Viewer.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoPannel

IMPLEMENT_DYNCREATE(CInfoPannel, CFormView)

CInfoPannel::CInfoPannel()
	: CFormView(CInfoPannel::IDD)
{
	// This is where we initialize default values
	// for dialog controls and some member
	// variables.

	// UpdateData( FALSE ) is called during
	// CFormView::OnInitialUpdate() so we
	// don't have to.

	//{{AFX_DATA_INIT(CInfoPannel)
	m_lowerLeft = SIDEVIEWPORT;
	m_lowerRight = PERSPVIEWPORT;
	m_upperLeft = TOPVIEWPORT;
	m_upperRight = FRONTVIEWPORT;
	//}}AFX_DATA_INIT
}

CInfoPannel::~CInfoPannel()
{
}

void CInfoPannel::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoPannel)
	DDX_CBIndex(pDX, IDC_LOWERLEFT, m_lowerLeft);
	DDX_CBIndex(pDX, IDC_LOWERRIGHT, m_lowerRight);
	DDX_CBIndex(pDX, IDC_UPPERLEFT, m_upperLeft);
	DDX_CBIndex(pDX, IDC_UPPERRIGHT, m_upperRight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoPannel, CFormView)
	//{{AFX_MSG_MAP(CInfoPannel)
	ON_CBN_SELCHANGE(IDC_UPPERLEFT, OnEditchangeUpperleft)
	ON_CBN_SELCHANGE(IDC_UPPERRIGHT, OnEditchangeUpperright)
	ON_CBN_SELCHANGE(IDC_LOWERLEFT, OnEditchangeLowerleft)
	ON_CBN_SELCHANGE(IDC_LOWERRIGHT, OnEditchangeLowerright)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoPannel diagnostics

#ifdef _DEBUG
void CInfoPannel::AssertValid() const
{
	CFormView::AssertValid();
}

void CInfoPannel::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInfoPannel message handlers

// Message handlers for the info bar
// controls. Viewport dropdowns.

void CInfoPannel::OnEditchangeUpperleft() 
{
	// Automatically update the form view
	// member variables with the values from
	// their associated controls.
	UpdateData( TRUE );

	// Delete the view in the appropriate
	// splitter pane and create a new one
	// based on the dropdown selection.

	CRuntimeClass *newViewClass;
	CRect cr;		// client rectange

	switch ( m_upperLeft )
	{
		case FRONTVIEWPORT:
			newViewClass = RUNTIME_CLASS( CFront );
			break;
		case TOPVIEWPORT:
			newViewClass = RUNTIME_CLASS( CTop );
			break;
		case SIDEVIEWPORT:
			newViewClass = RUNTIME_CLASS( CSide );
			break;
		case PERSPVIEWPORT:
			newViewClass = RUNTIME_CLASS( CPerspective );
			break;
	}

	m_viewports->GetClientRect( &cr );
	m_viewports->DeleteView( 0, 0 );
	m_viewports->CreateView( 0, 0, newViewClass,
		CSize( cr.Width() / 2, cr.Height() / 2 ), NULL );

	// Add the new view to the application's
	// document.
	GetDocument()->AddView( (CView*)(m_viewports->GetPane( 0, 0 )) );

	// Recalculate the splitter window so the
	// changes are displayed.
	m_viewports->RecalcLayout();
}

void CInfoPannel::OnEditchangeUpperright() 
{
	// Automatically update the form view
	// member variables with the values from
	// their associated controls.
	UpdateData( TRUE );

	// Delete the view in the appropriate
	// splitter pane and create a new one
	// based on the dropdown selection.

	CRuntimeClass *newViewClass;
	CRect cr;		// client rectange

	switch ( m_upperRight )
	{
		case FRONTVIEWPORT:
			newViewClass = RUNTIME_CLASS( CFront );
			break;
		case TOPVIEWPORT:
			newViewClass = RUNTIME_CLASS( CTop );
			break;
		case SIDEVIEWPORT:
			newViewClass = RUNTIME_CLASS( CSide );
			break;
		case PERSPVIEWPORT:
			newViewClass = RUNTIME_CLASS( CPerspective );
			break;
	}

	m_viewports->GetClientRect( &cr );
	m_viewports->DeleteView( 0, 1 );
	m_viewports->CreateView( 0, 1, newViewClass,
		CSize( cr.Width() / 2, cr.Height() / 2 ), NULL );

	// Add the new view to the application's
	// document.
	GetDocument()->AddView( (CView*)(m_viewports->GetPane( 0, 1 )) );

	// Recalculate the splitter window so the
	// changes are displayed.
	m_viewports->RecalcLayout();
}

void CInfoPannel::OnEditchangeLowerleft() 
{
	// Automatically update the form view
	// member variables with the values from
	// their associated controls.
	UpdateData( TRUE );

	// Delete the view in the appropriate
	// splitter pane and create a new one
	// based on the dropdown selection.

	CRuntimeClass *newViewClass;
	CRect cr;		// client rectange

	switch ( m_lowerLeft )
	{
		case FRONTVIEWPORT:
			newViewClass = RUNTIME_CLASS( CFront );
			break;
		case TOPVIEWPORT:
			newViewClass = RUNTIME_CLASS( CTop );
			break;
		case SIDEVIEWPORT:
			newViewClass = RUNTIME_CLASS( CSide );
			break;
		case PERSPVIEWPORT:
			newViewClass = RUNTIME_CLASS( CPerspective );
			break;
	}

	m_viewports->GetClientRect( &cr );
	m_viewports->DeleteView( 1, 0 );
	m_viewports->CreateView( 1, 0, newViewClass,
		CSize( cr.Width() / 2, cr.Height() / 2 ), NULL );

	// Add the new view to the application's
	// document.
	GetDocument()->AddView( (CView*)(m_viewports->GetPane( 1, 0 )) );

	// Recalculate the splitter window so the
	// changes are displayed.
	m_viewports->RecalcLayout();
}

void CInfoPannel::OnEditchangeLowerright() 
{
	// Automatically update the form view
	// member variables with the values from
	// their associated controls.
	UpdateData( TRUE );

	// Delete the view in the appropriate
	// splitter pane and create a new one
	// based on the dropdown selection.

	CRuntimeClass *newViewClass;
	CRect cr;		// client rectange

	switch ( m_lowerRight )
	{
		case FRONTVIEWPORT:
			newViewClass = RUNTIME_CLASS( CFront );
			break;
		case TOPVIEWPORT:
			newViewClass = RUNTIME_CLASS( CTop );
			break;
		case SIDEVIEWPORT:
			newViewClass = RUNTIME_CLASS( CSide );
			break;
		case PERSPVIEWPORT:
			newViewClass = RUNTIME_CLASS( CPerspective );
			break;
	}

	m_viewports->GetClientRect( &cr );
	m_viewports->DeleteView( 1, 1 );
	m_viewports->CreateView( 1, 1, newViewClass,
		CSize( cr.Width() / 2, cr.Height() / 2 ), NULL );

	// Add the new view to the application's
	// document.
	GetDocument()->AddView( (CView*)(m_viewports->GetPane( 1, 1 )) );

	// Recalculate the splitter window so the
	// changes are displayed.
	m_viewports->RecalcLayout();
}

void CInfoPannel::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// Automatically update the form view
	// controls with the values from the
	// member variables. Useful for cases
	// when you change the member variable
	// in the code and want the change to
	// be reflected in the control.
	UpdateData( FALSE );
}
