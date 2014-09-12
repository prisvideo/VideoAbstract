// ObjectViewDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "videotest2.h"
#include "ObjectViewDlg.h"
#include "afxdialogex.h"
#include "CvvImage.h"


// CObjectViewDlg �Ի���

IMPLEMENT_DYNAMIC(CObjectViewDlg, CDialog)

CObjectViewDlg::CObjectViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectViewDlg::IDD, pParent)
{
	m_pageSum=4;//��ʾ4��ͼ
	m_pageNum = 0;
	UserClick=FALSE;
	Generated=FALSE;
}

CObjectViewDlg::~CObjectViewDlg()
{

}

void CObjectViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_OBJECT1, ObjectPicture_1);
}


BEGIN_MESSAGE_MAP(CObjectViewDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OBJECT, &CObjectViewDlg::OnBnClickedButtonObject)
	ON_STN_CLICKED(IDC_STATIC_OBJECT1, &CObjectViewDlg::OnStnClickedStaticObject1)
	ON_BN_CLICKED(IDC_OBJECT_LEFT, &CObjectViewDlg::OnBnClickedObjectLeft)
	ON_BN_CLICKED(IDC_OBJECT_RIGHT, &CObjectViewDlg::OnBnClickedObjectRight)
	ON_STN_CLICKED(IDC_STATIC_OBJECT2, &CObjectViewDlg::OnStnClickedStaticObject2)
	ON_STN_CLICKED(IDC_STATIC_OBJECT3, &CObjectViewDlg::OnStnClickedStaticObject3)
	ON_STN_CLICKED(IDC_STATIC_OBJECT4, &CObjectViewDlg::OnStnClickedStaticObject4)
END_MESSAGE_MAP()


// CObjectViewDlg ��Ϣ�������

void CObjectViewDlg::ShowImage( IplImage* img, UINT ID ,CString WName)    // ID ��Picture Control�ؼ���ID��
{
	CWnd *m_pWnd = GetDlgItem(ID);
	CDC* pDC = GetDlgItem(ID) ->GetDC();        // �����ʾ�ؼ��� DC
	HDC hDC = pDC ->GetSafeHdc();                // ��ȡ HDC(�豸���) �����л�ͼ����
	DisplayFrame disPlayImage;//������Ƕ���Ŵ��ڵĶ���

	CRect rect;
	GetDlgItem(ID) ->GetClientRect( &rect );
	int rw = rect.right - rect.left;            // ���ͼƬ�ؼ��Ŀ�͸�
	int rh = rect.bottom - rect.top;
	int iw = img->width;                        // ��ȡͼƬ�Ŀ�͸�
	int ih = img->height;

	//float temp=max(iw/rw,ih/rh);
	//rw = (int)(iw/temp);		//Ӧ��ʾ�������Ŀ��
	//rh = (int)(ih/temp);	
	int tx = rect.left;
	int ty = rect.top;
	SetRect( rect, tx, ty, tx+rw, ty+rh );

	//disPlayImage.SetOpenCVWindow(m_pWnd,WName,
	//	rect.Width(), rect.Height());
	//disPlayImage.ShowPicture(WName, img);

	CvvImage cimg;
	cimg.CopyOf(img);
	cimg.DrawToHDC(hDC,&rect);
	ReleaseDC( pDC );
}


void CObjectViewDlg::OnBnClickedButtonObject()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//IplImage* image= NULL;
	//image = cvLoadImage("../00015_H/All.jpg",1);
	//ShowImage(image,IDC_STATIC_OBJECT1,"displayWindow_1");
	//ShowImage(image,IDC_STATIC_OBJECT2,"displayWindow_2");
	//ShowImage(image,IDC_STATIC_OBJECT3,"displayWindow_3");
	//ShowImage(image,IDC_STATIC_OBJECT4,"displayWindow_4");
	m_pageNum = 0;
	Generated=TRUE;
	DetectResult();
	DisplayPageSumImg();
}



void CObjectViewDlg::DisplayPageSumImg()
{
	CvCapture *capture = cvCreateFileCapture(oriPlayer.m_filePath);
	if (!capture)
		return;

	int num = m_pageSum;
	if (objDetectedInfos.size()/m_pageSum > m_pageNum)		//����ǰҳ��Ϊ���һҳ
		num = m_pageSum;									
	else
		num = objDetectedInfos.size()%m_pageSum;			//Ϊ���һҳ����ʾʣ���ͼ

	IplImage* image = NULL;
	CString nOldPara1,nOldPara2,nOldPara3,nOldPara4;
	for (int i = 0; i < m_pageSum; i++)
	{	
		///��ʾͼƬ
		if(i < num)											
		{
			///ȡ����Ƶ�и�Ŀ����ʼ֡�ŵ���һ֡
			cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,objDetectedInfos.at(m_pageSum * m_pageNum +i).MidFrameID);
			image = cvQueryFrame(capture);
			if(image == NULL)
				continue;
			///����һ֡�л�ROI������Ŀ��λ��
			CvRect rect = objDetectedInfos.at(m_pageNum * m_pageSum + i).roi;
			//cvRectangle(image,cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height),CV_RGB(200,200,0),5,8,0);
			cvSetImageROI(image,rect);

			///������ͼ����ʾ

			switch (i)
			{
			case 0:
				ShowImage(image,IDC_STATIC_OBJECT1,"displayWindow_1");
				nOldPara1.Format("%d",objDetectedInfos.at(m_pageNum * m_pageSum + i).nOldPara);
				GetDlgItem(IDC_STATIC_0)->SetWindowText(nOldPara1);
				break;
			case 1:
				ShowImage(image,IDC_STATIC_OBJECT2,"displayWindow_2");
				nOldPara2.Format("%d",objDetectedInfos.at(m_pageNum * m_pageSum + i).nOldPara);
				GetDlgItem(IDC_STATIC_1)->SetWindowText(nOldPara2);
				break;
			case 2:
				ShowImage(image,IDC_STATIC_OBJECT3,"displayWindow_3");
				nOldPara3.Format("%d",objDetectedInfos.at(m_pageNum * m_pageSum + i).nOldPara);
				GetDlgItem(IDC_STATIC_2)->SetWindowText(nOldPara3);
				break;
			case 3:
				ShowImage(image,IDC_STATIC_OBJECT4,"displayWindow_4");
				nOldPara4.Format("%d",objDetectedInfos.at(m_pageNum * m_pageSum + i).nOldPara);
				GetDlgItem(IDC_STATIC_3)->SetWindowText(nOldPara4);
				break;
			default:
				break;
			}
		}
		else											///��Ϊ���һҳ������closeup.bmp���
		{
			image = cvLoadImage("closeup.bmp",CV_LOAD_IMAGE_COLOR);
			switch (i)
			{
			case 0:
				ShowImage(image,IDC_STATIC_OBJECT1,"displayWindow_1");
				nOldPara1="";
				GetDlgItem(IDC_STATIC_0)->SetWindowText(nOldPara1);
				break;
			case 1:
				ShowImage(image,IDC_STATIC_OBJECT2,"displayWindow_2");
				nOldPara2="";
				GetDlgItem(IDC_STATIC_1)->SetWindowText(nOldPara2);
				break;
			case 2:
				ShowImage(image,IDC_STATIC_OBJECT3,"displayWindow_3");
				nOldPara3="";
				GetDlgItem(IDC_STATIC_2)->SetWindowText(nOldPara3);
				break;
			case 3:
				ShowImage(image,IDC_STATIC_OBJECT4,"displayWindow_4");
				nOldPara4="";
				GetDlgItem(IDC_STATIC_3)->SetWindowText(nOldPara4);
				break;
			default:
				break;
			}
		}

	}
	cvReleaseCapture(&capture);
}

void CObjectViewDlg::DetectResult()
{
	m_MysqlVideoHandle->GetObjectInfoFromObjectTable(&objDetectedInfos,videoPro->m_tableParams.CombineSegsTableName);
	m_MysqlVideoHandle->GetObjectOriMidFrameFromVideoFgTable(&objDetectedInfos,videoPro->m_tableParams.FGTraceTableName);
}






void CObjectViewDlg::OnStnClickedStaticObject1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Generated==TRUE)
	{	
		if(m_pageNum * m_pageSum + 0<objDetectedInfos.size())
		{
			OriFrame=objDetectedInfos.at(m_pageNum * m_pageSum + 0).OriFrameID;
			UserClick=TRUE;
		}
	}


}

void CObjectViewDlg::OnStnClickedStaticObject2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Generated==TRUE)
	{	
		if(m_pageNum * m_pageSum + 1<objDetectedInfos.size())
		{
			OriFrame=objDetectedInfos.at(m_pageNum * m_pageSum + 1).OriFrameID;
			UserClick=TRUE;
		}
	}
}


void CObjectViewDlg::OnStnClickedStaticObject3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Generated==TRUE)
	{
		if(m_pageNum * m_pageSum + 2<objDetectedInfos.size())
		{
			OriFrame=objDetectedInfos.at(m_pageNum * m_pageSum + 2).OriFrameID;
			UserClick=TRUE;
		}
	}
}


void CObjectViewDlg::OnStnClickedStaticObject4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Generated==TRUE)
	{	
		if(m_pageNum * m_pageSum + 2<objDetectedInfos.size())
		{
			OriFrame=objDetectedInfos.at(m_pageNum * m_pageSum + 3).OriFrameID;
			UserClick=TRUE;
		}
	}
}


void CObjectViewDlg::OnBnClickedObjectLeft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_pageNum > 0)
	{
		m_pageNum--;
		DisplayPageSumImg();
	}
}


void CObjectViewDlg::OnBnClickedObjectRight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DetectResult();			//����m_pageSumҪ��ʾ��object���objDetectedInfos
	if (m_pageNum < ceil(objDetectedInfos.size()/(float)m_pageSum) - 1)			
	{
		m_pageNum++; 
		DisplayPageSumImg();
	}
}


