#pragma once
#include "afxwin.h"
#include "vidPlayer.h"
#include "LibMySql.h"
#include "ButtonBeautify.h"
#include "UIbeautify.h"


// PictureAbsSUBDlg �Ի���

class PictureAbsSUBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PictureAbsSUBDlg)

public:
	PictureAbsSUBDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PictureAbsSUBDlg();

// �Ի�������
	enum { IDD = IDD_picsum };
	
	
	int m_pagenum;
	int m_pageSum;
	int OriFrame;
	int m_clickedObjRecPosInVec;                        ///<��¼���������Ŀ��ROI����m_objectRectVector�е��±��
	int m_distanceToRecCenter;                          ///<�����λ����ROI���ĵ�ľ���
	BOOL Generated;
	BOOL UserClick;
	BOOL  If_playpiece;//ԭʼ��Ƶ��ʼ����Ƭ���ñ�־λ;
	CStatic oriPicture;
	CSliderCtrl Tab2_CSliderPlayer1Ctrl;
	vidPlayer playerori_TAB2;
	
	afx_msg void OnBnClickeddlg2up();
	afx_msg void OnBnClickeddlg2down();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedBtnTab2OriPlay();
	afx_msg void OnBnClickedBtnTab2OriPause();
	afx_msg void OnBnClickedBtnTab2OriStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	
	vector <OrigTraceTable> m_objectOrigTraceTableVector;        ///<���ڴ洢�ں���Ƶ��Ŀ��ROI��OrigTraceTable����
	CDataMySql* Tab2_MysqlVideoParaSearchHandle;
	CVideo* m_videoPro;
	CvRect m_theObjRecClicked;                           ///<��¼����굥����Ŀ��ROI��
	CRect m_rect;
	CRect rcTabRect;                                    ///<�Ӵ�������
	CBitmap *BitmapBackGroundStrech;              ///<�����ͼƬ
	POINT old;

	UIbeautify UIBeautifier;                      ///<������������Ķ���
	CButtonBeautify  Btn_TAB2_PLAY;
	CButtonBeautify  Btn_TAB2_PAUSE;
	CButtonBeautify  Btn_TAB2_STOP;
	CButtonBeautify  Btn_TAB2_UP;
	CButtonBeautify  Btn_TAB2_DOWN;

	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	void DisplaySumImg();
	void ShowTime(int m_currentFrameNO, int totalFrameCount, int videoTimeInSecond, CWnd *m_pShowTimeWnd, int flag);  ///<������ʾ����ʱ��ĺ���


protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
