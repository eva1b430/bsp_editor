// TopView.cpp : 实现文件
//

#include "stdafx.h"
#include "mini_hammer.h"
#include "TopView.h"
#include "memdc.h"
#include "misc/Cgdi.h"
#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "GameLayer.h"


using namespace cocos2d;
// TopView

IMPLEMENT_DYNCREATE(TopView, CView)

TopView::TopView()
	: m_Scale(0.01f)
	, m_GridSize(0.1f)
	, m_hWnd(NULL)
	, m_hDC(NULL)
	, m_hRC(NULL)
{

}

TopView::~TopView()
{
}

BEGIN_MESSAGE_MAP(TopView, CView)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// TopView 绘图

void TopView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	
	// TODO: 在此添加绘制代码
	CMemoryDC *pMemDC = NULL;
	pDC = pMemDC = new CMemoryDC(pDC);

	RECT rect;
	GetClientRect(&rect);
	int nWidth = rect.right;
	int nHeight = rect.bottom;

	pMemDC->FillSolidRect(0, 0, nWidth, nHeight, RGB(255, 255, 255));
	gdi->StartDrawing(pDC->GetSafeHdc());

	DrawGrid();
	DrawViewInfo();

	gdi->StopDrawing(pDC->GetSafeHdc());
	delete pMemDC;

	return ;
}


// TopView 诊断

#ifdef _DEBUG
void TopView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void TopView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void TopView::DrawGrid()
{
	return ;

	RECT rect;
	GetClientRect(&rect);
	int nWidth = rect.right;
	int nHeight = rect.bottom;

	// 绘制网格线
	CPoint pointCenter;
	pointCenter.x = nWidth / 2;
	pointCenter.y = nHeight / 2;
	// 半个视图的宽度
	long halfWidth = nWidth / 2;
	long halfHeight = nHeight / 2;

	// 绘制垂直网格
	gdi->GreyPen();

	// 单位网格投影在屏幕上的像素数
	float gpix = m_GridSize/m_Scale;

	int nHalfCount = halfWidth / gpix;
	for (int j = -nHalfCount; j <= nHalfCount; j++)
	{
		gdi->Line(Vector2D(pointCenter.x + j * gpix, 0), Vector2D(pointCenter.x + j * gpix, nHeight));
	}

	// 绘制水平网格
	nHalfCount = halfHeight / gpix;
	for (int j = -nHalfCount; j <= nHalfCount; j++)
	{
		gdi->Line(Vector2D(0, pointCenter.y + j * gpix), Vector2D(nWidth, pointCenter.y + j * gpix));
	}

	return ;
}

void TopView::DrawViewInfo()
{
	gdi->TransparentText();
	gdi->TextAtPos(2, 0, "Top");
}

// BOOL TopView::CreateCocos2dXWindow()
// {
// 	// 新建一个CRect变量获取窗口的客户区大小
// 	CRect   tClientRect;
// 	GetClientRect(&tClientRect);
// 	// 取得使用的OpenGL视窗
// 	
// 	
// 	return TRUE;
// }

#endif
#endif //_DEBUG


// TopView 消息处理程序

void TopView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	m_hWnd = GetSafeHwnd();
	m_hDC = ::GetDC(m_hWnd);
	//m_hDC = GetDC()->GetSafeHdc();
	//SetupPixelFormat(m_hDC);
	//SetupPalette();

	int pixelFormat;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size
		1,                          // version
		PFD_SUPPORT_OPENGL |        // OpenGL window
		PFD_DRAW_TO_WINDOW |        // render to window
		PFD_DOUBLEBUFFER,           // support double-buffering
		PFD_TYPE_RGBA,              // color type
		32,                         // preferred color depth
		0, 0, 0, 0, 0, 0,           // color bits (ignored)
		0,                          // no alpha buffer
		0,                          // alpha bits (ignored)
		0,                          // no accumulation buffer
		0, 0, 0, 0,                 // accum bits (ignored)
		24,                         // depth buffer
		8,                          // no stencil buffer
		0,                          // no auxiliary buffers
		PFD_MAIN_PLANE,             // main layer
		0,                          // reserved
		0, 0, 0,                    // no layer, visible, damage masks
	};

	pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, pixelFormat, &pfd);

	m_hRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hRC);

	GLenum GlewInitResult = glewInit();

	const char *gl_extensions = (const char*)glGetString(GL_EXTENSIONS);
	if (glGenFramebuffers == NULL)
	{
		if (strstr(gl_extensions, "ARB_framebuffer_object"))
		{
			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbuffer");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbuffer");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffers");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffers");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorage");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameteriv");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebuffer");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebuffer");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffers");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffers");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatus");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1D");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2D");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3D");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbuffer");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmap");
		}
		else
			if (strstr(gl_extensions, "EXT_framebuffer_object"))
			{
				glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbufferEXT");
				glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbufferEXT");
				glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffersEXT");
				glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffersEXT");
				glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorageEXT");
				glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameterivEXT");
				glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebufferEXT");
				glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebufferEXT");
				glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffersEXT");
				glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffersEXT");
				glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatusEXT");
				glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1DEXT");
				glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2DEXT");
				glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3DEXT");
				glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbufferEXT");
				glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
				glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmapEXT");
			}
			else
			{
				
			}
	}

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

	SetTimer(2, 1, NULL);

	// Destroy is Need
}

void TopView::Activate()
{
	wglMakeCurrent(m_hDC, m_hRC);
}

bool TopView::IsActive()
{
	return (wglGetCurrentDC()==m_hDC);
}


void TopView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CView::OnPaint()

	// 自己绘制逻辑
}

extern AppDelegate app;
void TopView::OnTimer(UINT_PTR nIDEvent)
{
	Activate();

	kmGLPushMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 绘制逻辑
	GameLayer* pLayer3D = app.getGameLayer();
	CCArray* pChildren = pLayer3D->getChildren();
	for (int i = 0; i < pChildren->count(); i++)
	{
		if (pChildren->objectAtIndex(i))
		{
			CCSprite* p3DSprite = dynamic_cast<CCSprite*>(pChildren->objectAtIndex(i));
			if (p3DSprite)
			{
				//p3DSprite->draw();
			}
		}
	}

	kmGLPopMatrix();

	// 交换缓冲区数据
	::SwapBuffers(m_hDC);

	//CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	//eglView->Activate();

	//CView::OnTimer(nIDEvent);
}


void TopView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	wglMakeCurrent(m_hDC, NULL);
	wglDeleteContext(m_hRC);
}
