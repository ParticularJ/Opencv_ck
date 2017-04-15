//image process api

#pragma  once
#include "opencv/include/opencv2/opencv.hpp"
#include <string>
#include <complex>

#ifdef  UNICODE
	#define tstring wstring
#else
	#define tstring string
#endif

using namespace std;
using namespace cv;

#define WIDTHBYTES(i)	((i+31)/32*4)
#define PI 3.1415926


#ifdef _DEBUG
#pragma comment(lib,"opencv/lib/opencv_imgproc231d.lib")
#pragma comment (lib, "opencv/lib/opencv_core231d.lib")
#pragma comment (lib, "opencv/lib/opencv_highgui231d.lib")
#else
#pragma comment(lib,"opencv/lib/opencv_imgproc231.lib")
#pragma comment (lib, "opencv/lib/opencv_core231.lib")
#pragma comment (lib, "opencv/lib/opencv_highgui231.lib")
#endif

//ANSI to Unicode
void ANSIToUnicode( const string& strSource, wstring& wstrTarget );

//Unicode to ANSI
void UnicodeToANSI( const wstring& wstrSource, string &strTarget );

//  ����λͼ��Ϣ
BITMAPINFO *CreateBitmapInfo(Mat &workImg);   


//ƽ�Ʊ任
void Translate(const Mat &src, Mat &dst, int tx, int ty);

//�����任
void Scale(const Mat &src, Mat &dst, double sx, double sy);

//��ת�任
void Rotate(const Mat &src, Mat &dst, double a);

//ֱ��ͼ���⻯
void  Histogram(const Mat &src, Mat &dst);

//��ͨ�˲�
int LowPass(const Mat &src, Mat &dst, int radius);

