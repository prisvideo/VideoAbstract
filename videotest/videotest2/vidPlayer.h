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
	int canDraw;        ///<����(��)��־λ(����DrawDetectionSUBDlg��Ч)
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

	int m_currentFrameNO;//��ǰ֡��
	int m_lastFrameNO;
	int m_startFrameNO;//֡ͷ�ţ��������ļ�ʱӦ��ʹcurrent = start
	int m_endFrameNO;//֡δ��
	int m_videoTimeInSecond;  //������Ƶ�ĳ���
	int m_CurrentTimeInSecond;//����Ϊ��λ�ĵ�ǰʱ��
	int CSliderPos;    //������λ��
	int m_playState;//����״̬
	double m_timeGap;//����ʱ��֡��ʱ���
	double m_fps;//֡��
	double d_AbsVideoTimeRatio; //totalFrameCount--��֡��*videoTimeInSecond--��Ƶʱ�䳤�ȣ�s��
	CvSize m_size;//��¼��Ƶ����ߴ�
	IplImage *m_curFrame;//��ǰָ֡��
	IplImage *m_curFrameCopy;
	BOOL threadRunOrNot;//����״̬����or��
	CString m_windowName;//��ǰ���̿��Ƶ�CV������
	CString m_filePath;
	DisplayFrame disPlayImage;//������Ƕ���Ŵ��ڵĶ���
	BOOL m_gotCVlclick;
	BOOL playInitial(CWnd *pWnd, CString windowName);
	UINT playProcess();
	BOOL play();
	BOOL pause();
	BOOL stop();
	BOOL fastForward();
	BOOL fastBackward();
	BOOL fastForwardByFrame();
	BOOL fastBackwardByFrame();
	BOOL stopPlay();
	BOOL playPiece(); //����Ƭ��ʱ�����ⲿ������setCaptureProperty
	bool bEditIsChange; //<Edit Control�ı�־λ
	CWnd *m_pShowTimeWnd;       //��ʾ����ʱ��ľ��
	IplImage *screenShot();
	CPoint m_clickPosInCVWnd;///<��¼��������ĵ�
	CPoint m_lBtnDownPosInCVWnd;///<��¼������µĵ�
	CPoint m_lBtnUpPosInCVWnd;///<��¼�������ĵ�
	CDataMySql* m_MysqlVideoParaSearchHandle;
	CVideo *m_videoPro;
	vector<CvPoint> TimePosition;
	vector<int> Time;
	vector<CvRect> ROI;
	CRect PlaywindowRect;       //���Ŵ���ԭʼ��С
	int m_origPara;
	bool timeshow;
	void ShowTime();  //��ʾ��ǰ���Ž���ʱ��
	void ShowTime(int m_currentFrameNO,            ///<������ʾ����ʱ��ĺ���
		int totalFrameCount,
		int videoTimeInSecond,
		CWnd *m_pShowTimeWnd, int flag);
	void SetUrl(LPCTSTR lpszNewValue);
//*************************************************************************
///@�ֻ��ⲿ��������Ա
///@0924 ChenYJ
	IplImage *frameCopyForDraw; ///<��ʾ֡
	bool m_IfStartDetect;       ///<�ֻ��⿪ʼ����־λ
	int  m_drawDetectFlag;      ///<�ֻ���״̬��־λ
	vector<int>   objectIDs;    ///<�˶�Ŀ��ID���ϣ����������
	vector<CPoint> pointsToShow;///<�˶�Ŀ��켣�㼯��
	vector<CRect>  RectToShow;  ///<�˶�Ŀ��Rect����
	int m_clickObjectID;        ///<�������������˶�Ŀ��ID
	inline BOOL playInDrawDetection();   ///<����״̬�µ��˶�Ŀ����
	inline BOOL pauseInDrawDetection();  ///<��ͣ״̬�µ��˶�Ŀ����
	BOOL drawDetection(vector <CPoint> twoPoints, IplImage *img, int flag);///<ͼ��֡���켣
	BOOL drawROI(vector <CvRect> rect, CvScalar rectColor, int thickness);  ///<ͼ��֡����
	inline void UpdatePlayData(int flag);///<����״̬�µ����ݸ���
	inline void UpdatePauseData();       ///<��ͣ״̬�µ����ݸ���
	CDataMySql *m_MysqlObjHandle;///<�ڲ����ݿ��������ڲ�ѯObjectTable
	CString objtablename;       ///<ObjectTable���ݱ���
	vector<CRect> TempRect;     ///<�˶�Ŀ��Rect���ϣ���ʱ������
	vector<int>   TempObjectID; ///<�˶�Ŀ��ID���ϣ���ʱ������
	CPoint m_clickPoint;	    ///<������������

protected:
	CWnd *m_pWnd;               //��ʾ��Ƶ�Ĵ��ھ��
	CWinThread *m_threadControl;//���̿���
};

UINT RunPlayProcess(LPVOID controlNO);
void cvMouseHandler(int eventType,int x,int y,int flags, void *param);
CString absOriNameTansf(CString nameIn);
