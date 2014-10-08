#pragma once
#include "afxwin.h"
#include "vidPlayer.h"
#include "LibMySql.h"
#include "ButtonBeautify.h"
#include "UIbeautify.h"
#include "VTrack.h"

// drawDetection �Ի���

class drawDetection : public CDialogEx
{
	DECLARE_DYNAMIC(drawDetection)

public:
	drawDetection(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~drawDetection();

// �Ի�������
	enum { IDD = IDD_DRAW_DETECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CProgressCtrl* VTrackPro;
	DECLARE_MESSAGE_MAP()
private:
	vidPlayer player;    ///<������Ƶ���������
	vidPlayer oriPlayer; ///<�����Ƶ���������
	VTrack    tracker;   ///<��Ƶ���������
	bool    m_ifExistProData;               ///<���ݱ��������־λ
	int     numOfObj;                       ///<��Ƶ�˶�Ŀ������
	CString m_curCaseNameText;              ///<��ǰ��������
	CString m_curCameraNameText;            ///<��ǰ��ص�����
	CString m_curVideoPath;                 ///<��ǰ��Ƶ·��
	CString objtablename;                   ///<��ǰ���ݱ���
	CPoint tempDrewPoint1;                  ///<��ǰ����������1
	CPoint tempDrewPoint2;                  ///<��ǰ����������2
	vector<CString>    oriVideoName;        ///<��ǰ��Ƶ���Ƽ���
	vector<objectInfo> objDetectedInfos;	///<�洢���ݿ��й��߻�����������Ϣ��������ʾ����ͼ
	int m_pageNum;							///<��¼��ǰ����ͼ����ʾ��Ϊ�ڼ�ҳ
	int m_pageSum;							///<��¼һҳ���ٸ�����ͼ
	DisplayFrame  m_ShowResult;				///<��ʾͼƬ����
	void DetectResult();					///<ÿ�εõ�m_pageSum��Խ�ߣ��򣩵�Ŀ�꣬���objDetectedInfos��
	void DisplayPageSumImg();				///<��ʾ����ͼ

public:
	friend class Cvideotest2Dlg;    //��Ԫ��
	void ShowTime(int m_currentFrameNO,            ///<������ʾ����ʱ��ĺ���
		int totalFrameCount,
		int videoTimeInSecond, 
		CWnd *m_pShowTimeWnd, int flag);

	CSliderCtrl m_CSlider_playerCtrl;   ///<ԭʼ���Ż������ؼ�����
	CSliderCtrl m_CSlider_oriplayerCtrl;   ///<��������ڶ��������ؼ�����    //�Ķ�
	bool user_click_scrollbar;
	int Video_FrameCount;//��¼��Ƶ����֡�����ڻ������Ĳ�������
	CScrollBar* Draw_Detect_pScrollBar;

	CVideo* draw_videoPro;
	CDataMySql* m_MysqlHandle;

	//UIbeautify UIBeautifier;					///<������������Ķ���
	//CBitmap *BitmapBackGroundStrech;			///<�����ͼƬ
	/////����������ض��󡢱�������
	//CButtonBeautify Btn_PLAY_IN_INTELLI_SEARCH;					///<����
	//CButtonBeautify Btn_PAUSE_IN_INTELLI_SEARCH;				///<��ͣ
	//CButtonBeautify Btn_STOP_IN_INTELLI_SEARCH;					///<ֹͣ
	//CButtonBeautify Btn_FAST_FOWARD_IN_INTELLI_SEARCH;			///<���
	//CButtonBeautify Btn_FAST_BACKWARD_IN_INTELLI_SEARCH;		///<����
	//CButtonBeautify Btn_FRAME_FAST_FOWARD_IN_INTELLI_SEARCH;	///<��֡���     
	//CButtonBeautify Btn_FRAME_FAST_BACKWARD_IN_INTELLI_SEARCH;	///<��֡���� 
	//CButtonBeautify Btn_CLOSE;									///<�˳���ť
	//CButtonBeautify Btn_START_PROCESS_IN_DRAW_DETECT;			///<��ʼ���� 
	//CButtonBeautify Btn_STOP_PROCESS;							///<��ֹ����
	//CButtonBeautify Btn_SCREENSHOT_IN_DRAW_DETECT;				///<��Ƶ��ͼ
	//CButtonBeautify Btn_CLEAR_IN_DRAW_DETECT;					///<��ԭ����
	//CButtonBeautify Btn_SEARCH_IN_DRAW_DETECT;					///<��ʼ���
	//CButtonBeautify Btn_PLAY_IN_INTELLI_SEARCH2;				///<����
	//CButtonBeautify Btn_PAUSE_IN_INTELLI_SEARCH2;				///<��ͣ
	//CButtonBeautify Btn_STOP_IN_INTELLI_SEARCH2;				///<ֹͣ
	//CButtonBeautify Btn_FAST_FOWARD_IN_INTELLI_SEARCH2;			///<���
	//CButtonBeautify Btn_FAST_BACKWARD_IN_INTELLI_SEARCH2;		///<����
	//CButtonBeautify Btn_FRAME_FAST_FOWARD_IN_INTELLI_SEARCH2;   ///<��֡���     
	//CButtonBeautify Btn_FRAME_FAST_BACKWARD_IN_INTELLI_SEARCH2; ///<��֡���� 
	//CButtonBeautify Btn_SCREENSHOT_IN_DRAW_DETECT2;				///<��Ƶ��ͼ
	//CButtonBeautify Btn_SAVEAS_CLUE_IN_DRAW_DETECT;				///<Ϊ��֡��������
	//CButtonBeautify BTN_PAGE_UP_IN_DRAW_DETECT;					///<��һҳ
	//CButtonBeautify BTN_PAGE_DOWN_IN_DRAW_DETECT;				///<��һҳ

	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnPlayInDrawDetect();
	afx_msg void OnBnClickedBtnPauseInDrawDetect();
	afx_msg void OnBnClickedBtnStopInDrawDetect();
	afx_msg void OnBnClickedBtnStartProcess();
	afx_msg void OnBnClickedBtnStopProcess();
	afx_msg void OnBnClickedCheckLineInDrawDetect();
	afx_msg void OnBnClickedCheckRectInDrawDetect();
	afx_msg void OnBnClickedBtnClearInDrawDetect();
	afx_msg void OnBnClickedBtnSearchInDrawDetect();
	afx_msg void OnBnClickedBtnPlayInDrawDetect2();
	afx_msg void OnBnClickedBtnPauseInDrawDetect2();
	afx_msg void OnBnClickedBtnStopInDrawDetect2();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	CBitmap *BitmapBackGroundStrech;

	UIbeautify UIBeautifier;
	CButtonBeautify Btn_BTN1_DRAW_PLAY;
	CButtonBeautify Btn_BTN1_DRAW_PAUSE;
	CButtonBeautify Btn_BTN1_DRAW_STOP;
	CButtonBeautify Btn_BTN2_DRAW_PLAY;
	CButtonBeautify Btn_BTN2_DRAW_PAUSE;
	CButtonBeautify Btn_BTN2_DRAW_STOP;
};
