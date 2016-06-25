// ViewerDoc.cpp : implementation of the CViewerDoc class
//

#include "stdafx.h"
#include "Viewer.h"

#include "ViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewerDoc

IMPLEMENT_DYNCREATE(CViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CViewerDoc, CDocument)
	//{{AFX_MSG_MAP(CViewerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewerDoc construction/destruction

CViewerDoc::CViewerDoc()
{
	// No model has been loaded yet.
	m_currentModel = NULL;
}

CViewerDoc::~CViewerDoc()
{
	// If a model is currently loaded
	// delete it.
	if ( m_currentModel != NULL )
		delete m_currentModel;
}

BOOL CViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// If a model is currently loaded
	// delete it.
	if ( m_currentModel != NULL )
	{
		delete m_currentModel;
		m_currentModel = NULL;
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CViewerDoc serialization

void CViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// Load the MD3 file.

		if ( m_currentModel != NULL )
			delete m_currentModel;

		m_currentModel = new CMd3Model;
		if ( !LoadMd3( ar, m_currentModel ) )
		{
			MessageBox( NULL, "Not a valid md3 file!", "File Error!",
				MB_OK | MB_ICONERROR );
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CViewerDoc diagnostics

#ifdef _DEBUG
void CViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewerDoc commands
