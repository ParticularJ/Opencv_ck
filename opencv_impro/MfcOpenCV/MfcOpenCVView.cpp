
// MfcOpenCVView.cpp : CMfcOpenCVView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMfcOpenCVView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_COMMAND(ID_SCALE, &CMfcOpenCVView::OnScale)
END_MESSAGE_MAP()

// CMfcOpenCVView 构造/析构

CMfcOpenCVView::CMfcOpenCVView()
{
	// TODO: 在此处添加构造代码

}

CMfcOpenCVView::~CMfcOpenCVView()
{
}

BOOL CMfcOpenCVView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CMfcOpenCVView 绘制

void CMfcOpenCVView::OnDraw(CDC* pDC)
{
	CMfcOpenCVDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if ( !pDoc  || pDoc->m_matImage.empty() )
		return;

	// TODO: 在此处为本机数据添加绘制代码
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

	// TODO: 计算此视图的合计大小
	m_viewSize = GetDocument()->GetDocSize();
	SetScrollSizes(MM_TEXT, m_viewSize );
}


// CMfcOpenCVView 打印


void CMfcOpenCVView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMfcOpenCVView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMfcOpenCVView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMfcOpenCVView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CMfcOpenCVView 诊断

#ifdef _DEBUG
void CMfcOpenCVView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMfcOpenCVView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMfcOpenCVDoc* CMfcOpenCVView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcOpenCVDoc)));
	return (CMfcOpenCVDoc*)m_pDocument;
}
#endif //_DEBUG


// CMfcOpenCVView 消息处理程序

