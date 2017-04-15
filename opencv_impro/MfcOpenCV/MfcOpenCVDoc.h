
// MfcOpenCVDoc.h : CMfcOpenCVDoc 类的接口
//


#pragma once

#include "ImageProcess.h"

class CMfcOpenCVDoc : public CDocument
{
protected: // 仅从序列化创建
	CMfcOpenCVDoc();
	DECLARE_DYNCREATE(CMfcOpenCVDoc)

// 特性
public:
	Mat m_matImage;
	BITMAPINFO *m_pBmpinfo;
	CSize m_imgSize;
// 操作
public:
	CSize GetDocSize()const{ return m_imgSize; }
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMfcOpenCVDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
//	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSave();
//	afx_msg void OnFileOpen();
//	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
//	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnScale();
//	afx_msg void OnAddWatermark();
	afx_msg void OnOpen();
	afx_msg void OnUpdateImageProcess(CCmdUI *pCmdUI);
//	afx_msg void OnUpdateAddWatermark(CCmdUI *pCmdUI);
//	afx_msg void OnUpdateOpen(CCmdUI *pCmdUI);
//	afx_msg void OnUpdateCalculateDisplay(CCmdUI *pCmdUI);
//	afx_msg void OnCalculateDisplay();
//	afx_msg void OnUpdateBaseonRegion(CCmdUI *pCmdUI);
//	afx_msg void OnBaseonRegion();
//	afx_msg void OnUpdateBaseonBoundary(CCmdUI *pCmdUI);
//	afx_msg void OnBaseonBoundary();
	afx_msg void OnTranslate();
	afx_msg void OnUpdateTranslate(CCmdUI *pCmdUI);
	afx_msg void OnTranslateNew();
	afx_msg void OnUpdateTranslateNew(CCmdUI *pCmdUI);
	afx_msg void OnScaleNew();
	afx_msg void OnUpdateScaleNew(CCmdUI *pCmdUI);
	afx_msg void Onlotarote();
	afx_msg void OnUpdatelotarote(CCmdUI *pCmdUI);
	afx_msg void OnZhifangtu();
	afx_msg void OnFft();
	afx_msg void OnUpdateFft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLowPass(CCmdUI *pCmdUI);
	afx_msg void OnLowPass();
	afx_msg void OnUpdateMerge(CCmdUI *pCmdUI);
	afx_msg void OnMerge();
	afx_msg void OnUpdateLightness(CCmdUI *pCmdUI);
	afx_msg void OnLightness();
};
