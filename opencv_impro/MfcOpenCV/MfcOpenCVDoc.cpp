
// MfcOpenCVDoc.cpp : CMfcOpenCVDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MfcOpenCV.h"
#endif

#include "MfcOpenCVDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMfcOpenCVDoc

IMPLEMENT_DYNCREATE(CMfcOpenCVDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcOpenCVDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE_AS, &CMfcOpenCVDoc::OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE, &CMfcOpenCVDoc::OnFileSave)
ON_COMMAND(ID_SCALE, &CMfcOpenCVDoc::OnScale)
ON_UPDATE_COMMAND_UI(ID_SCALE, &CMfcOpenCVDoc::OnUpdateImageProcess)

ON_COMMAND(ID_TRANSLATE, &CMfcOpenCVDoc::OnTranslate)
ON_UPDATE_COMMAND_UI(ID_TRANSLATE, &CMfcOpenCVDoc::OnUpdateTranslate)
ON_COMMAND(ID_TRANSLATE_NEW, &CMfcOpenCVDoc::OnTranslateNew)
ON_UPDATE_COMMAND_UI(ID_TRANSLATE_NEW, &CMfcOpenCVDoc::OnUpdateTranslateNew)
ON_COMMAND(ID_SCALE_NEW, &CMfcOpenCVDoc::OnScaleNew)
ON_UPDATE_COMMAND_UI(ID_SCALE_NEW, &CMfcOpenCVDoc::OnUpdateScaleNew)
ON_COMMAND(ID_lotarote, &CMfcOpenCVDoc::Onlotarote)
ON_UPDATE_COMMAND_UI(ID_lotarote, &CMfcOpenCVDoc::OnUpdatelotarote)
ON_COMMAND(ID_ZHIFANGTU, &CMfcOpenCVDoc::OnZhifangtu)
ON_COMMAND(ID_FFT, &CMfcOpenCVDoc::OnFft)
ON_UPDATE_COMMAND_UI(ID_FFT, &CMfcOpenCVDoc::OnUpdateFft)
ON_UPDATE_COMMAND_UI(ID_LOW_PASS, &CMfcOpenCVDoc::OnUpdateLowPass)
ON_COMMAND(ID_LOW_PASS, &CMfcOpenCVDoc::OnLowPass)
ON_UPDATE_COMMAND_UI(ID_MERGE, &CMfcOpenCVDoc::OnUpdateMerge)
ON_COMMAND(ID_MERGE, &CMfcOpenCVDoc::OnMerge)
ON_UPDATE_COMMAND_UI(ID_LIGHTNESS, &CMfcOpenCVDoc::OnUpdateLightness)
ON_COMMAND(ID_LIGHTNESS, &CMfcOpenCVDoc::OnLightness)
END_MESSAGE_MAP()


// CMfcOpenCVDoc ����/����

CMfcOpenCVDoc::CMfcOpenCVDoc()
{
	m_pBmpinfo =NULL;
	m_imgSize.cx = m_imgSize.cy = 100;
}

CMfcOpenCVDoc::~CMfcOpenCVDoc()
{
	if( m_pBmpinfo )
	{
		delete m_pBmpinfo;
		m_pBmpinfo = NULL;
	}
}

BOOL CMfcOpenCVDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMfcOpenCVDoc ���л�

void CMfcOpenCVDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

	}
//	else
//	{
//		if( !m_matImage.empty() )
//		{
//			m_matImage.release();
//		}
//		string strFile;
//#ifdef _UNICODE
//		wstring wstrFile( ar.m_strFileName );
//		UnicodeToANSI( wstrFile, strFile );
//#else
//		strFile = (const char *)(LPCTSTR)GetPathName();
//#endif
//
//		Mat img = imread( strFile, 0 );
//		//imshow("original", img);
//		//waitKey();
//		if( !img.empty() )
//		{
//			//ȷ��ÿ�е��ֽ�����4�ı���
//			if( ( img.cols * img.elemSize() % 4 ) != 0 )
//			{
//				int bytesPerRow = (img.cols * img.elemSize()*8+31)/32*4;
//				int newWidth = bytesPerRow / img.elemSize();
//				int deltaBytes = bytesPerRow - img.cols * img.elemSize();
//				m_matImage.create( img.rows, newWidth, img.type() );
//				for(int y=0; y<img.rows; y++)
//				{
//					memcpy(m_matImage.data + y*bytesPerRow, img.data + y*img.step[0], img.step[0]);
//					memset(m_matImage.data + y*bytesPerRow + img.step[0], 0, deltaBytes );
//				}
//			}
//			else
//				m_matImage = img;
//
//			if( m_pBmpinfo )
//			{
//				delete m_pBmpinfo;
//				m_pBmpinfo = NULL;
//			}
//			m_pBmpinfo = CreateBitmapInfo( m_matImage );
//
//			m_imgSize.SetSize( m_matImage.cols, m_matImage.rows );
//
//			SetPathName( ar.m_strFileName );
//			UpdateAllViews(NULL);
//		}
//	
//	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMfcOpenCVDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMfcOpenCVDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMfcOpenCVDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMfcOpenCVDoc ���

#ifdef _DEBUG
void CMfcOpenCVDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcOpenCVDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMfcOpenCVDoc ����
void CMfcOpenCVDoc::OnFileSaveAs()
{
	//CString strFullPath = GetPathName(), strPath, strName;
	//int nIndex = strFullPath.ReverseFind(_T('\\'));
	//if( nIndex <= 0 )
	//	return;

	//strPath = strFullPath.Left( nIndex );
	//strName = strFullPath.Right( strFullPath.GetLength() - nIndex - 1  );

	//CFileDialog dlg(FALSE,_T(".bmp"), strName, 	
	//	OFN_OVERWRITEPROMPT,
	//	_T("λͼ��*.bmp)|*.bmp||") );
	//dlg.m_ofn.lpstrInitialDir = strPath;

	//if( IDOK != dlg.DoModal() )
	//	return;

	if( m_matImage.empty() )
		return;

	CDocument::OnFileSaveAs();

	CString strFullPath = GetPathName();
	
	string strFile;
#ifdef _UNICODE
	wstring wstrFile( (LPCTSTR)strFullPath );
	UnicodeToANSI( wstrFile, strFile );
#else
	strFile = (const char *)(LPCTSTR)strFullPath;
#endif
	imwrite(strFile,m_matImage);
}


void CMfcOpenCVDoc::OnFileSave()
{
	if( m_matImage.empty() )
		return;

	CDocument::OnFileSave();

	CString strFullPath = GetPathName();

	string strFile;
#ifdef _UNICODE
	wstring wstrFile( (LPCTSTR)strFullPath );
	UnicodeToANSI( wstrFile, strFile );
#else
	strFile = (const char *)(LPCTSTR)strFullPath;
#endif
	imwrite(strFile,m_matImage);
}

BOOL CMfcOpenCVDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������
	if( !m_matImage.empty() )
		m_matImage.release();

	string strFile;
#ifdef _UNICODE
	wstring wstrFile( lpszPathName );
	UnicodeToANSI( wstrFile, strFile );
#else
	strFile = (const char *)(LPCTSTR)lpszPathName;
#endif

	Mat img = imread( strFile, 0 ); //1ת����3ͨ����ɫͼ��0ת���ɻҶ�ͼ��-1��ʾ����ͼƬԭ���ĸ�ʽ
	if( img.empty() )
		return FALSE;

	//ȷ��ÿ�е��ֽ�����4�ı���
	if( ( img.cols * img.elemSize() % 4 ) != 0 )
	{
		int bytesPerRow = (img.cols * img.elemSize()*8+31)/32*4;
		int newWidth = bytesPerRow / img.elemSize();
		int deltaBytes = bytesPerRow - img.cols * img.elemSize();
		m_matImage.create( img.rows, newWidth, img.type() );
		for(int y=0; y<img.rows; y++)
		{
			memcpy(m_matImage.data + y*bytesPerRow, img.data + y*img.step[0], img.step[0]);
			memset(m_matImage.data + y*bytesPerRow + img.step[0], 0, deltaBytes );
		}
	}
	else
		m_matImage = img;

	if( m_pBmpinfo )
	{
		delete m_pBmpinfo;
		m_pBmpinfo = NULL;
	}
	m_pBmpinfo = CreateBitmapInfo( m_matImage );

	m_imgSize.SetSize( m_matImage.cols, m_matImage.rows );

	SetPathName( lpszPathName );
	UpdateAllViews(NULL);

	return TRUE;
}


void CMfcOpenCVDoc::OnScale()
{
	// TODO: �ڴ���������������

}

void CMfcOpenCVDoc::OnUpdateImageProcess(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( !m_matImage.empty() );
}

void CMfcOpenCVDoc::OnTranslate()
{
	


	// TODO: Add your command handler code here
	Mat newImage;
	
	Translate(m_matImage, newImage, 50, 50);

	m_matImage = newImage;
	if (m_pBmpinfo)
	{
		delete[]m_pBmpinfo;
		m_pBmpinfo = NULL;
	}
	m_pBmpinfo = CreateBitmapInfo(m_matImage);
	m_imgSize.SetSize(m_matImage.cols, m_matImage.rows);
	UpdateAllViews(NULL);
}


void CMfcOpenCVDoc::OnUpdateTranslate(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_matImage.empty());
}


void CMfcOpenCVDoc::OnTranslateNew()
{
	// TODO: Add your command handler code here
	AfxMessageBox(L"just a test");
}


void CMfcOpenCVDoc::OnUpdateTranslateNew(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_matImage.empty());
}


void CMfcOpenCVDoc::OnScaleNew()
{
	Mat newImage;

	Scale(m_matImage, newImage, 2, 2);

	m_matImage = newImage;
	if (m_pBmpinfo)
	{
		delete[]m_pBmpinfo;
		m_pBmpinfo = NULL;
	}
	m_pBmpinfo = CreateBitmapInfo(m_matImage);
	m_imgSize.SetSize(m_matImage.cols, m_matImage.rows);
	UpdateAllViews(NULL);
}


void CMfcOpenCVDoc::OnUpdateScaleNew(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_matImage.empty());
}

void CMfcOpenCVDoc::Onlotarote()
{
	Mat newImage;

	Rotate(m_matImage, newImage, 30);

	m_matImage = newImage;
	if (m_pBmpinfo)
	{
		delete[]m_pBmpinfo;
		m_pBmpinfo = NULL;
	}
	m_pBmpinfo = CreateBitmapInfo(m_matImage);
	m_imgSize.SetSize(m_matImage.cols, m_matImage.rows);
	UpdateAllViews(NULL);
}


void CMfcOpenCVDoc::OnUpdatelotarote(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_matImage.empty());
}


void CMfcOpenCVDoc::OnZhifangtu()
{
	// TODO: Add your command handler code here
	Mat newImage;

	Histogram(m_matImage, newImage);

	m_matImage = newImage;
	if (m_pBmpinfo)
	{
		delete[]m_pBmpinfo;
		m_pBmpinfo = NULL;
	}
	m_pBmpinfo = CreateBitmapInfo(m_matImage);
	m_imgSize.SetSize(m_matImage.cols, m_matImage.rows);
	UpdateAllViews(NULL);
}

void CMfcOpenCVDoc::OnFft()
{
	Mat newImage;

	//Foueier(  );

	m_matImage = newImage;
	if (m_pBmpinfo)
	{
		delete[]m_pBmpinfo;
		m_pBmpinfo = NULL;
	}
	m_pBmpinfo = CreateBitmapInfo(m_matImage);
	m_imgSize.SetSize(m_matImage.cols, m_matImage.rows);
	UpdateAllViews(NULL);
}


void CMfcOpenCVDoc::OnUpdateFft(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_matImage.empty());
}


void CMfcOpenCVDoc::OnUpdateLowPass(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_matImage.empty());
}


void CMfcOpenCVDoc::OnLowPass()
{
	BeginWaitCursor();
	Mat newImage;

	LowPass(m_matImage, newImage, 10);

	m_matImage = newImage;
	if (m_pBmpinfo)
	{
		delete[]m_pBmpinfo;
		m_pBmpinfo = NULL;
	}
	m_pBmpinfo = CreateBitmapInfo(m_matImage);
	m_imgSize.SetSize(m_matImage.cols, m_matImage.rows);
	UpdateAllViews(NULL);
	EndWaitCursor();
}


void CMfcOpenCVDoc::OnUpdateMerge(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_matImage.empty());
}


void CMfcOpenCVDoc::OnMerge()
{
	//ѡ��logoͼƬ�ļ�
	CFileDialog dlg(TRUE, 0, 0, 6UL, _T("ͼ���ļ�(*.bmp,*.jpg,*.png,*.gif,*.tiff)|*.bmp;*.jpg;*.png;*.gif;*.tiff||"));
	if (IDOK != dlg.DoModal())
		return;

	CString strFileName = dlg.GetPathName();
	string strFile;

#ifdef _UNICODE
	wstring wstrFile(strFileName);
	UnicodeToANSI(wstrFile, strFile);
#else
	strFile = (const char *)(LPCTSTR)strFileName;
#endif

	//��ȡͼ���ļ�
	Mat logo = imread(strFile, 0);

	//MerageImage(  )

	UpdateAllViews(NULL);
}


void CMfcOpenCVDoc::OnUpdateLightness(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_matImage.empty());
}

//���ȱ仯
void CMfcOpenCVDoc::OnLightness()
{
	CFileDialog dlg(TRUE, 0, 0, 6UL, _T("ͼ���ļ�(*.bmp,*.jpg,*.png,*.gif,*.tiff)|*.bmp;*.jpg;*.png;*.gif;*.tiff||"));
	if (IDOK != dlg.DoModal())
		return;

	CString strFileName = dlg.GetPathName();
	string strFile;

#ifdef _UNICODE
	wstring wstrFile(strFileName);
	UnicodeToANSI(wstrFile, strFile);
#else
	strFile = (const char *)(LPCTSTR)strFileName;
#endif

	BeginWaitCursor();

	Mat clrImg = imread(strFile, 1);

	//.....��ɫͼ����

	m_matImage = clrImg;
	if (m_pBmpinfo)
	{
		delete[]m_pBmpinfo;
		m_pBmpinfo = NULL;
	}
	m_pBmpinfo = CreateBitmapInfo(m_matImage);
	m_imgSize.SetSize(m_matImage.cols, m_matImage.rows);
	UpdateAllViews(NULL);
	EndWaitCursor();
}
