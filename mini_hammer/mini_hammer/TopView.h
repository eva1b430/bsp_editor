#pragma once


// TopView ��ͼ

class TopView : public CView
{
	DECLARE_DYNCREATE(TopView)

protected:
	TopView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~TopView();

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
	float	m_Scale;
	float	m_GridSize;

	HWND	m_hWnd;
	HDC		m_hDC;
	HGLRC	m_hRC;

	// ����������
	void DrawGrid();
	// ������ͼ������Ϣ
	void DrawViewInfo();
	// �ṩһ��Activate���������°���ͼ�����openGL
	void Activate();
	bool IsActive();
public:
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};


