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