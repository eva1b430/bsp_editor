#pragma once


// TopView 视图

class TopView : public CView
{
	DECLARE_DYNCREATE(TopView)

protected:
	TopView();           // 动态创建所使用的受保护的构造函数
	virtual ~TopView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

private:
	// 比例尺，对2D视图而言，即屏幕一像素等于世界空间多少长度单位
	float	m_Scale;
	float	m_GridSize;

	HWND	m_hWnd;
	HDC		m_hDC;
	HGLRC	m_hRC;

	// 绘制网格线
	void DrawGrid();
	// 绘制视图其他信息
	void DrawViewInfo();
	// 提供一个Activate方法，重新绑定视图句柄和openGL
	void Activate();
	bool IsActive();
public:
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};


