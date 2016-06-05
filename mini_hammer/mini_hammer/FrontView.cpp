// FrontView.cpp : 实现文件
//

#include "stdafx.h"
#include "mini_hammer.h"
#include "FrontView.h"
#include "memdc.h"
#include "misc/Cgdi.h"

// FrontView

IMPLEMENT_DYNCREATE(FrontView, CView)

FrontView::FrontView()
	: m_Scale(0.01f)
	, m_GridSize(0.1f)
{

}

FrontView::~FrontView()
{
}

BEGIN_MESSAGE_MAP(FrontView, CView)
END_MESSAGE_MAP()


// FrontView 绘图

void FrontView::OnDraw(CDC* pDC)
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


// FrontView 诊断

#ifdef _DEBUG
void FrontView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void FrontView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void FrontView::DrawGrid()
{
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

void FrontView::DrawViewInfo()
{
	gdi->TransparentText();
	gdi->TextAtPos(2, 0, "Front");
}

#endif
#endif //_DEBUG


// FrontView 消息处理程序
