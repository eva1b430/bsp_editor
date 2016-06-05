#pragma once


// SideView 视图

class SideView : public CView
{
	DECLARE_DYNCREATE(SideView)

protected:
	SideView();           // 动态创建所使用的受保护的构造函数
	virtual ~SideView();

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
	float m_Scale;
	float m_GridSize;

	// 绘制网格线
	void DrawGrid();
	// 绘制视图其他信息
	void DrawViewInfo();
};


