#pragma once
#include "ButtonBeautify.h"
#include "UIbeautify.h"

// Dialog1 �Ի���

class Dialog1 : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog1)

public:
	Dialog1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dialog1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

//ʵ��
public:
	bool Tab1_ifStartPro;          ///<�Ƿ���������ժҪ
	BOOL  Tab1_playpiece;//ԭʼ��Ƶ��ʼ����Ƭ���ñ�־λ;
	//������
	CSliderCtrl Tab1_CSliderPlayer1Ctrl;   ///<����һ�������ؼ�����
	CSliderCtrl Tab1_CSliderPlayer2Ctrl;   ///<���ڶ��������ؼ�����
	vidPlayer Tab1_Player1;
	vidPlayer Tab1_Player2;
	CDataMySql* Tab1_MysqlHandle;
	vector <CvRect> Tab1_objectRectVector;                  ///<���ڴ洢�ں���Ƶ��Ŀ��ROI��CvRect����
	CvRect Tab1_theObjRecClicked;                           ///<��¼����굥����Ŀ��ROI��
	int Tab1_clickedObjRecPosInVec;                        ///<��¼���������Ŀ��ROI����m_objectRectVector�е��±��
	int Tab1_distanceToRecCenter;                          ///<�����λ����ROI���ĵ�ľ���
	CString Tab1_PathName;	
	CVideo* Tab1_videoPro;
	CProgressCtrl* Tab1_Pro;
	HICON m_hIcon;
public:
	void ViewAbs();
	void ShowTime(int m_currentFrameNO,            ///<������ʾ����ʱ��ĺ���
		int totalFrameCount,
		int videoTimeInSecond,
		CWnd *m_pShowTimeWnd, int flag);
	//afx_msg void OnBnClickedButton9();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnTab1OriPause();
	afx_msg void OnBnClickedBtnTab1OriStop();
	afx_msg void OnBnClickedBtnTab1AbsStop();
	afx_msg void OnBnClickedBtnTab1AbsPlay();
	afx_msg void OnBnClickedBtnTab1AbsPause();
	afx_msg void OnBnClickedBtnTab1GenerateAbs();
	//afx_msg void OnBnClickedBtnTab1ViewAbs();
	afx_msg void OnBnClickedBtnTab1OriPlay();
	afx_msg void OnBnClickedCheckTab1();


	CRect m_rect;
	POINT old;  

	UIbeautify UIBeautifier;                      ///<������������Ķ���
	CButtonBeautify Btn_GENERATE_ABS;
	CButtonBeautify Btn_BTN1_PLAY;
	CButtonBeautify Btn_BTN1_PAUSE;
	CButtonBeautify Btn_BTN1_STOP;
	CButtonBeautify Btn_BTN2_PLAY;
	CButtonBeautify Btn_BTN2_PAUSE;
	CButtonBeautify Btn_BTN2_STOP;

	CBitmap *BitmapBackGroundStrech;              ///<�����ͼƬ
	CRect rcTabRect;                                    ///<�Ӵ�������
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
};
