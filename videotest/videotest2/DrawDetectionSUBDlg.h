#pragma once
#include "afxwin.h"
#include "vidPlayer.h"
#include "LibMySql.h"
#include "ButtonBeautify.h"
#include "UIbeautify.h"
#include "VTrack.h"

// DrawDetectionSUBDlg �Ի���

class DrawDetectionSUBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DrawDetectionSUBDlg)

public:
	DrawDetectionSUBDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DrawDetectionSUBDlg();

// �Ի�������
	enum { IDD = IDD_DRAW_DETECT };

	friend class Cvideotest2Dlg;    //��Ԫ��

	CSliderCtrl m_CSlider_playerCtrl;   ///<ԭʼ���Ż������ؼ�����
	CSliderCtrl m_CSlider_oriplayerCtrl;   ///<��������ڶ��������ؼ�����    //�Ķ�
	CScrollBar* Draw_Detect_pScrollBar;
	CVideo* draw_videoPro;
	CDataMySql* m_MysqlHandle;
	CBitmap *BitmapBackGroundStrech;
	UIbeautify UIBeautifier;
	CButtonBeautify Btn_BTN1_DRAW_PLAY;
	CButtonBeautify Btn_BTN1_DRAW_PAUSE;
	CButtonBeautify Btn_BTN1_DRAW_STOP;
	CButtonBeautify Btn_BTN2_DRAW_PLAY;
	CButtonBeautify Btn_BTN2_DRAW_PAUSE;
	CButtonBeautify Btn_BTN2_DRAW_STOP;

	bool user_click_scrollbar;
	int Video_FrameCount;//��¼��Ƶ����֡�����ڻ������Ĳ�������
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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CProgressCtrl* VTrackPro;
	DECLARE_MESSAGE_MAP()

private:
	vidPlayer player;    ///<������Ƶ���������
	vidPlayer oriPlayer; ///<�����Ƶ���������
	VTrack    tracker;   ///<��Ƶ���������
	CString m_curCaseNameText;              ///<��ǰ��������
	CString m_curCameraNameText;            ///<��ǰ��ص�����
	CString m_curVideoPath;                 ///<��ǰ��Ƶ·��
	CString objtablename;                   ///<��ǰ���ݱ���
	CPoint tempDrewPoint1;                  ///<��ǰ����������1
	CPoint tempDrewPoint2;                  ///<��ǰ����������2
	vector<CString>    oriVideoName;        ///<��ǰ��Ƶ���Ƽ���
	vector<objectInfo> objDetectedInfos;	///<�洢���ݿ��й��߻�����������Ϣ��������ʾ����ͼ
	DisplayFrame  m_ShowResult;				///<��ʾͼƬ����
	bool    m_ifExistProData;               ///<���ݱ��������־λ
	int     numOfObj;                       ///<��Ƶ�˶�Ŀ������
	int m_pageNum;							///<��¼��ǰ����ͼ����ʾ��Ϊ�ڼ�ҳ
	int m_pageSum;							///<��¼һҳ���ٸ�����ͼ

	void DetectResult();					///<ÿ�εõ�m_pageSum��Խ�ߣ��򣩵�Ŀ�꣬���objDetectedInfos��
	void DisplayPageSumImg();				///<��ʾ����ͼ
};
