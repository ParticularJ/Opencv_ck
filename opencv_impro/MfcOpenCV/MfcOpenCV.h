
// MfcOpenCV.h : MfcOpenCV Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMfcOpenCVApp:
// �йش����ʵ�֣������ MfcOpenCV.cpp
//

class CMfcOpenCVApp : public CWinAppEx
{
public:
	CMfcOpenCVApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnFileOpen();
//	afx_msg void OnFileSave();
//	afx_msg void OnFileSaveAs();
//	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
//	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
//	afx_msg void OnFileOpen();
};

extern CMfcOpenCVApp theApp;
