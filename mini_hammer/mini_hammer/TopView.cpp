// TopView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mini_hammer.h"
#include "TopView.h"
#include "memdc.h"
#include "misc/Cgdi.h"


// TopView

IMPLEMENT_DYNCREATE(TopView, CView)

TopView::TopView()
	: m_Scale(0.01f)
	, m_GridSize(0.1f)
{

}

TopView::~TopView()
{
}

BEGIN_MESSAGE_MAP(TopView, CView)
END_MESSAGE_MAP()


// TopView ��ͼ

void TopView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	
	// TODO: �ڴ���ӻ��ƴ���
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


// TopView ���

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
	RECT rect;
	GetClientRect(&rect);
	int nWidth = rect.right;
	int nHeight = rect.bottom;

	// ����������
	CPoint pointCenter;
	pointCenter.x = nWidth / 2;
	pointCenter.y = nHeight / 2;
	// �����ͼ�Ŀ��
	long halfWidth = nWidth / 2;
	long halfHeight = nHeight / 2;

	// ���ƴ�ֱ����
	gdi->GreyPen();

	// ��λ����ͶӰ����Ļ�ϵ�������
	float gpix = m_GridSize/m_Scale;

	int nHalfCount = halfWidth / gpix;
	for (int j = -nHalfCount; j <= nHalfCount; j++)
	{
		gdi->Line(Vector2D(pointCenter.x + j * gpix, 0), Vector2D(pointCenter.x + j * gpix, nHeight));
	}

	// ����ˮƽ����
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

#endif
#endif //_DEBUG


// TopView ��Ϣ�������
