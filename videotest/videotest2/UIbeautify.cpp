/**
*@file UIbeautify.cpp
*@brief ��ҪΪʹ�ý����������ܵĵ��ù�����Ķ��塣
*
*���ļ������UIbeautify�࣬�书������Ҫ������������ݣ������Ͱ�ť��������
*Ϊ�˽����Ч��������Ӧ����Ĵ�С����Ҫ�õ�ͼƬ�����죬�˴��õ���opencv��ͼƬ���������
*
*@author ���� lu peng&&chen dai wu ,����email��
*@version �汾��(0.0)
*@data 2012-8-21
*/

#include "stdafx.h"
#include "UIbeautify.h"


///@brief UIbeautify��Ĺ��캯��
///
///@param[in|out] NULL 
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL

UIbeautify::UIbeautify()
{
     bmi =new BITMAPINFO;
}

///@brief UIbeautify�����������
///
///@param[in|out] NULL 
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL

UIbeautify::~UIbeautify()
{
	delete bmi;
}

///@brief ���ر���ͼƬ
///
///@param[in] n_IDC ͼƬ��ID
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void UIbeautify::LoadBackgroundPic(int n_IDC)
{
	
	m_BitmapBackGround.LoadBitmap(n_IDC);///<����
	BITMAP bm;
	m_BitmapBackGround.GetObject(sizeof(BITMAP), &bm); ///<��ȡͼ��������Ϣ

}
///@brief ����������
///
///@param[in]  phwnd,��������pDC,�豸�����Ķ�����ࣻBitmapBackGroundStrech��������ı���ͼ
///@pre  NULL
///@return BOOL
///@retval NULL
///@post TRUE

BOOL UIbeautify::OnEraseBkgnd(HWND phwnd, CDC* pDC, CBitmap& BitmapBackGroundStrech)
{
	
	CRect rcClient;
	GetClientRect(phwnd, &rcClient); 

	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);

	dcMem.SelectObject(BitmapBackGroundStrech);///<Ϊ�豸����ѡ��һ������ȡ����ͼƬ

	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),&dcMem,0,0,SRCCOPY);///<��ȡ���ڿͻ��������꣨�������棩   

	dcMem.DeleteDC();
	return TRUE;

}

///@brief �����������һЩ���ò���
///
///@param[in]  phwnd,������
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void UIbeautify::PaintBackground(HWND phwnd)
{

	CRect rect;
	CWnd* pWnd = CWnd::GetDesktopWindow();            ///<��ȡ���ڿͻ��������꣨�������棩   ��ʾ������Ϊ��������
	pWnd->GetClientRect(rect);
	MoveWindow(phwnd, rect.left, rect.top, rect.Width(), rect.Height(), TRUE);

	CRgn m_rgn;                                      ///<��ȡ���ڿͻ��������꣨�������棩   ��Բ�Ǿ���
	GetClientRect(phwnd, &rect);
	m_rgn.CreateRoundRectRgn(rect.left,rect.top,rect.right+1,rect.bottom+1,5,5); 
	SetWindowRgn(phwnd, m_rgn,TRUE);

}

///@brief ʵ�ְ�ť�������Լ���λ
///
///@param[in]  BtName ��������Button��ť;n_IDB1,��ť���ص�ԭͼ��ӦResource����;n_IDB2,��ť���صĵ�2��ͼ��ӦResource����;LeftRatio,TopRatio,RightRatio,BottomRatio,��ť����ڽ������������λ�ñ���
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void UIbeautify::LoadButtonBitmaps(CButtonBeautify &BtName,
					               int n_IDB1,              int n_IDB2,
					               double LeftRatio,         double TopRatio,   double RightRatio,     double BottomRatio)
{

	CBitmap Bitmap1,Bitmap2;

	Bitmap1.LoadBitmap(n_IDB1);

	CBitmap* BitmapNew1=CBitmapResize(Bitmap1,rcDeskRect.Width()*(RightRatio-LeftRatio),
									rcDeskRect.Height()*(BottomRatio-TopRatio));

	Bitmap2.LoadBitmap(n_IDB2);
	CBitmap* BitmapNew2=CBitmapResize(Bitmap2,rcDeskRect.Width()*(RightRatio-LeftRatio),
									rcDeskRect.Height()*(BottomRatio-TopRatio));

	BtName.MoveWindow(CRect(rcDeskRect.Width()*LeftRatio,rcDeskRect.Height()*TopRatio,
									(int)(rcDeskRect.Width()*LeftRatio)+(int)(rcDeskRect.Width()*(RightRatio-LeftRatio)),(int)(rcDeskRect.Height()*TopRatio)+(int)(rcDeskRect.Height()*(BottomRatio-TopRatio)))); 
	BtName.SetBitmaps(*BitmapNew1,*BitmapNew2,*BitmapNew2);

	delete BitmapNew1;
	delete BitmapNew2;

}

///@brief ʵ�ְ�ť�������Լ���λ
///
///@param[in]  BtName ��������Button��ť;n_IDB1,��ť���ص�ԭͼ��ӦResource����;n_IDB2,��ť���صĵ�2��ͼ��ӦResource����;LeftRatio,TopRatio,RightRatio,BottomRatio,��ť����ڽ������������λ�ñ���
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void UIbeautify::LoadButtonBitmaps(CButtonBeautify &BtName,
								   int n_IDB1,              int n_IDB2,
								   double LeftRatio,         double TopRatio,   double RightRatio,     double BottomRatio,
								   int width,               int height)
{

	CBitmap Bitmap1,Bitmap2;

	Bitmap1.LoadBitmap(n_IDB1);

    CBitmap* Bitmapstrech1=CBitmapResize(Bitmap1,width,height);
	CBitmap* BitmapNew1=CBitmapResize(*Bitmapstrech1,rcDeskRect.Width()*(RightRatio-LeftRatio),
		rcDeskRect.Height()*(BottomRatio-TopRatio));

	Bitmap2.LoadBitmap(n_IDB2);
	CBitmap* Bitmapstrech2=CBitmapResize(Bitmap2,width,height);
	CBitmap* BitmapNew2=CBitmapResize(*Bitmapstrech2,rcDeskRect.Width()*(RightRatio-LeftRatio),
		rcDeskRect.Height()*(BottomRatio-TopRatio));


	BtName.MoveWindow(CRect(rcDeskRect.Width()*LeftRatio,rcDeskRect.Height()*TopRatio,
		(int)(rcDeskRect.Width()*LeftRatio)+(int)(rcDeskRect.Width()*(RightRatio-LeftRatio)),(int)(rcDeskRect.Height()*TopRatio)+(int)(rcDeskRect.Height()*(BottomRatio-TopRatio)))); 
	BtName.SetBitmaps(*BitmapNew1,*BitmapNew2,*BitmapNew2);

	delete Bitmapstrech1;
	delete Bitmapstrech2;
	delete BitmapNew1;
	delete BitmapNew2;

}

///@brief ʵ��CBitmap����ͼƬ��С�任
///
///@param[in]  Bmp,ԭCBitmap����ͼƬ��width,height,���ĳ��͸�
///@pre  NULL
///@return CBitmap*
///@retval CBitmap*
///@post NULL
CBitmap* UIbeautify::CBitmapResize(CBitmap& Bmp,int width,int height)
{
	IplImage * IpmageResize=CBitmapToIplImage(Bmp);
	IplImage *dst = 0; ///<��ȡ���ڿͻ��������꣨�������棩   Ŀ��ͼ��ָ��
	CvSize dst_cvsize; ///<��ȡ���ڿͻ��������꣨�������棩   Ŀ��ͼ��ߴ�

	dst_cvsize.width = width; ///<Ŀ��ͼ��Ŀ�ΪԴͼ����scale��
	dst_cvsize.height = height; ///<Ŀ��ͼ��ĸ�ΪԴͼ��ߵ�scale��

	dst = cvCreateImage( dst_cvsize, IpmageResize->depth, IpmageResize->nChannels); ///<����Ŀ��ͼ��
	cvResize(IpmageResize, dst, CV_INTER_LINEAR); ///<����Դͼ��Ŀ��ͼ��
	CBitmap* BmpNew=IplImageToCBitmap(dst);

	cvReleaseImage(&IpmageResize);
	cvReleaseImage(&dst);

	return BmpNew;

}


///@brief ʵ��CBitmapתIplImage
///
///@param[in]  Bmp,ԭCBitmap����ͼƬ
///@pre  NULL
///@return  IplImage *
///@retval IplImage *
///@post NULL
IplImage * UIbeautify::CBitmapToIplImage(CBitmap& Bmp)
{
	HBITMAP hBmp = HBITMAP(Bmp);///<��CBitmapת��ΪHBITMAP
	BITMAP bmp;
	Bmp.GetBitmap(&bmp);///<���λͼ��Ϣ

	int depth,nChannels;
	if(bmp.bmBitsPixel == 1)///<�õ�ͼ����Ⱥ�ͨ����
	{
		depth=IPL_DEPTH_1U;
		nChannels=1;
	}
	else
	{
		depth=IPL_DEPTH_8U;  
		nChannels=bmp.bmBitsPixel/8;
	}

	IplImage* pImg = cvCreateImage(cvSize(bmp.bmWidth,bmp.bmHeight), depth, nChannels); ///<����ͼ��      
	BYTE *pBuffer = new BYTE[bmp.bmHeight*bmp.bmWidth*nChannels]; ///<����������   
	GetBitmapBits(hBmp, bmp.bmHeight*bmp.bmWidth*nChannels, pBuffer); ///<��λͼ��Ϣ���Ƶ�������
	memcpy(pImg->imageData, pBuffer, bmp.bmHeight*bmp.bmWidth*nChannels);///<����������Ϣ���Ƹ�IplImage,���ǳɹ���CBitmap�õ���IplImage���͵�ͼƬpImg.

	delete [] pBuffer;
	return pImg;

}


///@brief ʵ��IplImage ת CBitmap
///
///@param[in] *pImage,ԭIplImage *����ͼƬ
///@pre  NULL
///@return  CBitmap * 
///@retval CBitmap * 
///@post NULL
CBitmap * UIbeautify:: IplImageToCBitmap(const IplImage *pImage)
{
	if( pImage && pImage->depth == IPL_DEPTH_8U )
	{
		CBitmap *pBitmap=new CBitmap;
		HDC hDC = GetDC(NULL);
		
		int bmp_w = pImage->width, bmp_h = pImage->height;
		FillBitmapInfo(bmi,bmp_w,bmp_h,pImage->depth*pImage->nChannels,pImage->origin);
	    char *pBits=NULL;
		HBITMAP hBitmap=::CreateDIBSection(hDC,bmi,DIB_RGB_COLORS,(void**)&pBits,NULL,0);
		memcpy(pBits,pImage->imageData,pImage->imageSize);
		
		pBitmap->Attach(hBitmap);

        ReleaseDC(NULL,hDC);
		return pBitmap;
	}
	else
		return NULL;
}

///@brief ʵ���½�BitmapͼƬʱ���Bitmap��Ϣ
///
///@param[in] BITMAPINFO* bmiͼƬ��Ϣ, int width��, int height��, int bppͼƬ����bit, int originԭʼ��ֵ
///@pre  NULL
///@return  NULL
///@retval NULL
///@post NULL
void UIbeautify::FillBitmapInfo(LPBITMAPINFO bmi, int width, int height, int bpp, int origin) 
{ 

	bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	//��ʼ��λͼ��Ϣͷ
	bmi->bmiHeader.biWidth = width;
	bmi->bmiHeader.biHeight = origin ? abs(height) : -abs(height);
	bmi->bmiHeader.biPlanes = 1;
	bmi->bmiHeader.biBitCount = (unsigned short)bpp;
	bmi->bmiHeader.biCompression = BI_RGB;
	bmi->bmiHeader.biSizeImage = 0;
	bmi->bmiHeader.biXPelsPerMeter = 0;
	bmi->bmiHeader.biYPelsPerMeter = 0;
	bmi->bmiHeader.biClrUsed = 0;
	bmi->bmiHeader.biClrImportant = 0;

}

