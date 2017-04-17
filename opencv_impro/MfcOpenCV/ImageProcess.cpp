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

//  ����λͼ��Ϣ
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
		//  256 ɫλͼ
		for(int i=0;i<256;i++) 
		{                //  ���ûҶȵ�ɫ��
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

//ƽ�Ʊ任
void Translate(const Mat &src, Mat &dst, int tx, int ty)
{
	//imwrite("output\\1.bmp", dst);

	int rows = src.rows+abs(ty);
	int cols = src.cols +abs(tx);

	//ȷ��ÿ�е��ֽ�����4�ı���
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

//�����任
void Scale(const Mat &src, Mat &dst, double sx, double sy)
{
	int rows = src.rows * abs(sy);
	int cols = src.cols * abs(sx);

	//ȷ��ÿ�е��ֽ�����4�ı���
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

//��ת�任
void Rotate(const Mat &src, Mat &dst, double a)
{
	double angle = a *CV_PI / 180;
	float c = sin(angle), d = cos(angle);
	int rows = src.rows, cols = src.cols;
	//��ת���ͼ���С
	int rotate_cols = (fabs(c)*rows + fabs(d)*cols);
	int rotate_rows = (fabs(d)*rows + fabs(c)*cols);
	//�����µ�ͼƬ
	dst.create(rotate_rows, rotate_cols, CV_8UC1);
	/*	float map[6];
	map[0] = b;
	map[1] = a;
	map[3] = -map[1];
	map[4] = map[0];
	map[2] += (rotate_rows - rows) / 2;
	map[5] += (rotate_cols - cols) / 2;
	cout << map[0];*/
	Mat map_matrix = Mat(2, 3, CV_8UC1);
	CvPoint2D32f center = cvPoint2D32f(rows / 2, cols / 2);
	map_matrix = getRotationMatrix2D(center, a, 1.0);
	map_matrix.at<double>(0, 2) += (int)((rotate_rows - rows) / 2);
	map_matrix.at<double>(1, 2) += (int)((rotate_cols - cols) / 2);

	////��ͼ��������任  
	////CV_WARP_FILL_OUTLIERS - ����������ͼ������ء�  
	////�������������������ͼ��ı߽��⣬��ô���ǵ�ֵ�趨Ϊ fillval.  
	warpAffine(src, dst, map_matrix, Size(rotate_rows, rotate_cols), CV_WARP_FILL_OUTLIERS, BORDER_CONSTANT, cvScalarAll(255));
}

//ֱ��ͼ���⻯
void  Histogram(const Mat &src, Mat &dst)
{
	equalizeHist(src,dst);
}

//��ͨ�˲�
int LowPass(const Mat &src, Mat &dst, int radius)
{
	dst = src;

	return 0;
}

//DFT
void DFT(const Mat &src, Mat &dst) {
	int m = getOptimalDFTSize(src.rows);
	int n = getOptimalDFTSize(src.cols);
	//����ӵ�Ԫ�س�ʼ��Ϊ0
	Mat padded;
	copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));
	//Ϊʵ�����鲿����ռ�,
	Mat planes[] = { Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F) };
	Mat complexI;
	//2�����������ĸ���
	merge(planes, 2, complexI);
	dft(complexI, complexI);
	//����ͨ�����ֱ���ʵ�����鲿,���Ҽ����ֵ
	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	Mat magnitudeImage = planes[0];

	//���ж����߶�����
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);

	//���к��طֲ���������ȥ������Ϊ���鲿��
	//��&-2����������ż��
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols&-2, magnitudeImage.rows&-2));
	//��������ʹ��Զ��λ������
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy)); //top left
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));//top right
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));//bottom left
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));//bottom right
												 //�������ޣ�������ʾ
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//��һ����������ʾ
	normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX);
	Mat B;
	for (int x = 0; x < magnitudeImage.rows; x++) {
		for (int y = 0; y < magnitudeImage.cols; y++) {
			magnitudeImage.at<float>(y, x) = 255 * magnitudeImage.at<float>(y, x);
			//cout << magnitudeImage.at<float>(y, x) << endl;
			magnitudeImage.convertTo(B, CV_8UC1);
		}
	}
	dst = B;
}

//��
void Reverse(const Mat &src, Mat &dst) {
	dst = ~src;
}

//��ǿ�Աȶ�
void contrast(const Mat &src, Mat &dst) {
	dst = Mat::zeros(src.size(), src.type());
	int t1 = 20, t2 = 220;
	int s1 = 70, s2 = 180;
	for (int x = 0; x < src.rows; x++) {
		for (int y = 0; y < src.cols; y++) {
			if (src.at<uchar>(x, y) <= s1&&src.at<uchar>(x, y)>=0)
				dst.at<uchar>(x, y) = t1 / s1*src.at<uchar>(x, y);
			else if (src.at<uchar>(x, y) >= s2&&src.at<uchar>(x, y)<=src.rows)
				dst.at<uchar>(x, y) = (src.rows - t2) / (src.rows - s2)*(src.at<uchar>(x, y) - s2) + t2;
			else
				dst.at<uchar>(x, y) = (t2 - t1) / (s2 - s1)*(src.at<uchar>(x, y) - s1) + t1;
		}
	}
}

//��̬��Χѹ��
void compress(const Mat &src, Mat &dst) {
	dst = Mat::zeros(src.size(), src.type());
	for (int x = 0; x < src.rows; x++) {
		for (int y = 0; y < src.cols; y++) {
			dst.at<uchar>(x, y) =18* log(1 + src.at<uchar>(x, y));
		}
	}
}

//�Ҷ��з�
void gray(const Mat &src, Mat &dst) {
	int s1 = 120, s2 = 180;
	int t1 = 30, t2 = 220;
	dst = Mat::zeros(src.size(), src.type());
	for (int x = 0; x < src.rows; x++) {
		for (int y = 0; y < src.cols; y++) {
			if (src.at<uchar>(x, y) >= s1&&src.at<uchar>(x, y) <= s2)
				dst.at<uchar>(x, y) = t2;
			else
				dst.at<uchar>(x, y) = t1;
		}
	}
}

//�����˲�
void lyfilter(const Mat &src, Mat &dst) {
	dst = Mat::zeros(src.size(), src.type());
	Mat ker = (Mat_<float>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1)/9;
	filter2D(src, dst, src.depth(), ker);
}

//��Ȩ�˲�
void weight(const Mat &src, Mat &dst) {
	Mat ker = (Mat_<float>(3, 3) << 1, 2, 1, 2, 4, 2, 1, 2, 1)/16;
	filter2D(src, dst, src.depth(), ker);
}

//��˹�˲�
void gaussian(const Mat &src, Mat &dst) {
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
}

//��ֵ�˲�
void Median(const Mat &src, Mat &dst) {
	medianBlur(src, dst, 5);
}

//���ֵ�˲�
void maxfilter(const Mat &src, Mat &dst) {
	dst = Mat::zeros(src.size(), src.type());
	for (int x = 0; x < src.rows; x++) {
		for (int y = 0; y <src.cols; y++) {
			int max = 0;
			for (int k = x ; (k <=x+ 3) && (k<src.rows); k++)
				for (int m = y ; m <= (y + 3) && (m<src.cols); m++)
					if (src.at<uchar>(k, m) > max)
						max = src.at<uchar>(k, m);
			dst.at<uchar>(x, y) = max;
		}
	}
}

//��Сֵ�˲�
void minfilter(const Mat &src, Mat &dst) {
	dst = Mat::zeros(src.size(), src.type());
	for (int x = 0; x < src.rows; x++) {
		for (int y = 0; y <src.cols; y++) {
			int min = 255;
			for (int k = x  ; (k <= x + 3) && (k<src.rows); k++)
				for (int m = y ; m <= (y + 3) && (m<src.cols); m++)
					if (src.at<uchar>(k, m) < min)
						min = src.at<uchar>(k, m);
			dst.at<uchar>(x, y) = min;
		}
	}
}

//�е��˲�
void midfilter(const Mat &src, Mat &dst) {
	dst = Mat::zeros(src.size(), src.type());
	for (int x = 0; x < src.rows; x++) {
		for (int y = 0; y <src.cols; y++) {
			int max = 0, min = 255;
			for (int k = x; (k <= x + 3) && (k < src.rows); k++)
				for (int m = y; m <= (y + 3) && (m < src.cols); m++)
					if (src.at<uchar>(k, m) > max)
						max = src.at<uchar>(k, m);
					else if (src.at<uchar>(k, m) < min)
						min = src.at<uchar>(k, m);
			dst.at<uchar>(x, y) =  (max + min)/2;
		}
	}
}