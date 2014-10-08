#pragma once
#include "afxwin.h"
#include "vidPlayer.h"
#include "LibMySql.h"
#include "ButtonBeautify.h"
#include "UIbeautify.h"


// picsum �Ի���

class picsum : public CDialogEx
{
	DECLARE_DYNAMIC(picsum)

public:
	picsum(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~picsum();

// �Ի�������
	enum { IDD = IDD_picsum };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void DisplaySumImg();
	vidPlayer playerori_TAB2;
	int m_pagenum;
	int m_pageSum;
	BOOL Generated;
	BOOL UserClick;
	CStatic oriPicture;
	int OriFrame;
	CSliderCtrl Tab2_CSliderPlayer1Ctrl;
	BOOL  If_playpiece;//ԭʼ��Ƶ��ʼ����Ƭ���ñ�־λ;
	void ShowTime(int m_currentFrameNO, int totalFrameCount, int videoTimeInSecond, CWnd *m_pShowTimeWnd, int flag);  ///<������ʾ����ʱ��ĺ���

	afx_msg void OnBnClickeddlg2up();
	afx_msg void OnBnClickeddlg2down();
	//afx_msg void OnBnClickeddlg2generate();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedBtnTab2OriPlay();
	afx_msg void OnBnClickedBtnTab2OriPause();
	afx_msg void OnBnClickedBtnTab2OriStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	virtual void OnCancel();
	int m_clickedObjRecPosInVec;                        ///<��¼���������Ŀ��ROI����m_objectRectVector�е��±��
	int m_distanceToRecCenter;                          ///<�����λ����ROI���ĵ�ľ���
	vector <OrigTraceTable> m_objectOrigTraceTableVector;        ///<���ڴ洢�ں���Ƶ��Ŀ��ROI��OrigTraceTable����
	CDataMySql* Tab2_MysqlVideoParaSearchHandle;
	CVideo* m_videoPro;
	CvRect m_theObjRecClicked;                           ///<��¼����굥����Ŀ��ROI��
	//afx_msg void OnPaint();

	CRect m_rect;
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	POINT old;  

	UIbeautify UIBeautifier;                      ///<������������Ķ���

	CButtonBeautify  Btn_TAB2_PLAY;
	CButtonBeautify  Btn_TAB2_PAUSE;
	CButtonBeautify  Btn_TAB2_STOP;
	CButtonBeautify  Btn_TAB2_UP;
	CButtonBeautify  Btn_TAB2_DOWN;

	CBitmap *BitmapBackGroundStrech;              ///<�����ͼƬ
	CRect rcTabRect;                                    ///<�Ӵ�������
};
