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
	float m_Scale;
	float m_GridSize;

	// 绘制网格线
	void DrawGrid();
	// 绘制视图其他信息
	void DrawViewInfo();
	// 创建cocos窗口
	BOOL CreateCocos2dXWindow();
public:
	virtual void OnInitialUpdate();
};


