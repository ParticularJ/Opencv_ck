
// MfcOpenCVView.h : CMfcOpenCVView 类的接口
//

#pragma once
#include "atltypes.h"


class CMfcOpenCVView : public CScrollView
{
protected: // 仅从序列化创建
	CMfcOpenCVView();
	DECLARE_DYNCREATE(CMfcOpenCVView)

// 特性
public:
	CMfcOpenCVDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMfcOpenCVView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	CSize m_viewSize;
public:
//	afx_msg void OnScale();
};

#ifndef _DEBUG  // MfcOpenCVView.cpp 中的调试版本
inline CMfcOpenCVDoc* CMfcOpenCVView::GetDocument() const
   { return reinterpret_cast<CMfcOpenCVDoc*>(m_pDocument); }
#endif

