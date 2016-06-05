#pragma once


// FrontView ��ͼ

class FrontView : public CView
{
	DECLARE_DYNCREATE(FrontView)

protected:
	FrontView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~FrontView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()


private:
	// �����ߣ���2D��ͼ���ԣ�����Ļһ���ص�������ռ���ٳ��ȵ�λ
	float m_Scale;
	float m_GridSize;

	// ����������
	void DrawGrid();
	// ������ͼ������Ϣ
	void DrawViewInfo();
};


