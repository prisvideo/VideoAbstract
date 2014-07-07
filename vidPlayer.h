/**
*@file  vidPlayer.h
*@brief ��Ƶ������Ķ��塣
*
*���ļ���������Ƶ���������ع��ܡ�
*@data 2014-06-04
*/

#pragma  once
#include "afxwin.h"
#include "publicheader.h"
#include "DisplayFrame.h"
#include <vector>
#include "LibMySql.h"
#include "VideoSeg.h"
using std::vector;

#define PLAY_STATE_PLAY                 0///<����   
#define PLAY_STATE_PAUSE                1///<��ͣ
#define PLAY_STATE_FAST_FORWORD         2///<���
#define PLAY_STATE_FAST_BACKWORD	    3///<����
#define PLAY_STATE_FRAME_FAST_FORWORD   4///<��֡���
#define PLAY_STATE_FRAME_FAST_BACKWORD  5///<��֡����
#define PLAY_STATE_STOP                 6///<��ֹ
#define PLAY_STATE_SCREEN_SHOT          7///<����
#define PLAY_STATE_PLAY_PIECE           8///<���Ŀ���󣬽���Ƭ�β���


/*********************************************
Struct:        pointForCvMouse 
Description:   ����cvMouseHandler�������⴫�ݵ���¼��Ĳ���
Author:        Lu Ying
Date:          2012-9-11
*********************************************/
typedef struct _pointForCvMouse
{
	int x;			    ///<�����������x
	int y;				///<�����������y
	int x1;				///<�����������x
	int y1;				///<�����������y
	BOOL lBtnUp;		///<��������־λ
	BOOL clickInCVwnd;  ///<�����Ƶ���Ŵ���(��ͣ״̬��Ч)
	BOOL clickInBPwnd;  ///<�����ʾͼƬ����(����ǿ���Ч)
	int canDraw;        ///<����(��)��־λ(����drawDetection��Ч)
}pointForCvMouse;

/*********************************************
Class:         vidPlayer 
Description:   ������Ƶ���ţ������߳̿��������ڳ�ʼ�������Ų����ȣ�
Author:        Lu Peng&Chen Daiwu
Date:          2012-8-24
*********************************************/
class vidPlayer
{

public:
	vidPlayer();
	~vidPlayer();

public:
	CString m_filePath;
	int m_currentFrameNO;//��ǰ֡��
	int m_lastFrameNO;
	int m_startFrameNO;//֡ͷ�ţ��������ļ�ʱӦ��ʹcurrent = start
	int m_endFrameNO;//֡δ��
	CvSize m_size;//��¼��Ƶ����ߴ�
	double m_fps;//֡��
	int m_playState;//����״̬
	double m_timeGap;//����ʱ��֡��ʱ���
	IplImage *m_curFrame;//��ǰָ֡��
	IplImage *m_curFrameCopy;
	BOOL threadRunOrNot;//����״̬����or��
	CString m_windowName;//��ǰ���̿��Ƶ�CV������
	DisplayFrame disPlayImage;//������Ƕ���Ŵ��ڵĶ���
	int m_videoTimeInSecond;  //������Ƶ�ĳ���
	int m_CurrentTimeInSecond;//����Ϊ��λ�ĵ�ǰʱ��
	BOOL m_gotCVlclick;//

	


	double d_AbsVideoTimeRatio; //totalFrameCount--��֡��*videoTimeInSecond--��Ƶʱ�䳤�ȣ�s��

	//CWnd *m_SliderCtrl;
	int CSliderPos;    //������λ��
	CWnd *m_pShowTimeWnd;       //��ʾ����ʱ��ľ��

	bool bEditIsChange; //<Edit Control�ı�־λ
	
protected:
	CWnd *m_pWnd;               //��ʾ��Ƶ�Ĵ��ھ��
	CWinThread *m_threadControl;//���̿���

public:
	BOOL playInitial(CWnd *pWnd, CString windowName);
	UINT playProcess();
	BOOL play();
	BOOL pause();
	BOOL stop();
	BOOL fastForward();
	BOOL fastBackward();
	BOOL fastForwardByFrame();
	BOOL fastBackwardByFrame();
	IplImage *screenShot();
	BOOL drawROI(vector <CRect> rect, CvScalar rectColor, int thickness);  ///<ͼ��֡����
	BOOL stopPlay();

	void ShowTime();  //��ʾ��ǰ���Ž���ʱ��
	BOOL playPiece(); //����Ƭ��ʱ�����ⲿ������setCaptureProperty
    void SetUrl(LPCTSTR lpszNewValue);

	CPoint m_clickPosInCVWnd;///<��¼��������ĵ�
	CPoint m_lBtnDownPosInCVWnd;///<��¼������µĵ�
	CPoint m_lBtnUpPosInCVWnd;///<��¼�������ĵ�
	
	vector<CvPoint> TimePosition;
	vector<int> Time;
	CDataMySql* m_MysqlVideoParaSearchHandle;
	CVideo *m_videoPro;
	bool timeshow;
};

UINT RunPlayProcess(LPVOID controlNO);
void cvMouseHandler(int eventType,int x,int y,int flags, void *param);
CString absOriNameTansf(CString nameIn);
