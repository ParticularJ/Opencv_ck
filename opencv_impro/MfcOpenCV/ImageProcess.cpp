#include "stdafx.h"
#include "ImageProcess.h"

//ANSI to Unicode
void ANSIToUnicode( const string& strSource, wstring &wstrTarget )
{
	int  len = 0;
	len = strSource.length();
	int  unicodeLen = ::MultiByteToWideChar( CP_ACP,
		0,
		strSource.c_str(),
		-1,
		NULL,
		0 );  
	wchar_t *  pUnicode;  
	pUnicode = new  wchar_t[unicodeLen+1];  
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_ACP,
		0,
		strSource.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen );  
	wstrTarget = ( wchar_t* )pUnicode;
	delete  pUnicode; 
}

//  Unicode to ANSI
void UnicodeToANSI( const wstring& wstrSource, string &strTarget )
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte( CP_ACP,
		0,
		wstrSource.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL );
	pElementText = new char[iTextLen + 1];
	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	::WideCharToMultiByte( CP_ACP,
		0,
		wstrSource.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL );

	strTarget = pElementText;
	delete[] pElementText;
}

//  建立位图信息
BITMAPINFO *CreateBitmapInfo(Mat &workImg)    
{                                          
	BITMAPINFOHEADER BIH={40,1,1,1,8,0,0,0,0,0,0};
	int bits, colors;
	BYTE *pBmpInfo = NULL;
	if(CV_8UC3==workImg.type())
	{
		bits=24;
	}
	else if(CV_8UC1==workImg.type())
	{
		bits=8;
	}   
	if(bits>8)
		colors=0;
	else
		colors=1<<bits;  
	BIH.biWidth   = workImg.cols;    
	BIH.biHeight  = workImg.rows;
	BIH.biBitCount= (BYTE) bits;  
	BIH.biClrUsed = colors;
	if(bits==8)
	{             
		pBmpInfo = new BYTE[sizeof(BITMAPINFOHEADER)+ 1024];
		memcpy( pBmpInfo, &BIH, sizeof(BITMAPINFOHEADER) );
		RGBQUAD  *ColorTab = (RGBQUAD*) ( pBmpInfo+sizeof(BITMAPINFOHEADER) );
		//  256 色位图
		for(int i=0;i<256;i++) 
		{                //  设置灰度调色板
			ColorTab[i].rgbRed=ColorTab[i].rgbGreen=ColorTab[i].rgbBlue=(BYTE)i;
			ColorTab[i].rgbReserved = 0;
		}
//		memcpy( pBmpInfo+sizeof(BITMAPINFOHEADER), ColorTab, 1024 );
	}
	else if( bits == 24 )
	{
		pBmpInfo = new BYTE[sizeof(BITMAPINFOHEADER)];
		memcpy( pBmpInfo, &BIH, sizeof(BITMAPINFOHEADER) );
	}

	return (BITMAPINFO *)pBmpInfo;
}

//平移变换
void Translate(const Mat &src, Mat &dst, int tx, int ty)
{
	//imwrite("output\\1.bmp", dst);

	int rows = src.rows+abs(ty);
	int cols = src.cols +abs(tx);

	//确保每行的字节数是4的倍数
	if ((cols % 4) != 0)
	{
		cols = (cols * 8 + 31) / 32 * 4;
	}

	dst.create(rows, cols, CV_8UC1);

	for(int y=0; y<dst.rows; y++)
		for(int x=0; x<dst.cols; x++)
		{
			int x0 = x - tx;
			int y0 = y - ty;
			if( x0 >= 0 && y0 >= 0 && x0 < src.cols && y0 < src.rows )
				dst.at<uchar>(y,x) = src.at<uchar>( y0, x0 );
			else
				dst.at<uchar>(y,x) = 255;
		}
}

//放缩变换
void Scale(const Mat &src, Mat &dst, double sx, double sy)
{
	int rows = src.rows * abs(sy);
	int cols = src.cols * abs(sx);

	//确保每行的字节数是4的倍数
	if ((cols % 4) != 0)
	{
		cols = (cols * 8 + 31) / 32 * 4;
	}

	dst.create(rows, cols, CV_8UC1);

	for (int y = 0; y<dst.rows; y++)
	for (int x = 0; x<dst.cols; x++)
	{
		int x0 = x / sx;
		int y0 = y / sy;
		if (x0 >= 0 && y0 >= 0 && x0 < src.cols && y0 < src.rows)
			dst.at<uchar>(y, x) = src.at<uchar>(y0, x0);
		else
			dst.at<uchar>(y, x) = 255;
	}
}

void Rotate(const Mat &src, Mat &dst, double a)
{
	dst = src;
}

//直方图均衡化
void  Histogram(const Mat &src, Mat &dst)
{
	dst = src;
}

//低通滤波
int LowPass(const Mat &src, Mat &dst, int radius)
{
	dst = src;

	return 0;
}

