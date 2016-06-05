// SideView.cpp : 实现文件
//

#include "stdafx.h"
#include "mini_hammer.h"
#include "SideView.h"
#include "memdc.h"
#include "misc/Cgdi.h"

// SideView

IMPLEMENT_DYNCREATE(SideView, CView)

SideView::SideView()
	: m_Scale(0.01f)
	, m_GridSize(0.1f)
{

}

SideView::~SideView()
{
}

BEGIN_MESSAGE_MAP(SideView, CView)
END_MESSAGE_MAP()


// SideView 绘图

void SideView::OnDraw(CDC* pDC)
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


// SideView 诊断

#ifdef _DEBUG
void SideView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void SideView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void SideView::DrawGrid()
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

void SideView::DrawViewInfo()
{
	gdi->TransparentText();
	gdi->TextAtPos(2, 0, "Side");
}

#endif
#endif //_DEBUG


// SideView 消息处理程序
