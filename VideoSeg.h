/**
*@file  VideoSeg.h
*@brief ʵ����Ƶ�ָ��ںϹ��ܣ�������ƵժҪ��
*
*��Ҫģ�飺��Ƶ��������Ƶ�ָ������ȡ��ǰ����ȡ������Ƶ�ںϣ�ժҪ���ɣ���
*
*
*@author ���� lu ying&&zhang nan nan ,����email��
*@version �汾��(0.0)
*@data 2012-8-21
*/
#pragma  once
#include "stdafx.h"
#include "publicheader.h"
#include "LibMySql.h"
#include "GlobalFunctions.h"
#include "opencv2\legacy\legacy.hpp"
#include  "opencv2\video\background_segm.hpp"


#define SEG_L_RATIO  0.05 ///<���������ص����ռ����ͼ�İٷֱ�
#define SEG_M_RATIO  0.01 ///<���������ص����ռ����ͼ�İٷֱ�
//#define VideoConnection_Is_On  1  ///<��Ƶƴ�Ӻ�������


///@brief ������Ƶ�ں���������ݱ�����
///
///�ýṹ�������Ƶ�ں���������ݱ�����
///
///@invariant
///
typedef struct _TableParams
{
	CString VideoFGTableName;       ///<ǰ������Ϣ����
	CString FGTraceTableName;       ///<�˶�����켣����
	CString NewToOldFrameTableName; ///<�¾���Ƶ֡���ձ���
	CString NewTraceTable;          ///<Ŀ��켣��Ϣ����
}TableParams;

///@brief ������Ƶ�ں���
///
///���������Ƶ�������ָ�ں������ֹ��ܡ�
///
///@invariant
///

using namespace cv;

class CVideo
{
public:
	CVideo();
	~CVideo();
public:
    ///DoSegmentation
	int    DoProcessing(const char* pFilePath);///<��ʼ���������߳�
	double ProcessingSpeed();///<��õ�ǰ�������
	void   StopProcessing(); ///<��ֹ�������
	int    VideoOriCount();  ///<����ԭʼ��Ƶ��֡��
	int    VideoSegCount();  ///<���طָ���Ƶ��֡��
	int    VideoFusCount();  ///<�����ں���Ƶ��֡��
public:
	///Segmentation Processing
	void VideoProcessing();///<��Ƶ�ָ��ں��ܿغ���

	///Initialization
	int Initialization(const char *pVideoPath);///<��Ƶ������ʼ��
	int InitSampleSetting();     ///<��ʼ��ѹ������
	void InitStorage();          ///<��ʼ��ͼ�����ݣ�����ռ�
	void InitGaussParam();       ///<��ʼ����˹ģ��
	void InitTableParam();       ///<��ʼ�����ݿ��
	void InitAbstractVideo(const char* pVideoPath);///<��ʼ��ժҪ��Ƶ����

	///Video Segmentation Processing
	void VideoParaProcessing();  ///<��Ƶ�ֶ�
	void VideoBGProcessing();    ///<��Ƶ������ȡ
	void VideoFGProcessing();    ///<��Ƶǰ���з�
	void ParaSegmentation();     ///<��Ƶ�ֶ��㷨
	void FGSegmentation();       ///<��Ƶǰ���з��㷨
	void VideoConnection();      ///<�ָ���Ƶƴ��
	void TimeLineRestructed();   ///<ʱ�����ع�
	
	///Video Fusion Processing
	void VideoFusionProcessing();///<��Ƶ�ں�
	void CreateNewFrame();       ///<��������Ƶ֡
	void FusionNewFrame();       ///<�ں�����Ƶ֡

	///Video Character Processing
	string ColorSearch(IplImage *CutImg);   ///<�˶�Ŀ����ɫ����
	string SizeSearch(CvRect CutRect);      ///<�˶�Ŀ���С����

	///�ڲ�������˽�г�Ա
private:
	CDataMySql        *m_MysqlSegHandle;      ///<��Ƶ�ں����ݱ���

	CvCapture         *m_pCapture;            ///<��Ƶ�ļ����    
	CvGaussBGModel    *m_pGaussBGModel;       ///<��˹ģ��
	CvGaussBGStatModelParams *m_pGaussParams; ///<��˹ģ�Ͳ���
	BackgroundSubtractorMOG2 m_pBGSubMOG2;  //�°�ǰ��������



	CvSeq        *m_pCont;          ///<�˶�Ŀ������ָ��
	CvMemStorage *m_pStor;          ///<�˶�Ŀ�������洢�ռ�ָ��

	IplImage *m_pOriFrame;          ///<δ���������ԭʼ֡(3ͨ��)
	IplImage *m_pProcessFrame;      ///<��������Ƶ֡(3ͨ��)
//	IplImage *m_pResizeFrame;       ///<����ѹ�����֡(3ͨ��)
	
	Mat m_ResizeFrameMat;       ///<����ѹ�����֡(3ͨ��)
	Mat m_GrayResizeFrameMat;  ///<�����ҶȻ���ѹ����ͼƬ(1ͨ��)
    Mat foregroundMat;

//	IplImage *m_pGrayResizeFrame;   ///<�����ҶȻ���ѹ����ͼƬ(1ͨ��)
	IplImage *m_pBGFrame;           ///<����ͼƬ(3ͨ��)
	IplImage *m_pBGFinal[10];       ///<��ȡ���ı���ͼƬ(3ͨ��)
	IplImage *m_pNewFrame;          ///<�ںϺ������Ƶ֡(3ͨ��)

	CvVideoWriter *m_pVideoWriter4seg;   ///<��Ƶ�ָ�дָ��
	CvVideoWriter *m_pVideoWriter4fusion;///<��Ƶ�ں�дָ��

	int   m_nBGFinal[10];       ///<��ȡ����ͼ�ľ�̬�η�Χ
	int   m_nFGFinal[1000];     ///<��ȡǰ��ͼ�ľ�̬�η�Χ
	int   m_nParaFinal[1000];   ///<���ںϵĶ�̬�η�Χ

	IplImage *m_pGrayFrame; 
	cv::Mat m_FrameMat;          ///<��Ƶͼ������(3ͨ��)
	cv::Mat m_BGMat;             ///<����ͼ������(3ͨ��)
	CvMat *m_pGrayFrameMat;      ///<��Ƶͼ������(1ͨ��)
	CvMat *m_pGrayBGMat;         ///<����ͼ������(1ͨ��)
	CvMat *m_pGrayFGMat;         ///<ǰ��ͼ������(1ͨ��)

	int m_nCurrentFrame;         ///<��ǰ֡���
	int m_nFps;                  ///<��ǰ��ƵĬ��֡��
	int m_nTotalFrame;           ///<��ǰ��Ƶ��֡��
	int m_nTotalFrameToDo;       ///<�ܴ���ʱ��            Ĭ�ϴ�������֡
	int m_nSampleTime;           ///<��������              Ĭ��5��
	int m_nSamplingRate;         ///<������ �������        
	int m_nCompressionRatioW;    ///<��Ƶ֡���ѹ����         Ĭ��16     
	int	m_nCompressionRatioH;    ///<��Ƶ֡�߶�ѹ����         Ĭ��16
	int m_nProcessingRatio;      ///<��Ƶ֡��С�������
	
	int m_nBGUpdateFrames;       ///<����������֡��        Ĭ��m_nTotalFrameToDo/9
	int m_nBGUpdateSampleFrame;  ///<�������²���֡��      Ĭ��m_nBGUpdateFrames/20
	double m_rFGSegThreshold;       ///<ǰ���з�����Ӧ��ֵ

	int m_nVideoW;               ///<��Ƶ֡���
	int m_nVideoH;               ///<��Ƶ֡�߶�
	int m_nVideoResizeW;         ///<��Ƶ֡ѹ������
	int m_nVideoResizeH;         ///<��Ƶ֡ѹ����߶�
	int m_nMaxTargetArea;        ///<�˶�Ŀ��������
	int m_nMinTargetArea;        ///<�˶�Ŀ����С���

	//char m_strName[500];         ///<������ʱ����
	//char m_tempFile[100];        ///<�ݴ��ں�ͼ����ļ�������
	CString m_frameName;         ///<�ں�ͼ����

	CvRect r;                    ///<������ʱ����

	int SegFrame_Count;
	int FGPara_Count;           ///<��ȡǰ�����ܶ���
	int BGPara_Count;           ///<��ȡ�������ܶ���      
    int m_segIDCount;           ///<ÿһ�ε�segID����Ŀ
	int m_segIDParam;           ///<segID��������ʼ������Ϊ��
	int m_FusionParam;          ///<��Ƶ�ںϲ���
	int m_FusionStart;          ///<��Ƶ�ں���ʼ����ж�����

	CString m_newTraceTextPath; ///<����fgtrace���txt�ļ�·��
	ofstream m_newTraceOfstream;///<����fgtrace���txt�ļ�����

	///�ⲿ�ӿ���ر��� - ��һ��Ϊ���ⲿ��ȡ	
public:
	bool   m_IfContinue;            ///<���������־λ
	double m_ProcessingSpeed;       ///<��ǰ�������
	string m_strFilePath;           ///<��Ƶ·��

	///��Ƶ���ݱ���Ϣ
	TableParams        m_tableParams;       ///<������Ϣ
	VideoBGTable       m_VideoBGParam;      ///<��Ƶ������Ϣ
	VideoFGTable       m_VideoFGParam;      ///<��Ƶǰ����Ϣ
	OrigTraceTable     m_traceTab;          ///<trace����Ϣ
	NewToOldParaTable  m_New2OldParaParam;  ///<�¾ɶ���Ϣ
	NewToOldFrameTable m_New2OldFrameParam; ///<�¾�֡��Ϣ

	///��Ƶ�ںϲ�����Ϣ
	string strSegVideoNewName;   ///<���ɵķָ���Ƶ��·��
	string strFusionVideoNewName;///<���ɵ��ں���Ƶ��·��
	bool m_IfDoneSeg;            ///<��Ƶ�ָ���ɱ�־λ
	bool m_IfDoneFus;            ///<��Ƶ�ں���ɱ�־λ
	int FusFrame_Count;          ///<��Ƶ�ں���֡��
};

UINT BeginSegProcess(LPVOID pParam);///<�����߳̿��ƺ���