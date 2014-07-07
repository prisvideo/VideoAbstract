/**
*@file  VideoSeg.cpp
*@brief ʵ����Ƶ�ָ��ںϹ��ܣ�������ƵժҪ��
*
*��Ҫģ�飺��Ƶ��������Ƶ�ָ������ȡ��ǰ����ȡ������Ƶ�ںϣ�ժҪ���ɣ���
*
*
*@author ���� lu ying&&zhang nan nan ,����email��
*@version �汾��(0.0)
*@data 2014-6-4
*/
#include "stdafx.h"
#include <afxwin.h>
#include <afxmt.h>
#include "VideoSeg.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
///@brief CVideo��ı�׼���캯��
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL

CVideo::CVideo()
{///������ʼ��
	m_IfDoneSeg       = false;///<��Ƶ�ָ���ɱ�־λ�÷�
	m_IfDoneFus       = false;///<��Ƶ�ں���ɱ�־λ�÷�
	SegFrame_Count    = 0;    ///<�ָ���Ƶ��֡������
	FusFrame_Count    = 0;    ///<�ں���Ƶ��֡������

	m_ProcessingSpeed = 0.0;  ///<�����������

	///��Ƶorͼ��ָ����Ϣ�ÿ�
	m_pCapture        = NULL;   
	m_pGaussBGModel   = NULL;
	m_pGaussParams    = NULL;

	m_pCont           = NULL;
	m_pStor           = NULL;

	m_pOriFrame       = NULL;
	m_pProcessFrame   = NULL;
//	m_pResizeFrame    = NULL;
	m_pGrayFrame      = NULL;
//	m_pGrayResizeFrame= NULL;
	m_pBGFrame        = NULL;
	for (int i=0;i<10;i++)
	{
		m_pBGFinal[i] = NULL;
	}
	m_pNewFrame       = NULL;

	m_FrameMat       = NULL;      
	m_BGMat          = NULL;       
	m_pGrayFrameMat   = NULL;          
	m_pGrayBGMat      = NULL;            
	m_pGrayFGMat      = NULL;          

	m_pVideoWriter4seg    = NULL;
	m_pVideoWriter4fusion = NULL;

	m_MysqlSegHandle = new CDataMySql;///<�½����ݿ����Ӿ��
}

///@brief CVideo��ı�׼��������
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL

CVideo::~CVideo()
{///�ͷ��ڴ�
	if (m_pProcessFrame!=NULL)
		cvReleaseImage(&m_pProcessFrame);
	if (m_pBGFrame!=NULL)
		cvReleaseImage(&m_pBGFrame);
	for (int i=0;i<10;i++)
	{
		if (m_pBGFinal[i]!=NULL)
			cvReleaseImage(&m_pBGFinal[i]);
	}
//	if (m_pResizeFrame!=NULL)
//		cvReleaseImage(&m_pResizeFrame);
	if (m_pGrayFrame!=NULL)
		cvReleaseImage(&m_pGrayFrame);
//	if (m_pGrayResizeFrame!=NULL)
//		cvReleaseImage(&m_pGrayResizeFrame);
	if (m_pNewFrame!=NULL)
		cvReleaseImage(&m_pNewFrame);
	if (m_pCapture!=NULL)
		cvReleaseCapture(&m_pCapture);
	if (m_pVideoWriter4seg!=NULL)
		cvReleaseVideoWriter(&m_pVideoWriter4seg);
	if (m_pVideoWriter4fusion!=NULL)
		cvReleaseVideoWriter(&m_pVideoWriter4fusion);
	if (m_pStor!=NULL)
		cvReleaseMemStorage(&m_pStor);
	if (m_pGaussBGModel!=NULL)
		cvReleaseBGStatModel((CvBGStatModel**)&m_pGaussBGModel);

//	if (m_pFrameMat!=NULL)
//		cvReleaseMat(&m_pFrameMat);
//	if (m_pBGMat!=NULL)
//		cvReleaseMat(&m_pBGMat);
	if (m_pGrayFrameMat!=NULL)
		cvReleaseMat(&m_pGrayFrameMat);
	if (m_pGrayBGMat!=NULL)
		cvReleaseMat(&m_pGrayBGMat);
	if (m_pGrayFGMat!=NULL)
		cvReleaseMat(&m_pGrayFGMat);
	


	delete m_pGaussParams;	///<ɾ����˹ģ�Ͳ���ָ��
	delete m_MysqlSegHandle;///<ɾ�����ݿ����Ӿ��

	_CrtDumpMemoryLeaks();
}
///@brief CVideo��Ŀ�ʼ������
/// 
///@param[in] ��Ƶ·��
///@pre  NULL
///@return NULL
///@retval int
///@post NULL
int CVideo::DoProcessing(const char* pFilePath)
{
	m_strFilePath = pFilePath;///<��ȡ��Ƶ·��
	AfxBeginThread(BeginSegProcess,this);///<������Ƶ�����߳�
	return 0;
}
///@brief CVideo��Ļ�õ�ǰ������Ⱥ���
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval double
///@post NULL
double CVideo::ProcessingSpeed()   
{
	return this->m_ProcessingSpeed;///<���ص�ǰ�������
}
///@brief CVideo�����ֹ������
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::StopProcessing()
{
	if (!m_IfDoneFus&&m_IfContinue)///<���ںϴ���δ���ʱ
	{
		this->m_IfContinue = false;///<���������־λ�÷�

		//m_MysqlSegHandle->DropTable(m_tableParams.VideoFGTableName);///<ɾ��ǰ������Ϣ��
		//cvWaitKey(1);///<�ȴ�ʱ�䣬ȷ��ɾ��ɹ�
		//m_MysqlSegHandle->DropTable(m_tableParams.FGTraceTableName);///<ɾ���˶�����켣��
		//cvWaitKey(1);///<�ȴ�ʱ�䣬ȷ��ɾ��ɹ�
		m_MysqlSegHandle->DropTable(m_tableParams.NewToOldFrameTableName);///<ɾ���¾���Ƶ֡���ձ�
		cvWaitKey(1);///<�ȴ�ʱ�䣬ȷ��ɾ��ɹ�
		//m_MysqlSegHandle->DropTable(m_tableParams.NewTraceTable);///<ɾ��Ŀ��켣��Ϣ��
		cvWaitKey(5);
	}
}
///@brief CVideo��Ļ�ȡԭʼ��Ƶ֡������
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval int
///@post NULL
int CVideo::VideoOriCount()
{
	if(m_nTotalFrameToDo>0)
		return m_nTotalFrameToDo;///<��ԭʼ��Ƶ��֡��Ϊ��ʱ�����ظ�ֵ
	else
		return -1;///<���򷵻�-1
}
///@brief CVideo��Ļ�ȡ�ָ���Ƶ֡������
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval int
///@post NULL
int CVideo::VideoSegCount()
{
	if (m_IfDoneSeg)
		return this->SegFrame_Count;///<���ָ���Ƶ��֡��Ϊ��ʱ�����ظ�ֵ
	else
		return -1;///<���򷵻�-1
}
///@brief CVideo��Ļ�ȡ�ں���Ƶ֡������
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval int
///@post NULL
int CVideo::VideoFusCount()
{
	if (m_IfDoneFus)
		return this->FusFrame_Count;///<���ں���Ƶ��֡��Ϊ��ʱ�����ظ�ֵ
	else
		return -1;///<���򷵻�-1
}
///@brief CVideo�����Ƶ�ָ��ں��ܿغ���
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::VideoProcessing()
{
	if(this->Initialization(m_strFilePath.c_str()) != -1)
	{///����ʼ����������ֵΪ��ʱ���������²���
		this->VideoParaProcessing();  ///<��Ƶ�ֶ�
#ifdef VideoConnection_Is_On
		this->VideoConnection();      ///<�ָ���Ƶƴ��
#endif
		this->VideoBGProcessing();    ///<��Ƶ������ȡ
		this->VideoFGProcessing();    ///<��Ƶǰ���з�
		this->VideoFusionProcessing();///<��Ƶ�ں�
	}
	else 
	{///����ʼ����������ֵΪ-1ʱ�����������־λ�÷�
		m_IfContinue = false;
	}
}
///@brief CVideo�����Ƶ������ʼ������
/// 
///@param[in] ��Ƶ·��
///@pre  NULL
///@return NULL
///@retval int
///@post NULL
int  CVideo::Initialization(const char *pVideoPath)
{
	m_pCapture = cvCreateFileCapture(pVideoPath);///<��ȡ��Ƶͷָ��
	if (m_pCapture == NULL)
		return -1;///<��ȡʧ�ܷ���-1
    
	///��Ƶ��Ϣ
	m_nTotalFrame   = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_FRAME_COUNT);///<��ȡ��Ƶ��֡��
	m_nFps          = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_FPS);///<��ȡ��Ƶ֡��
	m_pStor         = cvCreateMemStorage(0);///<�����˶�Ŀ�������洢�ռ�

	cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES, 1);///<������Ƶ��ǰ֡Ϊ��֡
	m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ��Ƶ֡ͼ��
	if (m_pOriFrame == NULL) 
		return -1;///<��ǰ֡ͼ���ȡʧ�ܣ�����-1

	///��Ƶ֡��Ϣ
	m_nVideoH = m_pOriFrame->height;///<��ȡ֡ͼ��߶�
	m_nVideoW = m_pOriFrame->width; ///<��ȡ֡ͼ����

	///��ʼ����������
	if(InitSampleSetting() == -1)///<��ʼ��ѹ������
		return -1;              ///<��ʼ��ѹ������ʧ�ܣ�����-1
	
	InitStorage();	  ///<��ʼ��ͼ�����ݣ�����ռ�
	InitGaussParam();   ///<��ʼ����˹ģ��
	InitTableParam();   ///<��ʼ�����ݿ��
	InitAbstractVideo(pVideoPath);///<��ʼ��ժҪ��Ƶ����

	m_newTraceTextPath.Format("%s_newTrace.txt",pVideoPath);
	m_newTraceOfstream.open(m_newTraceTextPath,ios::out); 

	
	return 1;///<��ʼ������ִ�гɹ�������1
}
///@brief CVideo��ĳ�ʼ��ѹ����������
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
int CVideo::InitSampleSetting()
{
	double ratio = 1.0;
	double ratioH = (double)m_nVideoH/800.0;
	double ratioW = (double)m_nVideoW/800.0;// ʹ�����Ƶ��800*800���ڡ�Ŀǰѡ00015_hΪ������Ƶ��ԭ��Ƶ640*480�������ƵΪ640*480
	ratio = MAX(ratioH,ratioW);

	m_nProcessingRatio   = (int)ceil(ratio);///<��ʼ����Ƶ֡��С�������
	m_nCompressionRatioH = 16;///<��ʼ���߶�ѹ����
	m_nCompressionRatioW = 16;///<��ʼ�����ѹ����
	m_nSamplingRate      = m_nFps/2;///<��ʼ������֡�����
	m_nSampleTime        = 5;///<��ʼ������ʱ����
	m_nTotalFrameToDo    = m_nTotalFrame - m_nFps;///<��ʼ���ܲ���֡��
	if (m_nTotalFrameToDo < 5000)
	{///������Ƶ��֡��>5000,��4min��Ƶ�ɴ���������Ƶ�������账��,ԭΪ20000��@QiFeng
		m_nTotalFrameToDo = -1;
		m_ProcessingSpeed = -1;
		return m_ProcessingSpeed;
	}
	else
	{
		m_ProcessingSpeed = 0;///<��ʼ���������
	}
	m_nTotalFrameToDo    = 45000;

	m_nBGUpdateFrames    = MAX(m_nTotalFrameToDo/9,m_nFps*300);   ///<��ʼ������������֡��
	m_nBGUpdateSampleFrame = m_nBGUpdateFrames/20;///<��ʼ���������²���֡��
	//m_nBGUpdateFrames    = 4000;
	//m_nBGUpdateSampleFrame = 400;
	
	return m_ProcessingSpeed;
} 
///@brief CVideo��ĳ�ʼ��ͼ�����ݣ�����ռ亯��
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::InitStorage()
{
	m_nVideoH /= m_nProcessingRatio;///<��ʼ����Ƶ֡����߶�
	m_nVideoW /= m_nProcessingRatio;///<��ʼ����Ƶ֡������
	m_nVideoResizeH   = m_nVideoH / m_nCompressionRatioH;///<��ʼ����Ƶ֡ѹ���߶�
	m_nVideoResizeW   = m_nVideoW / m_nCompressionRatioW;///<��ʼ����Ƶ֡ѹ���߶�
	m_nMaxTargetArea  = m_nVideoH * m_nVideoW / 4;  ///<��ʼ���˶�Ŀ��������
	m_nMinTargetArea  = m_nVideoH * m_nVideoW / 400;///<��ʼ���˶�Ŀ����С���

	m_pProcessFrame   = cvCreateImage(cvSize(m_nVideoW, m_nVideoH), IPL_DEPTH_8U, 3);///<��ʼ������ͼ��֡������ռ�
	m_pGrayFrame      = cvCreateImage(cvSize(m_nVideoW, m_nVideoH), IPL_DEPTH_8U, 1);///<��ʼ���Ҷ�ͼ��֡������ռ�
	m_pBGFrame        = cvCreateImage(cvSize(m_nVideoW, m_nVideoH), IPL_DEPTH_8U, 3);///<��ʼ������ͼ��֡������ռ�
	for (int i=0;i<10;i++)
	{
		m_pBGFinal[i]  = cvCreateImage(cvSize(m_nVideoW, m_nVideoH), IPL_DEPTH_8U, 3);///<��ʼ����ȡ����ͼ��֡������ռ�
	}

	cvResize  (m_pOriFrame, m_pProcessFrame, CV_INTER_LINEAR);
	
	cv::Mat m_OriFrameMat = m_pOriFrame;
	cv::Mat m_GrayFrameMat = m_pGrayFrame;
	
	//��ά��m_nVideoResizeW*m_nVideoResizeH
	resize(m_OriFrameMat,m_ResizeFrameMat,Size(m_nVideoResizeW,m_nVideoResizeH),0,0,CV_INTER_LINEAR);
	cvtColor(m_OriFrameMat, m_GrayFrameMat, CV_BGR2GRAY,1); ///<�ҶȻ�
	resize(m_GrayFrameMat,m_GrayResizeFrameMat,Size(m_nVideoResizeW,m_nVideoResizeH),0,0,CV_INTER_LINEAR);
	cvCopy    (m_pProcessFrame, m_pBGFrame);
	
//	m_pFrameMat      = cvCreateMat(m_nVideoH, m_nVideoW, CV_32FC3);///<��ʼ����Ƶͼ������(3ͨ��)
//	m_pBGMat         = cvCreateMat(m_nVideoH, m_nVideoW, CV_32FC3);///<��ʼ������ͼ������(3ͨ��)
	m_pGrayFrameMat  = cvCreateMat(m_nVideoH, m_nVideoW, CV_32FC1);///<��ʼ����Ƶͼ������(1ͨ��)
	m_pGrayBGMat     = cvCreateMat(m_nVideoH, m_nVideoW, CV_32FC1);///<��ʼ������ͼ������(1ͨ��)
	m_pGrayFGMat     = cvCreateMat(m_nVideoH, m_nVideoW, CV_32FC1);///<��ʼ��ǰ��ͼ������(1ͨ��)
//	cvConvert(m_pProcessFrame, m_pFrameMat);  
	m_FrameMat = m_pProcessFrame;
	m_BGMat = m_pProcessFrame;

	
//	m_pGrayFrameMat = m_pGrayFrame;
//	m_GrayBGMat = m_pGrayFrame;
	
	//m_pFrameMat(m_pProcessFrame);
	//cvConvert(m_pProcessFrame, m_pBGMat);
	cvConvert(m_pGrayFrame,    m_pGrayFrameMat);
	cvConvert(m_pGrayFrame,    m_pGrayBGMat);
	cvConvert(m_pGrayFrame,    m_pGrayFGMat);
}
///@brief CVideo��ĳ�ʼ����˹ģ�ͺ���
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::InitGaussParam()
{
	///�½���˹ģ�Ͳ���ʼ����ز���
	//m_pGaussParams = new CvGaussBGStatModelParams;
	//m_pGaussParams->win_size      = 300;	// ��ʼ���׶ε�֡�����û��Զ���ģ��ѧ ϰ��a=1/win_size;
	//m_pGaussParams->bg_threshold  = 0.65;	//������һ����˹ģ��ƥ��ʱ����ֵ
	//m_pGaussParams->std_threshold = 3.5;	//�Ƿ�Ϊ�����ĵ���ֵ
	//m_pGaussParams->weight_init   = 0.05;	//��˹�ֲ��ĳ�ʼȨֵ
	//m_pGaussParams->variance_init = 30*30;	//��˹�ֲ��ĳ�ʼ����
	//m_pGaussParams->minArea       = 15;		 //��С����������������ȥ�룬������Ŀ������������С����minAreaʱ���Ͱ���������ȥ��
	//m_pGaussParams->n_gauss       = 3;		//��˹�ֲ������ĸ���
	// m_pBGSubMOG2 = new cv::BackgroundSubtractorMOG2;
	//m_pGaussBGModel     = (CvGaussBGModel*)cvCreateGaussianBGModel(m_pGrayResizeFrame, m_pGaussParams);
}
///@brief CVideo��ĳ�ʼ�����ݿ����
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::InitTableParam()
{
	///����Ƶ·��������
	CString m_tmpFileName0 = m_strFilePath.c_str();
    CString m_tmpFileName1, m_tmpFileName2;
	GetVideoNameFromAbsolutePath(&m_tmpFileName0,&m_tmpFileName1);///<��ȡ�ļ���(������׺)
	GetFileNameBeforeDot(&m_tmpFileName1,&m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
	
	///��ʼ���������
	m_tableParams.VideoFGTableName.Format("%s_VideoFGTable",m_tmpFileName2);
	m_tableParams.FGTraceTableName.Format("%s_FGTraceTable",m_tmpFileName2);
	m_tableParams.NewToOldFrameTableName.Format("%s_New2OldFrameTable",m_tmpFileName2);
	m_tableParams.NewTraceTable.Format("%s_NewTraceTable",m_tmpFileName2);
	m_tableParams.CombineSegsTableName.Format("%s_CombineSegsTable", m_tmpFileName2);

	///����ǰ������Ϣ��
	if(!m_MysqlSegHandle->DropTable(m_tableParams.VideoFGTableName))
	{
		AfxMessageBox("ɾ��fgtable�����");
		return;
	}	
	if(!m_MysqlSegHandle->CreateVideoFGTable(m_tableParams.VideoFGTableName))
	{
		AfxMessageBox("����fgtable����");
		return;
	}
	m_MysqlSegHandle->CleanTable(m_tableParams.VideoFGTableName);
	///�����˶�����켣��
	if(!m_MysqlSegHandle->DropTable(m_tableParams.FGTraceTableName))
	{
		AfxMessageBox("ɾ��trace�����");
		return;
	}	
	if(!m_MysqlSegHandle->CreateOrigTraceTable(m_tableParams.FGTraceTableName))
	{
		AfxMessageBox("��trace�����");
		return;
	}
	m_MysqlSegHandle->CleanTable(m_tableParams.FGTraceTableName);
	///�����¾���Ƶ֡���ձ�
	if(!m_MysqlSegHandle->DropTable(m_tableParams.NewToOldFrameTableName))
	{
		AfxMessageBox("ɾ��NewToOldFrameTable�����");
		return;
	}
	if(!m_MysqlSegHandle->CreateNewToOldFrameTable(m_tableParams.NewToOldFrameTableName))
	{
		AfxMessageBox("����NewToOldFrameTable����");
		return;
	}
	m_MysqlSegHandle->CleanTable(m_tableParams.NewToOldFrameTableName);
	///����Ŀ��켣��Ϣ��
	if(!m_MysqlSegHandle->DropTable(m_tableParams.NewTraceTable))
	{
		AfxMessageBox("ɾ����trace�����");
		return;
	}
	if(!m_MysqlSegHandle->CreateNewTraceTable(m_tableParams.NewTraceTable))
	{	
		AfxMessageBox("��trace����ʧ��");
		return;
	}
	m_MysqlSegHandle->CleanTable(m_tableParams.NewTraceTable);
	
	///�����ϳ�ǰ��ͼ��Ϣ��
	if (!m_MysqlSegHandle->DropTable(m_tableParams.CombineSegsTableName))
	{
		AfxMessageBox("ɾ��Combine�����");
		return;
	}
	if (!m_MysqlSegHandle->CreateCombineSegsTable(m_tableParams.CombineSegsTableName))
	{
		AfxMessageBox("��Combine�����");
		return;
	}
	///�����ݴ��ں�ͼ����ļ���
	CFileFind m_find;
	if (!m_find.FindFile("..\\"+m_tmpFileName2))///<FindFile�ڵ�ǰĿ¼������Ŀ¼�²�ѯ
	{
		CString CreateFileCommand = "md ..\\";
		CreateFileCommand += m_tmpFileName2;
		system(CreateFileCommand);///<DOS������ļ���
	}
}
///@brief CVideo��ĳ�ʼ��ժҪ��Ƶ��������
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::InitAbstractVideo(const char* pVideoPath)
{
	strSegVideoNewName    = pVideoPath;
	strFusionVideoNewName = pVideoPath;
	///��ʼ���ָ���Ƶ·�����½��ָ���Ƶдָ��
	strSegVideoNewName    = strSegVideoNewName + "_newcut.avi";
	m_pVideoWriter4seg    = cvCreateVideoWriter(strSegVideoNewName.c_str(), CV_FOURCC('D','I','V','X'), m_nFps/2,cvSize(m_nVideoW, m_nVideoH));
	///��ʼ���ں���Ƶ·�����½��ں���Ƶдָ��
	strFusionVideoNewName = strFusionVideoNewName + "_fusion.avi";
	m_pVideoWriter4fusion = cvCreateVideoWriter(strFusionVideoNewName.c_str(), CV_FOURCC('D','I','V','X'), m_nFps/2,cvSize(m_nVideoW, m_nVideoH));
}
///@brief CVideo�����Ƶ�ֶκ���
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::VideoParaProcessing()
{
	if(m_IfContinue == FALSE)///<���������־λΪ�񣬷���
		return;

	bool m_tableExist = false;///<���ݱ��������־λ
	///�ж����ݱ��Ƿ���ȷ����
	if(!m_MysqlSegHandle->IfExistTable(m_tableParams.VideoFGTableName,&m_tableExist))
	{
		AfxMessageBox("���ݿ����");
		return ;
	}
	if(!m_tableExist)
	{
		AfxMessageBox("ǰ�α�����");
		return;
	}

	if (!m_pCapture)///<��Ƶͷָ�벻���ڣ��򷵻�
		return;
	cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES,1);///<��Ƶͷָ����ڣ����õ�ǰ֡Ϊ��֡
	m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
	if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ�����
		return;
	m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��
	///��ʼ����Ƶ�ֶβ���
	m_VideoBGParam.BGImgID    = 0;
	m_VideoFGParam.nOldPara   = 0;
	m_VideoBGParam.startFrame = m_nCurrentFrame;
	m_VideoBGParam.endFrame   = m_nCurrentFrame;
	m_VideoFGParam.startFrame = m_nCurrentFrame;
	m_VideoFGParam.endFrame   = m_nCurrentFrame;

	m_rFGSegThreshold = 0.01;///<��ʼ��Ϊ0.01��ǰ������ռȫͼ��1%
	
	///��ʼ��Ƶ�ֶ�
	while(m_IfContinue)
	{
		m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
		if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ��˳�ѭ��
			break;	
		m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��
		m_ProcessingSpeed = (double)m_nCurrentFrame/(double)m_nTotalFrameToDo;///<���㴦�����

        if(m_nCurrentFrame>m_VideoFGParam.endFrame)
		{
			if ((int)m_nCurrentFrame%m_nSamplingRate == 1)
			{///������ȡ֡ͼ��������
				cvSmooth  (m_pOriFrame, m_pOriFrame, CV_GAUSSIAN,3,0,0);     ///<��˹�˲�
				cv::Mat m_OriFrameMat = m_pOriFrame;

				resize(m_OriFrameMat,m_ResizeFrameMat,Size(m_nVideoResizeW,m_nVideoResizeH),0,0,CV_INTER_LINEAR);///<ѹ�� 640*480 m_pResizeFrame=30*40
				cvtColor(m_ResizeFrameMat, m_GrayResizeFrameMat, CV_BGR2GRAY,1); ///<�ҶȻ�
			
				m_pBGSubMOG2.operator()(m_GrayResizeFrameMat, foregroundMat, 0.001);						
				//cvUpdateBGStatModel(m_pGrayResizeFrame, (CvBGStatModel*)m_pGaussBGModel);///<��˹��������
				
				m_GrayResizeFrameMat = foregroundMat; //?????
				//cvCopy(m_pGaussBGModel->foreground, m_pGrayResizeFrame);     ///<��ȡǰ��		
				this->ParaSegmentation();///<��Ƶ�ֶ��㷨
			}
			if (m_nCurrentFrame >= m_nTotalFrameToDo)///<��ǰ֡Ϊ�ܴ���֡�ţ���Ƶ�ֶδ�����ɣ��˳�ѭ��
				break;
		}
	}
	///������Ƶ�ֶ�

	BGPara_Count = m_VideoBGParam.BGImgID;   ///<����������������ͼƬ��
	FGPara_Count = m_VideoFGParam.nOldPara;  ///<ǰ�����������ָ�Ƭ����
}
///@brief CVideo�����Ƶ������ȡ����
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::VideoBGProcessing()
{
	if (!m_pCapture)///<��Ƶͷָ�벻���ڣ��򷵻�
		return;
    cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES,0);///<��Ƶͷָ����ڣ����õ�ǰ֡Ϊ��֡
	m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
	if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ�����
		return;
	m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��
	///��ʼ����Ƶ������ȡ����
	m_VideoBGParam.BGImgID    = 0;
	m_VideoBGParam.startFrame = m_nCurrentFrame;
	m_VideoBGParam.endFrame   = m_nCurrentFrame;

	float bgkNum = 0.0;
	float alpha = 0.0;
	float beta = 0.0;
	
	///��ʼ��Ƶ������ȡ
	bool m_IfInitBGFinal = true;///<����ͼƬ��ʼ����־λ
	for(;m_VideoBGParam.BGImgID < BGPara_Count && m_IfContinue;m_VideoBGParam.BGImgID++)
	{
		m_VideoBGParam.startFrame = m_nBGFinal[m_VideoBGParam.BGImgID];                ///<��Ƶ��̬����ʼ֡��
		m_VideoBGParam.endFrame   = m_VideoBGParam.startFrame + m_nBGUpdateSampleFrame;///<��Ƶ��̬�ν���֡��
		//if(m_VideoBGParam.startFrame>500)
		if(m_VideoBGParam.startFrame>(m_nBGUpdateFrames/4))
		{
			cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES, m_VideoBGParam.startFrame);
		}
		else
		{
			cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES,0);///<��Ƶͷָ����ڣ����õ�ǰ֡Ϊ��֡
		}
		while (m_IfContinue)
		{
			m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
			if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ��˳��ڲ�ѭ��
				break;
			m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��
			if(m_nCurrentFrame < m_VideoBGParam.startFrame)
				continue;
			else if(m_nCurrentFrame>=m_VideoBGParam.startFrame && m_nCurrentFrame<=m_VideoBGParam.endFrame)
			{///<��ǰ֡�Ŵ��ڸþ�̬�η�Χ����������
				//if ((int)m_nCurrentFrame % m_nSamplingRate == 1)
				{
					m_ProcessingSpeed = 2.0+(double)m_nCurrentFrame/(double)m_nTotalFrameToDo;///<���㴦�����
					cvResize(m_pOriFrame, m_pProcessFrame);///<ѹ��
					//cvConvert(m_pProcessFrame, m_pFrameMat);///<����ת����IplimageתΪcvMat
					m_FrameMat = m_pProcessFrame; //<����ת����IplimageתΪMat
					//cvRunningAvg(m_pFrameMat, m_pBGMat, 0.03, 0);///<�����ƶ�ƽ��
					//cvCopy(m_pFrameMat,m_pBGMat);
					m_BGMat = m_FrameMat.clone();  //����ͼ��Mat
					//cvConvert(m_pBGMat, m_pBGFrame);///<����ת����cvMatתΪIplimage
					*m_pBGFrame = m_BGMat;       //<����ת����MatתΪIplimage
					if (m_IfInitBGFinal)
					{
						cvCopy(m_pBGFrame,m_pBGFinal[m_VideoBGParam.BGImgID]);///<����ͼƬ��ʼ����ɣ�����ͼ����뱳��ͼƬ����
						m_IfInitBGFinal = false;///<����ͼƬ��ʼ����־λ�÷�
						bgkNum = 0.0;
					}
					bgkNum += 1.0;
					alpha = (bgkNum-1.0)/bgkNum;
					beta = 1.0-alpha;
					cvAddWeighted(m_pBGFinal[m_VideoBGParam.BGImgID],alpha,m_pBGFrame,beta,0,m_pBGFinal[m_VideoBGParam.BGImgID]);///<ͼ���ɫ
				}
			}
			else if((m_nCurrentFrame > m_VideoBGParam.endFrame))
			{///��ǰ֡�ų����þ�̬�η�Χ
				m_IfInitBGFinal = true; ///<����ͼƬ��ʼ����־λ����Ϊtrue
				break;                  ///<�˳��ڲ�ѭ��
			}		
		}	
	}
	///������Ƶ������ȡ
}
///@brief CVideo�����Ƶǰ���зֺ���
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::VideoFGProcessing()
{
	if (!m_pCapture)///<��Ƶͷָ�벻���ڣ��򷵻�
		return;
	cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES,1);///<��Ƶͷָ����ڣ����õ�ǰ֡Ϊ��֡
	m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
	if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ�����
		return;
	///��ʼ����Ƶǰ���зֲ���
	m_nSamplingRate          = MIN(m_nFps/4,5);
	m_traceTab.segID         = 0;
	m_VideoFGParam.nOldPara  = 0;
	m_VideoBGParam.BGImgID   = 0;
	m_New2OldParaParam.nOldPara = 0;
	m_New2OldParaParam.nNewPara = 0;
	m_segIDCount             = 0;
	m_segIDParam             = 1; ///<��ʼ������Ϊ��
	m_FusionParam            = 0;
	

	///��ʼ��Ƶǰ���з�
	m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��
	for (;m_VideoFGParam.nOldPara<FGPara_Count && m_IfContinue;m_VideoFGParam.nOldPara++)
	{
		m_VideoFGParam.startFrame = m_nFGFinal[m_VideoFGParam.nOldPara];             ///<��Ƶ��̬����ʼ֡��
		m_VideoFGParam.endFrame   = m_VideoFGParam.startFrame + m_nFps*m_nSampleTime;///<��Ƶ��̬����ʼ֡��
		m_segIDCount = 0;
		while(m_IfContinue)
		{
			m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
			if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ��˳��ڲ�ѭ��
				break;
			m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��
			m_ProcessingSpeed = 3.0+(double)m_nCurrentFrame/(double)m_nTotalFrameToDo;///<���㴦�����
			if (m_nCurrentFrame < m_VideoFGParam.startFrame)
				continue;
			///<��ǰ֡�Ŵ��ڸö�̬�η�Χ����������
			if (m_nCurrentFrame/m_nBGUpdateFrames == m_VideoBGParam.BGImgID)
			{
				///��������
				if (m_VideoBGParam.BGImgID >= BGPara_Count)
					m_VideoBGParam.BGImgID = BGPara_Count-1;
				
				cvCvtColor(m_pBGFinal[m_VideoBGParam.BGImgID], m_pGrayFrame, CV_BGR2GRAY);
				cvConvert(m_pGrayFrame, m_pGrayBGMat);
				//m_GrayBGMat = m_pGrayFrame;
				if (m_VideoBGParam.BGImgID < BGPara_Count-1)
					m_VideoBGParam.BGImgID++;
			}
			if ((int)m_nCurrentFrame%m_nSamplingRate == 1)
			{
				///ǰ���ָ�
				cvResize(m_pOriFrame, m_pProcessFrame, CV_INTER_LINEAR);///<��С
				cvCvtColor (m_pProcessFrame, m_pGrayFrame, CV_BGR2GRAY);///<�ҶȻ�
			

				//m_GrayFrameMat = m_pGrayFrame;   //<תΪMat����
				//GaussianBlur(m_GrayFrameMat,m_GrayFrameMat,Size(3,0),0,0);//<��ƽ���˲�
				//subtract(m_GrayFrameMat,m_GrayBGMat,m_GrayFGMat);
				cvConvert(m_pGrayFrame, m_pGrayFrameMat);///<תΪcvMat����
				cvSmooth (m_pGrayFrameMat, m_pGrayFrameMat, CV_GAUSSIAN, 3, 0, 0, 0);///<ƽ���˲�
				
				cvAbsDiff(m_pGrayFrameMat, m_pGrayBGMat, m_pGrayFGMat);///<ǰ��=ԭͼ-����
				cvErode  (m_pGrayFGMat, m_pGrayFGMat, 0, 1);///<ͼ��ʴ
				cvDilate (m_pGrayFGMat, m_pGrayFGMat, 0, 1);///<ͼ������
				cvThreshold(m_pGrayFGMat, m_pGrayFrame, 30,255.0,CV_THRESH_BINARY);///<ǰ��ͼ���ֵ��
				FGSegmentation();///<��Ƶǰ���з��㷨
			}
			if (m_nCurrentFrame>m_VideoFGParam.endFrame)
				break;///<��ǰ֡�ų����ö�̬�η�Χ���˳��ڲ�ѭ��
		}
		if (m_segIDCount)
		{///�ö�̬�η�Χ�����˶�����
			TimeLineRestructed();///<�ع�ʱ����
		}
		else
		{///�ö�̬�η�Χ�������˶�����
			m_nParaFinal[m_VideoFGParam.nOldPara] = -1;///<�ֶα��Ӧλ�ø�Ϊ-1
		}
	}
	m_newTraceOfstream.close();///<�ر���

	///��������txt�ļ��е����ݵ���fgtrace����
	if(m_IfContinue && !m_MysqlSegHandle->LoadTextData2Table(m_newTraceTextPath,m_tableParams.FGTraceTableName))
	{
		AfxMessageBox("�����������");
		return;
	}

	///������Ƶǰ���з�
	m_segIDCount = m_traceTab.segID;///<��Ƶǰ����ȡ��������
}
///@brief CVideo�����Ƶ�ֶ��㷨
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::ParaSegmentation()
{
	int i,j,k;
	k = 0;
	for (i = 0;i < m_nVideoResizeH; i++)
	{
		for (j = 0;j < m_nVideoResizeW; j++)
		{
			if (m_GrayResizeFrameMat.data[i*m_nVideoResizeW + j] != 0)
			{
				k++;///<�����ֵǰ��ͼ���0���ص����
			}
		}
	}
	double k_ratio = (double)k/(double)(m_nVideoResizeW*m_nVideoResizeH);
	if (k_ratio <=0.01)
		return;
	if (k_ratio/m_rFGSegThreshold > 1.5 || k_ratio/m_rFGSegThreshold < 0.67)
		m_rFGSegThreshold = k_ratio;
	
	///��⵽�˶���Ƶ��
	if (k_ratio >= m_rFGSegThreshold)
	{
		m_VideoFGParam.startFrame = m_nCurrentFrame;///<��ȡ��̬����ʼ֡��
		if (m_VideoFGParam.startFrame/m_nBGUpdateFrames == m_VideoBGParam.BGImgID)
		{///�жϵ�ǰ֡�������ı���ͼ��ID
			if (m_VideoFGParam.startFrame - m_VideoFGParam.endFrame > m_nBGUpdateSampleFrame)
			{///��ʼ�Ҿ�̬��������Ƶ������ȡ
				m_VideoBGParam.startFrame = (m_VideoFGParam.startFrame+m_VideoFGParam.endFrame)/2-m_nBGUpdateSampleFrame/2;///<��ȡ��̬����ʼ֡��
				m_VideoBGParam.endFrame   = (m_VideoFGParam.startFrame+m_VideoFGParam.endFrame)/2+m_nBGUpdateSampleFrame/2;///<��ȡ��̬�ν���֡��
				m_nBGFinal[m_VideoBGParam.BGImgID] = m_VideoBGParam.startFrame;///<���澲̬��λ����Ϣ
				m_VideoBGParam.BGImgID++;///<����ͼ��ID����һ
				cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES,m_VideoBGParam.startFrame);///<��Ƶͷָ����ڣ����õ�ǰ֡Ϊ��֡
				m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
				if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ�����
					return;
				m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��

			}
		}
		m_VideoFGParam.endFrame = m_VideoFGParam.startFrame + m_nFps*m_nSampleTime;///<��ȡ��̬�ν���֡��
		if (m_VideoFGParam.endFrame>= m_nTotalFrameToDo)///<��ǰ֡Ϊ�ܴ���֡�ţ��������
		{
			m_VideoFGParam.nOldPara--;///<��Ƶǰ����������һ
			return;///<����
		}
		else
		{
			if (m_VideoFGParam.endFrame>((m_VideoBGParam.BGImgID+1)*m_nBGUpdateFrames))
			{///��Ƶǰ���ν���֡�ų�����Ӧ����ͼ��ID��Χ
				m_VideoBGParam.startFrame = (m_VideoBGParam.BGImgID)*m_nBGUpdateFrames+m_nBGUpdateFrames/2-m_nBGUpdateSampleFrame/2;///<��ȡĬ�Ͼ�̬����ʼ֡��
				m_VideoBGParam.endFrame   = (m_VideoBGParam.BGImgID)*m_nBGUpdateFrames+m_nBGUpdateFrames/2+m_nBGUpdateSampleFrame/2;///<��ȡĬ�Ͼ�̬�ν���֡��
				m_nBGFinal[m_VideoBGParam.BGImgID] = m_VideoBGParam.startFrame;///<���澲̬��λ����Ϣ
				cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES,m_VideoBGParam.startFrame);///<��Ƶͷָ����ڣ����õ�ǰ֡Ϊ��֡
				m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
				if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ�����
					return;
				m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��

				m_VideoBGParam.BGImgID++;///<����ͼ��ID����һ
			}
		}
		m_nFGFinal[m_VideoFGParam.nOldPara] = m_VideoFGParam.startFrame;///<���涯̬��λ����Ϣ
		if(m_IfContinue && !m_MysqlSegHandle->InsertData2VideoFGTable(m_VideoFGParam,m_tableParams.VideoFGTableName))
		{///����д��ǰ������Ϣ��
			AfxMessageBox("ǰ���α�������");
			return ;
		}
		m_VideoFGParam.nOldPara++;///<��̬����������һ
		return;///<����
	}
}
///@brief CVideo�����Ƶǰ���з��㷨
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::FGSegmentation()
{
	float ratio = 0.0;
	m_pCont = NULL;
	cvFindContours(m_pGrayFrame, m_pStor, &m_pCont, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));///<��ȡ��ֵǰ��ͼ���˶�����������Ϣ
	for (;m_pCont;m_pCont = m_pCont->h_next)
	{
		if (m_pCont->total<6)///<��������٣���������
			continue;
		r = ((CvContour*)m_pCont)->rect;///<��ȡ��ǰ������Ӿ���
		if (r.height*r.width>m_nMinTargetArea && r.height*r.width<m_nMaxTargetArea)
		{///<�����˶�Ŀ����Ӿ����������Ҫ�󣬱��������Ϣ
			/*m_traceTab.nLeft= r.x;
			m_traceTab.nRight = (r.x+r.width);
			m_traceTab.nTop   = r.y;
			m_traceTab.nBottom= (r.y+r.height);*/
			m_traceTab.nX= r.x;
			m_traceTab.nY = r.y;
			m_traceTab.nHeight   = r.height;
			m_traceTab.nWidth= r.width;
			m_traceTab.origFrame = (int)m_nCurrentFrame; 
			m_traceTab.nOldPara = m_VideoFGParam.nOldPara;
			ratio = (float)r.width*r.height/m_nVideoH/m_nVideoW;
			if(ratio>SEG_L_RATIO)
			{
				m_traceTab.segSize = 0;//"L";
			}
			else if(ratio>SEG_M_RATIO)
			{
				m_traceTab.segSize = 1;//"M";
			}
			else
			{
				m_traceTab.segSize = 2;//"S";
			}
			if(m_IfContinue &&!m_MysqlSegHandle->InsertData2OrigTraceTable(m_traceTab,m_tableParams.FGTraceTableName))
			{///����д���˶�����켣��
				AfxMessageBox("trace��������");
				return ;
			}
			///��fgtraceд����
			m_newTraceOfstream<<m_traceTab.nOldPara<<","<<m_traceTab.segID<<","<<m_traceTab.nX<<","<<m_traceTab.nY<<","<<m_traceTab.nWidth<<","<<m_traceTab.nHeight<<","<<m_traceTab.origFrame<<","<<m_traceTab.segSize<<endl;

			m_traceTab.segID++;///<�˶�����������һ
			m_segIDCount++;    ///<�˶�������������һ
		}
	}	   
}
///@brief CVideo��ķָ���Ƶƴ�Ӻ���
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::VideoConnection()
{
	if (!m_pCapture)///<��Ƶͷָ�벻���ڣ��򷵻�
		return;
	cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES, 1);///<��Ƶͷָ����ڣ����õ�ǰ֡Ϊ��֡
	///��ʼ���ָ���Ƶƴ�Ӳ���
	SegFrame_Count = 0;
	int i;
	///��ʼ�ָ���Ƶƴ�Ӳ���
	for(i = 0;i<FGPara_Count && m_IfContinue;i++)
	{
		m_VideoFGParam.startFrame = m_nFGFinal[i];///<��ȡ��̬����ʼ֡��
		m_VideoFGParam.endFrame   = m_VideoFGParam.startFrame + m_nFps*m_nSampleTime;///<��ȡ��̬�ν���֡��
		if(m_VideoFGParam.startFrame>500)
		{
			cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES, m_VideoFGParam.startFrame-500);///<��Ƶͷָ����ڣ����õ�ǰ֡Ϊ��֡
		}
		else
		{
			//cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES, 1);///<��Ƶͷָ����ڣ����õ�ǰ֡Ϊ��֡
		}
		m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
		if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ��˳�ѭ��
			break;
		m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��
       
		while (m_IfContinue)
		{
			m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
			if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ��˳�ѭ��
				break;
			m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��
			m_ProcessingSpeed = 1.0+(double)m_nCurrentFrame/(double)m_nTotalFrameToDo;///<���㴦�����
			if (m_nCurrentFrame >= m_VideoFGParam.startFrame && m_nCurrentFrame<= m_VideoFGParam.endFrame)
			{///<��ǰ֡�Ŵ��ڸö�̬�η�Χ����������
				if ((int)m_nCurrentFrame%m_nSamplingRate == 1)
				{
					cvResize(m_pOriFrame, m_pProcessFrame);
					cvWriteFrame(m_pVideoWriter4seg, m_pProcessFrame);///<д��ָ���Ƶ
					SegFrame_Count++;
				}
			}
			if(m_nCurrentFrame>m_nTotalFrameToDo||m_nCurrentFrame>m_VideoFGParam.endFrame)
				break;
		}
	}
	///�����ָ���Ƶƴ�Ӳ���
	if(i>=FGPara_Count)
	{
		if (m_pVideoWriter4seg!=NULL)
		{
			cvReleaseVideoWriter(&m_pVideoWriter4seg);
		}
		m_IfDoneSeg = true;///<���ж��������Ƶ�ָ���ɱ�־λ��Ϊtrue
	}
}
///@brief CVideo���ʱ�����ع�����
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::TimeLineRestructed()
{
	///ʱ�����ع�������ʼ��
	if (m_segIDCount<10)
	{
		m_nParaFinal[m_VideoFGParam.nOldPara] = -1;///<��̬���˶�������٣��ж�Ϊ���
		return;///<���أ���������
	}
	if (m_segIDParam == 1)
	{
		m_segIDParam = m_segIDCount;///<��ʼ��segID����
	}
	if (abs((double)m_segIDCount/(double)m_segIDParam)-1.0 < 0.1)
	{
		///���ڶ�̬��������Ŀֵ���ƣ���ΪͬһĿ����һ��ʱ���ڵ�λ���˶���Ӧ��Ϊ����
		m_segIDParam = (m_segIDCount+m_segIDParam)/2;///<���㶯̬��������Ŀ��ֵ
		m_New2OldParaParam.nOldPara = m_VideoFGParam.nOldPara;
		m_nParaFinal[m_VideoFGParam.nOldPara] = m_New2OldParaParam.nNewPara;///<�����¾���Ƶ�ζ�����Ϣ
		m_FusionParam++;///<��Ƶ�ںϲ�������һ
		if (m_FusionParam >=6)
		//if (m_FusionParam >=8)
		{///�ں�Ϊͬһ����Ƶ�Ķ�����������Χ
			m_segIDParam = 1;///<����segID����
			m_New2OldParaParam.nNewPara++;///<�ں��¶κ�����һ
			m_FusionParam = 0;///<������Ƶ�ںϲ���
			return;///<����
		}
	}
	else
	{
		///���ڶ�̬��������Ŀ�����󣬱�ʾ�˶�Ŀ��仯��
		m_segIDParam = m_segIDCount;///<segID�������ڵ�ǰ����������
		m_New2OldParaParam.nOldPara = m_VideoFGParam.nOldPara;///<�ں��¶κŵ��ڵ�ǰ�ɶκ�
		if (m_FusionParam >=4)
		//if (m_FusionParam >=6)
		{///�ں�Ϊͬһ����Ƶ�Ķ�����������Χ
			m_FusionParam = 0;///<������Ƶ�ںϲ���
			m_New2OldParaParam.nNewPara++;///<�ں��¶κ�����һ
		}
		else
		{///�ں�Ϊͬһ����Ƶ�Ķ�����δ������Χ
			m_FusionParam++;///<��Ƶ�ںϲ�������һ
		}
		m_nParaFinal[m_VideoFGParam.nOldPara] = m_New2OldParaParam.nNewPara;///<�����¾���Ƶ�ζ�����Ϣ
	}
}
///@brief CVideo�����Ƶ�ںϺ���
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::VideoFusionProcessing()
{
	if(m_IfContinue == FALSE)///<���������־λΪ�񣬷���
		return;
	bool m_tableExist = false;///<���ݱ��������־λ
	///�ж����ݱ��Ƿ���ȷ����
	if(!m_MysqlSegHandle->IfExistTable(m_tableParams.FGTraceTableName,&m_tableExist))
	{
		AfxMessageBox("���ݿ����");
		return ;
	}
	if(!m_tableExist)
	{
		AfxMessageBox("ԭʼtrace������");
		return;
	}
	m_tableExist = false;
	if(!m_MysqlSegHandle->IfExistTable(m_tableParams.NewToOldFrameTableName,&m_tableExist))
	{
		AfxMessageBox("���ݿ����");
		return ;
	}
	if(!m_tableExist)
	{
		AfxMessageBox("�¾�֡��Ӧ������");
		return;
	}
	
	if (!m_pCapture)///<��Ƶͷָ�벻���ڣ��򷵻�
		return;
	cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES, 1);///<��Ƶͷָ����ڣ����õ�ǰ֡Ϊ��֡
	///��ʼ����Ƶ�ںϲ���
	m_segIDParam   = 0;
	m_FusionParam  = 0;
	m_FusionStart  = 0;
	m_New2OldFrameParam.origFrame = 0;
	m_New2OldFrameParam.newFrame  = 0;
	m_VideoFGParam.nOldPara       = 0;
	///��ʼ�����ں�ͼ��֡����
	CString m_tmpFileName0 = m_strFilePath.c_str();
	CString m_tmpFileName1, m_tmpFileName2;
	GetVideoNameFromAbsolutePath(&m_tmpFileName0,&m_tmpFileName1);///<��ȡ�ļ���(������׺)
	GetFileNameBeforeDot(&m_tmpFileName1,&m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
	m_frameName = "..\\"+ m_tmpFileName2 +"\\new_%d.jpg";

	m_pCombineSegsImage = cvCreateImage(cvSize(m_nVideoW, m_nVideoH), IPL_DEPTH_8U, 3);///<�½�ͼ�񣬴�����Ŀ��
	cvCopy(m_pBGFinal[0], m_pCombineSegsImage);///<��ʼ������Ƶ֡ͼ��Ϊ��ǰ����ͼƬ
			
			

	const int m_nPara4Fusion = 3;
	
	
	///��ʼ��Ƶ�ں�
	while(m_VideoFGParam.nOldPara<FGPara_Count && m_IfContinue)
	{
		if (m_nParaFinal[m_VideoFGParam.nOldPara] == -1)
		{///<��̬�α�������ĿΪ-1ʱ����������
			m_VideoFGParam.nOldPara++;
			continue;
		}
		m_FusionStart = m_FusionParam;               ///<��¼�ں���ʼ���� 
		m_New2OldFrameParam.newFrame = m_FusionStart;///<��¼�ں���ʼ֡��
		m_pNewFrame   = cvCreateImage(cvSize(m_nVideoW, m_nVideoH), IPL_DEPTH_8U, 3);///<�½�����Ƶ֡ͼ�񣬷���ռ�
		for (;m_nParaFinal[m_VideoFGParam.nOldPara]%m_nPara4Fusion == 0;m_VideoFGParam.nOldPara++)
		{///ȡ��һ�����ں�
			m_VideoFGParam.startFrame = m_nFGFinal[m_VideoFGParam.nOldPara];           ///<��ȡ�����ں���ʼ֡��
			m_VideoFGParam.endFrame = m_VideoFGParam.startFrame + m_nFps*m_nSampleTime;///<��ȡ�����ںϽ���֡��
			this->CreateNewFrame();///<��������Ƶ֡
			m_ProcessingSpeed = 4.0+(double)(m_VideoFGParam.nOldPara+1)/(double)FGPara_Count;///<���㴦�����
		}
		cvReleaseImage(&m_pNewFrame);///<�ͷ�����Ƶ֡ͼ��ռ�



		for (int Fus_sample = 1;Fus_sample<m_nPara4Fusion;Fus_sample++)
		{
			m_New2OldFrameParam.newFrame = m_FusionStart;///<�����ں���ʼ֡��
			for(;m_nParaFinal[m_VideoFGParam.nOldPara]%m_nPara4Fusion == Fus_sample;m_VideoFGParam.nOldPara++)
			{///ȡ�ڶ������ں�
				m_VideoFGParam.startFrame = m_nFGFinal[m_VideoFGParam.nOldPara];           ///<��ȡ�����ں���ʼ֡��
				m_VideoFGParam.endFrame = m_VideoFGParam.startFrame + m_nFps*m_nSampleTime;///<��ȡ�����ںϽ���֡��
				this->FusionNewFrame();///<�ں�����Ƶ֡
				m_ProcessingSpeed = 4.0+(double)(m_VideoFGParam.nOldPara+1)/(double)FGPara_Count;///<���㴦�����
			}
		}
		if (m_FusionParam - m_FusionStart<=1)
			return;

		char m_strName[500];         ///<������ʱ����
		for (int k=m_FusionStart;k<m_FusionParam && m_IfContinue;k++)
		{
			sprintf_s(m_strName,m_frameName,k);
			m_pNewFrame = cvLoadImage(m_strName);            ///<��ȡ�ںϺ�����Ƶ֡ͼ��
			cvWriteFrame(m_pVideoWriter4fusion, m_pNewFrame);///<д���ں���Ƶ(Ҳ��ժҪ��Ƶ)
		}
	}
	if (m_VideoFGParam.nOldPara >= FGPara_Count)
	{

		///Ŀ��켣��Ϣ���ǰ������Ϣ��ϲ�ΪNewTraceTable
		if(m_IfContinue &&!m_MysqlSegHandle->Unite2NewTraceTable(m_tableParams.NewTraceTable,m_tableParams.FGTraceTableName,m_tableParams.NewToOldFrameTableName))
		{
			AfxMessageBox("��trace������ʧ��");
			return;
		}
		cvWaitKey(1);
		//m_MysqlSegHandle->DropTable(m_tableParams.FGTraceTableName);      ///<ɾ��Ŀ��켣��Ϣ��
		//cvWaitKey(1);///<�ȴ�ʱ�䣬ȷ��ɾ��ɹ�
		m_MysqlSegHandle->DropTable(m_tableParams.NewToOldFrameTableName);///<ɾ���¾���Ƶ֡���ձ�
		cvWaitKey(1);///<�ȴ�ʱ�䣬ȷ��ɾ��ɹ�
		//m_MysqlSegHandle->DropTable(m_tableParams.VideoFGTableName);      ///<ɾ��ǰ������Ϣ��
		//cvWaitKey(1);///<�ȴ�ʱ�䣬ȷ��ɾ��ɹ�
		if (m_pVideoWriter4fusion!=NULL)
		{
			cvReleaseVideoWriter(&m_pVideoWriter4fusion);
		}
		m_IfDoneFus = true;            ///<��Ƶ�ں���ɱ�־λΪtrue
		//cvWaitKey(1);
		FusFrame_Count = m_FusionParam;///<��¼��Ƶ�ں���֡��
	}
	///������Ƶ�ں�
	cvSaveImage("..\\"+ m_tmpFileName2 +"\\All.jpg", m_pCombineSegsImage);///<��������Ƶ֡ͼ��
	cvReleaseImage(&m_pCombineSegsImage);///<�ͷ�����Ƶ֡ͼ��ռ�

}
///@brief CVideo��Ĵ�������Ƶ֡����
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::CreateNewFrame()
{
	if (m_segIDParam >= m_segIDCount)///<�Ѵ�����ص�����Ƶ֡����������
		return;
	///��ʼ����������Ƶ֡����
	bool m_IfFindStart = true;
	bool m_IfSameFrame = true;
	char m_strName[500];///<������ʱ����

	while (m_IfContinue)
	{
		///��ȡ��ǰ�ں϶���ʼ֡�źͽ���֡��
		if(m_IfContinue &&!m_MysqlSegHandle->GetInfor1DataFromOrigTraceTable(m_segIDParam,&m_traceTab,m_tableParams.FGTraceTableName))
		{
			AfxMessageBox("���ݿ����");
			return;
		}
		if (m_traceTab.origFrame>=m_VideoFGParam.startFrame)
			break;
		else
		{
			m_segIDParam++;
			if (m_segIDParam >= m_segIDCount)
				return;
		}
	}
	///��ʼ��������Ƶ֡
	while (m_IfContinue)
	{
		//0702 needs improve
		m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
		if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ��˳�ѭ��
			return;
		m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��
		if (m_nCurrentFrame>=m_traceTab.origFrame && m_nCurrentFrame<=m_VideoFGParam.endFrame)
		{///��ǰ֡�Ŵ��ڸö�̬�η�Χ�������´���
			m_IfSameFrame = true;
			cvResize(m_pOriFrame, m_pProcessFrame);///<��С
			///��ȡ����ͼƬID
			m_VideoBGParam.BGImgID = (int)(m_VideoFGParam.startFrame+m_VideoFGParam.endFrame)/(2*m_nBGUpdateFrames);
			if (m_VideoBGParam.BGImgID>=BGPara_Count)
				m_VideoBGParam.BGImgID = BGPara_Count-1;
			cvCopy(m_pBGFinal[m_VideoBGParam.BGImgID], m_pNewFrame);///<��ʼ������Ƶ֡ͼ��Ϊ��ǰ����ͼƬ
			///��ʼ�ҵ�һ������
			if(m_IfFindStart)
			{
				if((int)m_nCurrentFrame < m_traceTab.origFrame)
					continue;
				else if ((int)m_nCurrentFrame==m_traceTab.origFrame)
				{
					///��ǰ֡Ϊ���ںϵ�ԭʼ֡
					m_IfFindStart = false;
					///��ȡ�˶�Ŀ����Ϣ
					r.x = m_traceTab.nX;
					r.y = m_traceTab.nY;
					r.width = m_traceTab.nWidth;
					r.height = m_traceTab.nHeight;
					///��ǰ��Ŀ��ͼ��Ƕ���Ӧλ�õ�����Ƶ֡ͼ����
					cvSetImageROI(m_pNewFrame,     r);
					cvSetImageROI(m_pProcessFrame, r);
					cvAddWeighted(m_pProcessFrame, 0.8, m_pNewFrame, 0.2, 0, m_pNewFrame);
					cvResetImageROI(m_pProcessFrame);
					cvResetImageROI(m_pNewFrame);
					
					int temp = m_MysqlSegHandle->FindSegIDFromFGTraceTable(m_tableParams.FGTraceTableName,m_VideoFGParam.nOldPara);
					
					if( m_segIDParam == (temp +1))
					{
								/////��ǰ��Ŀ��ͼ��Ƕ���Ӧλ�õ�����Ƶ֡ͼ����1
						cvSetImageROI(m_pCombineSegsImage,     r);
						cvSetImageROI(m_pProcessFrame, r);
						cvAddWeighted(m_pProcessFrame, 0.5, m_pCombineSegsImage, 0.5, 0, m_pCombineSegsImage);
						if (m_IfContinue &&!m_MysqlSegHandle->InsertData2CombineSegsTable(m_traceTab, m_tableParams.CombineSegsTableName))
						{
							AfxMessageBox("�ϳ�ǰ��ͼ��Ϣ��������");
							return;
						}
						cvResetImageROI(m_pProcessFrame);
						cvResetImageROI(m_pCombineSegsImage);
					}

					if (m_New2OldFrameParam.origFrame!=m_traceTab.origFrame)
					{
						m_New2OldFrameParam.origFrame = m_traceTab.origFrame;
						///�������ݵ��¾���Ƶ֡���ձ�
						if(m_IfContinue &&!m_MysqlSegHandle->InsertData2NewToOldFrameTable(m_New2OldFrameParam,m_tableParams.NewToOldFrameTableName))
						{
							AfxMessageBox("�¾�֡��Ӧ��������ݳ���");
							return;
						}
					}
					m_segIDParam++;///<�ö����ں�Ŀ��������һ
					if (m_segIDParam >= m_segIDCount)
						return;///<�ö����ں�Ŀ���������ö���Ŀ����������
				}
				else
				{
					///��ǰ֡�޷�ƥ�����ݱ�����
					m_segIDParam++;///<�ö����ں�Ŀ��������һ
					if (m_segIDParam >= m_segIDCount)
						return;///<�ö����ں�Ŀ���������ö���Ŀ����������
				}
			}///�����ҵ�һ������

			///ǰ��Ŀ�괦��ԭʼͼ��ͬһ֡�Ĵ���
			while (m_IfSameFrame)
			{
				///��ȡ���ݱ��е�ǰ���ں�֡��Ϣ
				if(m_IfContinue &&!m_MysqlSegHandle->GetInfor1DataFromOrigTraceTable(m_segIDParam,&m_traceTab,m_tableParams.FGTraceTableName))
				{
					AfxMessageBox("��ȡԭʼtrace�����");
					return;
				}
				if (m_traceTab.origFrame > m_VideoFGParam.endFrame)
					break;///<֡�ų����öη�Χ������
				if ((int)m_nCurrentFrame == m_traceTab.origFrame)
				{
					///��ǰ֡Ϊ���ںϵ�ԭʼ֡����ȡ�˶�Ŀ����Ϣ
					r.x = m_traceTab.nX;
					r.y = m_traceTab.nY;
					r.width = m_traceTab.nWidth;
					r.height = m_traceTab.nHeight;
					///��ǰ��Ŀ��ͼ��Ƕ���Ӧλ�õ�����Ƶ֡ͼ����
					cvSetImageROI(m_pNewFrame,     r);
					cvSetImageROI(m_pProcessFrame, r);
					cvAddWeighted(m_pProcessFrame, 0.8, m_pNewFrame, 0.2, 0, m_pNewFrame);
					cvResetImageROI(m_pProcessFrame);
					cvResetImageROI(m_pNewFrame);
					int temp = m_MysqlSegHandle->FindSegIDFromFGTraceTable(m_tableParams.FGTraceTableName,m_VideoFGParam.nOldPara);
					
					if( m_segIDParam == (temp +1))
					{
								/////��ǰ��Ŀ��ͼ��Ƕ���Ӧλ�õ�����Ƶ֡ͼ����2
						cvSetImageROI(m_pCombineSegsImage,     r);
						cvSetImageROI(m_pProcessFrame, r);
						cvAddWeighted(m_pProcessFrame, 0.5, m_pCombineSegsImage, 0.5, 0, m_pCombineSegsImage);
						if (m_IfContinue &&!m_MysqlSegHandle->InsertData2CombineSegsTable(m_traceTab, m_tableParams.CombineSegsTableName))
						{
							AfxMessageBox("�ϳ�ǰ��ͼ��Ϣ��������");
							return;
						}
						cvResetImageROI(m_pProcessFrame);
						cvResetImageROI(m_pCombineSegsImage);
					}
					if (m_New2OldFrameParam.origFrame!=m_traceTab.origFrame)
					{
						m_New2OldFrameParam.origFrame = m_traceTab.origFrame;
						if(m_IfContinue &&!m_MysqlSegHandle->InsertData2NewToOldFrameTable(m_New2OldFrameParam,m_tableParams.NewToOldFrameTableName))
						{
							AfxMessageBox("�¾�֡��Ӧ��������");
							return;
						}
					}
					m_segIDParam++;
					if (m_segIDParam >= m_segIDCount)
						return;///<�ö����ں�Ŀ���������ö���Ŀ����������
				}
				else
				{
					m_IfSameFrame = false;
				}
			}
			
			///ǰ��Ŀ�괦��ԭʼͼ��ͬ֡�Ĵ���
			if (m_IfSameFrame == false)
			{
				sprintf_s(m_strName,m_frameName,m_New2OldFrameParam.newFrame);
				cvSaveImage(m_strName, m_pNewFrame);///<��������Ƶ֡
				m_New2OldFrameParam.newFrame++;     ///<����Ƶ֡������һ
				m_FusionParam++;                    ///<��Ƶ�ںϲ�������һ
			}
		}
		if (m_nCurrentFrame > m_VideoFGParam.endFrame)
			break;///<��ǰ֡�ų����ö�̬�η�Χ���˳�ѭ��
	}
	///������������Ƶ֡
	m_FusionParam = MAX(m_FusionParam, m_New2OldFrameParam.newFrame);///<����ö�����Ƶ��֡��
}
///@brief CVideo����ں�����Ƶ֡����
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CVideo::FusionNewFrame()
{
	if (m_segIDParam >= m_segIDCount)///<�Ѵ�����ص�����Ƶ֡����������
		return;
	///��ʼ���ں�����Ƶ֡����
	bool m_IfFindStart = true;
	bool m_IfSameFrame = true;
	char m_strName[500];///<������ʱ����

	while (m_IfContinue)
	{///��ȡ��ǰ�ں϶���ʼ֡�źͽ���֡��
		if(m_IfContinue &&!m_MysqlSegHandle->GetInfor1DataFromOrigTraceTable(m_segIDParam,&m_traceTab,m_tableParams.FGTraceTableName))//�ɶ���֡
		{
			AfxMessageBox("��ȡԭʼtrace�����");
			return;
		}
		if (m_traceTab.origFrame>=m_VideoFGParam.startFrame)
			break;
		else
		{
			m_segIDParam++;
			if (m_segIDParam >= m_segIDCount)
				return;
		}
	}
	///��ʼ�ں�����Ƶ֡
	while (m_IfContinue)
	{
		m_pOriFrame = cvQueryFrame(m_pCapture);///<��ȡ��ǰ֡ͼ��
		if (!m_pOriFrame)///<��ȡ֡ͼ��ʧ�ܣ��˳�ѭ��
			return;
		m_nCurrentFrame = (int)cvGetCaptureProperty(m_pCapture, CV_CAP_PROP_POS_FRAMES);///<��ȡ��ǰ֡��
		if (m_nCurrentFrame>=m_traceTab.origFrame && m_nCurrentFrame<=m_VideoFGParam.endFrame)
		{///��ǰ֡�Ŵ��ڸö�̬�η�Χ�������´���
			m_IfSameFrame = true;
			cvResize(m_pOriFrame, m_pProcessFrame);///<��С
			if (m_New2OldFrameParam.newFrame < m_FusionParam)
			{///����Ƶ֡�Ѵ��ڣ����ȡ����Ƶ֡
				sprintf_s(m_strName,m_frameName,m_New2OldFrameParam.newFrame);
				m_pNewFrame = cvLoadImage(m_strName);
			}
			else
			{
				///����Ƶ֡�����ڣ��򴴽�����Ƶ֡
				m_VideoBGParam.BGImgID = (int)(m_VideoFGParam.startFrame+m_VideoFGParam.endFrame)/(2*m_nBGUpdateFrames);
				if (m_VideoBGParam.BGImgID>=BGPara_Count)
					m_VideoBGParam.BGImgID = BGPara_Count-1;

				m_pNewFrame = cvCreateImage(cvSize(m_nVideoW, m_nVideoH), IPL_DEPTH_8U, 3);
				cvCopy(m_pBGFinal[m_VideoBGParam.BGImgID], m_pNewFrame);
			}

			///��ʼ�ҵ�һ������
			if(m_IfFindStart)
			{
				if((int)m_nCurrentFrame < m_traceTab.origFrame)
					continue;
				else if ((int)m_nCurrentFrame==m_traceTab.origFrame)
				{
					///��ǰ֡Ϊ���ںϵ�ԭʼ֡
					m_IfFindStart = false;
					///��ȡ�˶�Ŀ����Ϣ
					r.x = m_traceTab.nX;
					r.y = m_traceTab.nY;
					r.width = m_traceTab.nWidth;
					r.height = m_traceTab.nHeight;
					///��ǰ��Ŀ��ͼ��Ƕ���Ӧλ�õ�����Ƶ֡ͼ����
					cvSetImageROI(m_pNewFrame,     r);
					cvSetImageROI(m_pProcessFrame, r);
					cvAddWeighted(m_pProcessFrame, 0.8, m_pNewFrame, 0.2, 0, m_pNewFrame);
					cvResetImageROI(m_pProcessFrame);
					cvResetImageROI(m_pNewFrame);

					int temp = m_MysqlSegHandle->FindSegIDFromFGTraceTable(m_tableParams.FGTraceTableName,m_VideoFGParam.nOldPara);
					
					if( m_segIDParam == (temp +1))
					{
								/////��ǰ��Ŀ��ͼ��Ƕ���Ӧλ�õ�����Ƶ֡ͼ����
						cvSetImageROI(m_pCombineSegsImage,     r);
						cvSetImageROI(m_pProcessFrame, r);
						cvAddWeighted(m_pProcessFrame, 0.5, m_pCombineSegsImage, 0.5, 0, m_pCombineSegsImage);
						if (m_IfContinue &&!m_MysqlSegHandle->InsertData2CombineSegsTable(m_traceTab, m_tableParams.CombineSegsTableName))
						{
							AfxMessageBox("�ϳ�ǰ��ͼ��Ϣ��������");
							return;
						}
						cvResetImageROI(m_pProcessFrame);
						cvResetImageROI(m_pCombineSegsImage);
					}

					if (m_New2OldFrameParam.origFrame!=m_traceTab.origFrame)
					{
						m_New2OldFrameParam.origFrame = m_traceTab.origFrame;
						if(!m_MysqlSegHandle->InsertData2NewToOldFrameTable(m_New2OldFrameParam,m_tableParams.NewToOldFrameTableName))
						{
							AfxMessageBox("�¾�֡��Ӧ��������");
							return;
						}
					}
					m_segIDParam++;
					if (m_segIDParam >= m_segIDCount)
						return;///<�ö����ں�Ŀ���������ö���Ŀ����������
				}
				else
				{
					m_segIDParam++;
					if (m_segIDParam >= m_segIDCount)
						return;
				}
			}///�����ҵ�һ������

			///ǰ��Ŀ�괦��ԭʼͼ��ͬһ֡�Ĵ���
			while (m_IfSameFrame)
			{
				///��ȡ���ݱ��е�ǰ���ں�֡��Ϣ
				if(!m_MysqlSegHandle->GetInfor1DataFromOrigTraceTable(m_segIDParam,&m_traceTab,m_tableParams.FGTraceTableName))
				{
					AfxMessageBox("��ȡԭʼtrace�����");
					return;
				}
				if (m_traceTab.origFrame > m_VideoFGParam.endFrame)
					break;///<֡�ų����öη�Χ������
				if ((int)m_nCurrentFrame == m_traceTab.origFrame)
				{
					///��ǰ֡Ϊ���ںϵ�ԭʼ֡����ȡ�˶�Ŀ����Ϣ
					/*r.x = m_traceTab.nLeft;
					r.y = m_traceTab.nTop;
					r.width = m_traceTab.nRight - m_traceTab.nLeft;
					r.height = m_traceTab.nBottom - m_traceTab.nTop;*/
					r.x = m_traceTab.nX;
					r.y = m_traceTab.nY;
					r.width = m_traceTab.nWidth;
					r.height = m_traceTab.nHeight;
					///��ǰ��Ŀ��ͼ��Ƕ���Ӧλ�õ�����Ƶ֡ͼ����
					cvSetImageROI(m_pNewFrame,     r);
					cvSetImageROI(m_pProcessFrame, r);
					cvAddWeighted(m_pProcessFrame, 0.8, m_pNewFrame, 0.2, 0, m_pNewFrame);
					cvResetImageROI(m_pProcessFrame);
					cvResetImageROI(m_pNewFrame);

					int temp = m_MysqlSegHandle->FindSegIDFromFGTraceTable(m_tableParams.FGTraceTableName,m_VideoFGParam.nOldPara);
					
					if( m_segIDParam == (temp +1))
					{
								/////��ǰ��Ŀ��ͼ��Ƕ���Ӧλ�õ�����Ƶ֡ͼ����
						cvSetImageROI(m_pCombineSegsImage,     r);
						cvSetImageROI(m_pProcessFrame, r);
						cvAddWeighted(m_pProcessFrame, 0.5, m_pCombineSegsImage, 0.5, 0, m_pCombineSegsImage);
						if (m_IfContinue &&!m_MysqlSegHandle->InsertData2CombineSegsTable(m_traceTab, m_tableParams.CombineSegsTableName))
						{
							AfxMessageBox("�ϳ�ǰ��ͼ��Ϣ��������");
							return;
						}
						cvResetImageROI(m_pProcessFrame);
						cvResetImageROI(m_pCombineSegsImage);
					}

					if (m_New2OldFrameParam.origFrame!=m_traceTab.origFrame)
					{
						m_New2OldFrameParam.origFrame = m_traceTab.origFrame;
						if(m_IfContinue &&!m_MysqlSegHandle->InsertData2NewToOldFrameTable(m_New2OldFrameParam,m_tableParams.NewToOldFrameTableName))
						{
							AfxMessageBox("�¾�֡��Ӧ��������");
							return;
						}
					}
					m_segIDParam++;
					if (m_segIDParam >= m_segIDCount)
						return;///<�ö����ں�Ŀ���������ö���Ŀ����������
				}
				else
				{
					m_IfSameFrame = false;
				}
			}
			///ǰ��Ŀ�괦��ԭʼͼ��ͬ֡�Ĵ���
			if (m_IfSameFrame == false)
			{
				sprintf_s(m_strName,m_frameName,m_New2OldFrameParam.newFrame);
				cvSaveImage(m_strName, m_pNewFrame);///<��������Ƶ֡ͼ��
				m_New2OldFrameParam.newFrame++;
			}
			if (m_pNewFrame)
				cvReleaseImage(&m_pNewFrame);
		}
		if (m_nCurrentFrame > m_VideoFGParam.endFrame)
			break;///<��ǰ֡�ų����ö�̬�η�Χ���˳�ѭ��
	}
	///�����ں�����Ƶ֡
	m_FusionParam = MAX(m_FusionParam, m_New2OldFrameParam.newFrame);///<����ö�����Ƶ��֡��
}
///@brief CVideo����˶�Ŀ����ɫ��������
/// 
///@param[in] ����ͼ��
///@pre  NULL
///@return NULL
///@retval string
///@post NULL
string CVideo::ColorSearch(IplImage* CutImg)
{
	if (!CutImg)
		return "";
	{//��ɫ�������򣬴˴���д��
		if ((int)m_nCurrentFrame%(m_nSamplingRate*3) == 0)
			return "red";
		else if ((int)m_nCurrentFrame%(m_nSamplingRate*3) == 1)
			return "green";
		else
			return "blue";
	}
}
///@brief CVideo����˶�Ŀ���С��������
/// 
///@param[in] ����ͼ���С
///@pre  NULL
///@return NULL
///@retval string
///@post NULL
string CVideo::SizeSearch(CvRect CutRect)
{
	int myCutsize = CutRect.width * CutRect.height;
	if (myCutsize > m_nMaxTargetArea/2)
		return "L";
	else
		return "S";
}

///@brief �����߳̿��ƺ���
/// 
///@param[in] �߳̿��Ʋ���
///@pre  NULL
///@return NULL
///@retval UINT
///@post NULL
UINT BeginSegProcess(LPVOID pParam)
{
	CVideo *pLibHandle = (CVideo*)pParam;///<�̲߳���ת��
	pLibHandle->VideoProcessing();///<���߳̿���
	return 0;
}