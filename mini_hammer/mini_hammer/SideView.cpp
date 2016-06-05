// SideView.cpp : ʵ���ļ�
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


// SideView ��ͼ

void SideView::OnDraw(CDC* pDC)
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


// SideView ���

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

void SideView::DrawViewInfo()
{
	gdi->TransparentText();
	gdi->TextAtPos(2, 0, "Side");
}

#endif
#endif //_DEBUG


// SideView ��Ϣ�������
