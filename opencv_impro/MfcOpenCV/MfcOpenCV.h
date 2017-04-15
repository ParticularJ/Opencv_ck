
// MfcOpenCV.h : MfcOpenCV 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMfcOpenCVApp:
// 有关此类的实现，请参阅 MfcOpenCV.cpp
//

class CMfcOpenCVApp : public CWinAppEx
{
public:
	CMfcOpenCVApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
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
