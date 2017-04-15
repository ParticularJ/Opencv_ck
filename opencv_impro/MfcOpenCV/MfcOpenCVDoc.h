
// MfcOpenCVDoc.h : CMfcOpenCVDoc ��Ľӿ�
//


#pragma once

#include "ImageProcess.h"

class CMfcOpenCVDoc : public CDocument
{
protected: // �������л�����
	CMfcOpenCVDoc();
	DECLARE_DYNCREATE(CMfcOpenCVDoc)

// ����
public:
	Mat m_matImage;
	BITMAPINFO *m_pBmpinfo;
	CSize m_imgSize;
// ����
public:
	CSize GetDocSize()const{ return m_imgSize; }
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMfcOpenCVDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
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
