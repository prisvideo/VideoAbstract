/**********************************************************************************
					Copyright:      BUPT PRIS LAB
					File name:      DisplayFrame.cpp
					Author:         Kang Jian
					Date:           2012-3-16

					Description:   	��ҪΪ��DisplayFrame���ʵ�֡�
									DisplayFrame����Ҫ�ṩ����MFC��
									OpenCV��ͼ����ʾ���ܡ�
***********************************************************************************/
#pragma  once
#include "stdafx.h"
#include "DisplayFrame.h"


/*********************************************
Function:      DisplayFrame    
Description:   DisplayFrame��Ĺ��캯��
Author:        Kang Jian
Date:          2012-3-19
Calls:         NULL 

Input:         NULL

Return:        NULL 

Others:        NULL
*********************************************/
DisplayFrame::DisplayFrame(void)
{
	lpbmih = new BITMAPINFO;
	lpbmih->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	
	lpbmih->bmiHeader.biWidth = 0;
	lpbmih->bmiHeader.biHeight = 0;
	lpbmih->bmiHeader.biPlanes = 1;
	lpbmih->bmiHeader.biBitCount = 24;
	lpbmih->bmiHeader.biCompression = BI_RGB;
	lpbmih->bmiHeader.biSizeImage = 0;
	lpbmih->bmiHeader.biXPelsPerMeter = 0;
	lpbmih->bmiHeader.biYPelsPerMeter = 0;
	lpbmih->bmiHeader.biClrUsed = 0;
	lpbmih->bmiHeader.biClrImportant = 0;
}

/*********************************************
Function:      ~DisplayFrame    
Description:   DisplayFrame�����������
Author:        Kang Jian
Date:          2012-3-19
Calls:         NULL 

Input:         NULL

Return:        NULL 

Others:        NULL
*********************************************/
DisplayFrame::~DisplayFrame(void)
{

}

/*********************************************
Function:      ShowPicture    
Description:   ʹ��OpenCV�еĺ����Ե���ͼƬ������ʾ
Author:        Kang Jian
Date:          2012-3-19
Calls:         NULL 

Input:         csWndName - Ŀ����ʾ���ڵ����ƣ���ʹ��OpenCV���д���ʱ������
			   pImg - ����ʾͼƬ��ָ��

Return:        NULL

Others:        NULL
*********************************************/
void DisplayFrame::ShowPicture(CString csWndName,IplImage *pImg)
{
	char *pWndName = csWndName.GetBuffer();
	cvShowImage(pWndName, pImg);

}

/******************** *************************
Function:      SetOpenCVWindow    
Description:   ��ʹ��OpenCV���ɵĴ���Ƕ��MFC���
Author:        Kang Jian
Date:          2012-3-20
Calls:         NULL 

Input:         pWnd - MFC����ʾ���ڵľ�� 
			   csWndName - OpenCV�����ɴ��ڵ����� ���ڻ�ȡ���
			   nTarWidth - Ŀ�괰�ڵĿ��
			   nTarHeight - Ŀ�괰�ڵĳ���

Return:        NULL

Others:        NULL
*********************************************/
void DisplayFrame::SetOpenCVWindow(CWnd *pWnd,CString csWndName,
								   int nTarWidth,int nTarHeight)
{
	char *pWndName = csWndName.GetBuffer();
	cvNamedWindow(pWndName, 0);
	HWND hWnd = (HWND)cvGetWindowHandle(pWndName);//��ʾ�ؼ�
	HWND hParent = ::GetParent(hWnd);//������
	::SetParent(hWnd,pWnd->m_hWnd);
	::ShowWindow(hParent,SW_HIDE);//������ʾ���ڿؼ�
	pWnd->SetWindowPos(NULL, 0, 0, nTarWidth, nTarHeight, 
						SWP_NOMOVE | SWP_NOZORDER);
	cvResizeWindow(pWndName, nTarWidth, nTarHeight);
	
}

void DisplayFrame::ShowPictureHolderBMP(IplImage *image, HDC hDC, CRect rec, CClientDC &dc)
{	
	lpbmih->bmiHeader.biWidth = image->width;				//��ʼ��λͼ��Ϣͷ��ͼƬ�ߺͿ�
	lpbmih->bmiHeader.biHeight = -image->height;			//��ֵ��ʾλͼ������(Ĭ���ǵ����ŵ�)

	BYTE *pBits;											//λͼ����ָ��
	HBITMAP hBitmap = CreateDIBSection(hDC, lpbmih, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);		//����λͼ���
	memcpy(pBits, image->imageData, image->imageSize);		//��IplImageͼƬ���ݿ�����bmp��������    
	ShowImg.CreateFromBitmap(hBitmap, NULL, FALSE);			//��λͼ���������CPictureHolder���� 	
	ShowImg.Render((CDC*)&dc, &rec, 0);						//��picture�ؼ���������(rec)��ʾͼƬ
	if(!DeleteObject(hBitmap))
		AfxMessageBox("ɾ��λͼ���ͷ���Դʧ�ܣ�");
}
