
// MfcOpenCVView.h : CMfcOpenCVView ��Ľӿ�
//

#pragma once
#include "atltypes.h"


class CMfcOpenCVView : public CScrollView
{
protected: // �������л�����
	CMfcOpenCVView();
	DECLARE_DYNCREATE(CMfcOpenCVView)

// ����
public:
	CMfcOpenCVDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMfcOpenCVView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // MfcOpenCVView.cpp �еĵ��԰汾
inline CMfcOpenCVDoc* CMfcOpenCVView::GetDocument() const
   { return reinterpret_cast<CMfcOpenCVDoc*>(m_pDocument); }
#endif

