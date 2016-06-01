#pragma once

class Cmini_hammerView : public CView
{
protected: // create from serialization only
	Cmini_hammerView();
	DECLARE_DYNCREATE(Cmini_hammerView)

// Attributes
public:
	Cmini_hammerDoc* GetDocument() const;

	//创建Cocos2dX窗口  
	BOOL CreateCocos2dXWindow();
private:  
	//是否已经初始化  
	BOOL m_bInitCocos2dX;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate( );

// Implementation
public:
	virtual ~Cmini_hammerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnUpdateEnableGraph(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // debug version in mini_hammerView.cpp
inline Cmini_hammerDoc* Cmini_hammerView::GetDocument() const
   { return reinterpret_cast<Cmini_hammerDoc*>(m_pDocument); }
#endif

