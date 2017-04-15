
// MfcOpenCVView.cpp : CMfcOpenCVView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MfcOpenCV.h"
#endif

#include "MfcOpenCVDoc.h"
#include "MfcOpenCVView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcOpenCVView

IMPLEMENT_DYNCREATE(CMfcOpenCVView, CScrollView)

BEGIN_MESSAGE_MAP(CMfcOpenCVView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMfcOpenCVView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_COMMAND(ID_SCALE, &CMfcOpenCVView::OnScale)
END_MESSAGE_MAP()

// CMfcOpenCVView ����/����

CMfcOpenCVView::CMfcOpenCVView()
{
	// TODO: �ڴ˴���ӹ������

}

CMfcOpenCVView::~CMfcOpenCVView()
{
}

BOOL CMfcOpenCVView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CMfcOpenCVView ����

void CMfcOpenCVView::OnDraw(CDC* pDC)
{
	CMfcOpenCVDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if ( !pDoc  || pDoc->m_matImage.empty() )
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if( m_viewSize != pDoc->GetDocSize() )
	{
		m_viewSize = pDoc->GetDocSize();
		SetScrollSizes(MM_TEXT, m_viewSize);
	}

	const Mat &img = pDoc->m_matImage;
	::StretchDIBits( pDC->GetSafeHdc(), 0, 0, img.cols, img.rows,
		0,img.rows,img.cols, -img.rows, img.data, pDoc->m_pBmpinfo, DIB_RGB_COLORS,SRCCOPY);

	//CDC memDC;
	//memDC.CreateCompatibleDC( pDC );
	//CBitmap bitmap;
	//bitmap.CreateCompatibleBitmap( pDC, img.cols, img.rows );
	//CBitmap* oldBitmap = (CBitmap*)memDC.SelectObject( bitmap );

	//::StretchDIBits( memDC.GetSafeHdc(), 0, 0, img.cols, img.rows,
	//	0,img.rows,img.cols, -img.rows, img.data, pDoc->m_pBmpinfo, DIB_RGB_COLORS,SRCCOPY);
	//pDC->BitBlt(0,0, img.cols, img.rows, &memDC, 0,0, SRCCOPY);
}

void CMfcOpenCVView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: �������ͼ�ĺϼƴ�С
	m_viewSize = GetDocument()->GetDocSize();
	SetScrollSizes(MM_TEXT, m_viewSize );
}


// CMfcOpenCVView ��ӡ


void CMfcOpenCVView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMfcOpenCVView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMfcOpenCVView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMfcOpenCVView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMfcOpenCVView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMfcOpenCVView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMfcOpenCVView ���

#ifdef _DEBUG
void CMfcOpenCVView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMfcOpenCVView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMfcOpenCVDoc* CMfcOpenCVView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcOpenCVDoc)));
	return (CMfcOpenCVDoc*)m_pDocument;
}
#endif //_DEBUG


// CMfcOpenCVView ��Ϣ�������

