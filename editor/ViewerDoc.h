// ViewerDoc.h : interface of the CViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWERDOC_H__E263D93A_AC22_4BBF_8FA1_9D4A1C1E95A7__INCLUDED_)
#define AFX_VIEWERDOC_H__E263D93A_AC22_4BBF_8FA1_9D4A1C1E95A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Model.h"

class CViewerDoc : public CDocument
{
protected: // create from serialization only
	CViewerDoc();
	DECLARE_DYNCREATE(CViewerDoc)

// Attributes
public:
	CMd3Model *m_currentModel;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CViewerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWERDOC_H__E263D93A_AC22_4BBF_8FA1_9D4A1C1E95A7__INCLUDED_)
