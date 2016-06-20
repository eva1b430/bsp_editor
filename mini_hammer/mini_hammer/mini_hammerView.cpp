#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "mini_hammer.h"
#endif

#include "mini_hammerDoc.h"
#include "mini_hammerView.h"

#include "cocos2d.h"
#include "CCEGLView.h"
#include "CCApplication.h"
#include "AppDelegate.h"
#include "GameLayer.h"

using namespace cocos2d;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmini_hammerView

IMPLEMENT_DYNCREATE(Cmini_hammerView, CView)

BEGIN_MESSAGE_MAP(Cmini_hammerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cmini_hammerView::OnFilePrintPreview)

	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//ON_UPDATE_COMMAND_UI(ID_ENABLE_GRAPH, &Cmini_hammerView::OnUpdateEnableGraph)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// Cmini_hammerView construction/destruction

AppDelegate app;
Cmini_hammerView::Cmini_hammerView()
	: m_bInitCocos2dX(FALSE)
{
	// TODO: add construction code here

	//AppDelegate app;
	//CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	//eglView->setViewName("HelloCpp");
	//eglView->setFrameSize(400, 300);
	//CCApplication::sharedApplication()->run(true);	
}

Cmini_hammerView::~Cmini_hammerView()
{
	
}

BOOL Cmini_hammerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cmini_hammerView drawing

 void Cmini_hammerView::OnDraw(CDC* pDC)
 {
	 Cmini_hammerDoc* pDoc = GetDocument();
	 ASSERT_VALID(pDoc);
	 if (!pDoc)
		 return;

	 // TODO: add draw code for native data here

	 /*if (m_pPathFinder)
	 {
	 CMemoryDC *pMemDC = NULL;
	 pDC = pMemDC = new CMemoryDC(pDC);

	 RECT rect;
	 GetClientRect(&rect);
	 int nWidth = rect.right;
	 int nHeight = rect.bottom;

	 pMemDC->FillSolidRect(0, 0, nWidth, nHeight, RGB(255, 255, 255));
	 gdi->StartDrawing(pDC->GetSafeHdc());
	 m_pPathFinder->Render();
	 gdi->StopDrawing(pDC->GetSafeHdc());

	 delete pMemDC;

	 return ;
	 }*/
 }


// Cmini_hammerView printing


void Cmini_hammerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cmini_hammerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cmini_hammerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cmini_hammerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Cmini_hammerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cmini_hammerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cmini_hammerView diagnostics

#ifdef _DEBUG
void Cmini_hammerView::AssertValid() const
{
	CView::AssertValid();
}

void Cmini_hammerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cmini_hammerDoc* Cmini_hammerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmini_hammerDoc)));
	return (Cmini_hammerDoc*)m_pDocument;
}

 void Cmini_hammerView::OnPaint()
 {
 	CPaintDC dc(this); 
 	OnPrepareDC(&dc); 
 	OnDraw(&dc); //调用了OnDraw
 }

void Cmini_hammerView::OnInitialUpdate()
{
	// 
	CreateCocos2dXWindow();
}

#endif //_DEBUG


// Cmini_hammerView message handlers


void Cmini_hammerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonUp(nFlags, point);
}


void Cmini_hammerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags == MK_LBUTTON)
	{
		
	}

	CView::OnMouseMove(nFlags, point);
}

BOOL Cmini_hammerView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	// 双缓冲
	return CView::OnEraseBkgnd(pDC);

	//return TRUE;
}

BOOL Cmini_hammerView::CreateCocos2dXWindow()
{
	if (m_bInitCocos2dX)
	{
		return TRUE;
	}

	// 新建一个CRect变量获取窗口的客户区大小
	CRect   tClientRect;
	GetClientRect(&tClientRect);
	// 取得使用的OpenGL视窗
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	// 以指定的客户区大小创建视窗，这里我们对setFrameSize增加了参数3以传入当前控件的窗口句柄
	eglView->setFrameSize(tClientRect.Width(), tClientRect.Height(), GetSafeHwnd());
	// 调用程序的运行函数，增加参数bool型变量控制是否进行消息循环。因为MFC控件本身有自已的消息响应处理
	// 如果不改动的话，这里就会进入死循环
	cocos2d::CCApplication::sharedApplication()->run(false);
	
	// 这里将变量设置为TRUE
	m_bInitCocos2dX = TRUE;

	SetTimer(1, 1, NULL);

	return TRUE;
}


LRESULT Cmini_hammerView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_bInitCocos2dX)  
	{  
		//CCEGLView::sharedOpenGLView()->WindowProc(message, wParam, lParam);  
	}

	return CView::WindowProc(message, wParam, lParam);
}


void Cmini_hammerView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//我们写一个renderWorld函数代表Cocos2d-x的世界渲染  
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->Activate();

	glPolygonMode(GL_NONE, GL_LINE);

	cocos2d::CCApplication::sharedApplication()->renderWorld();
	//CWnd::OnTimer(nIDEvent);

	CView::OnTimer(nIDEvent);
}


void Cmini_hammerView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	if(TRUE == m_bInitCocos2dX)
	{  
		//退出将m_bInitCocos2dX设为FALSE
		m_bInitCocos2dX = FALSE;
		//释放定时器资源  
		KillTimer(1);

		//调用显示设备单件实例对象的end函数  
		CCDirector::sharedDirector()->end();
		//处理一次下一帧，必须调用.  
		CCDirector::sharedDirector()->mainLoop();

		CWnd::OnDestroy();
	}
}


void Cmini_hammerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(TRUE == m_bInitCocos2dX)
	{  
		CRect   tClientRect;
		GetClientRect(&tClientRect);
		//重新设置窗口大小及投影矩阵  
		CCEGLView::sharedOpenGLView()->resize(tClientRect.Width(),tClientRect.Height());
		CCDirector::sharedDirector()->reshapeProjection(CCSizeMake(tClientRect.Width(),tClientRect.Height()));

		if (m_bInitCocos2dX)
		{
			CCDirector::sharedDirector()->getRunningScene()->setContentSize(CCSizeMake(tClientRect.Width(),tClientRect.Height()));
			app.getGameLayer()->setContentSize(CCSizeMake(tClientRect.Width(),tClientRect.Height()));
		}

	}
}


void Cmini_hammerView::OnFileSave()
{
	// TODO: Add your command handler code here
}


void Cmini_hammerView::OnFileOpen()
{
	// TODO: Add your command handler code here
}