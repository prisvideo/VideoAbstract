
// videotest2Dlg.h : ͷ�ļ�
/* ȥ��CWMPControls�ؼ��й�ͷ�ļ�
@version �汾��(0.0)
*@data 2014-10-9
*/

#pragma once
#include "publicheader.h"
#include "CvvImage.h"
#include "afxwin.h"  
#include "afxcmn.h"
#include "VideoSeg.h"
#include "Resource.h"
#include "vidPlayer.h"
#include "ObjectViewSUBDlg.h"
#include "LibMySql.h"
#include "VideoAbsSUBDlg.h"
#include "PictureAbsSUBDlg.h"
#include "ButtonBeautify.h"
#include "UIbeautify.h"
#include "WelcomeDlg.h"
#include "DrawDetectionSUBDlg.h"


// Cvideotest2Dlg �Ի���
class Cvideotest2Dlg : public CDialogEx
{
public:
	Cvideotest2Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~Cvideotest2Dlg();
	CDataMySql* m_MysqlVideoParaSearchHandle;
	int m_CurSelTab; 
    VideoAbsSUBDlg m_page1;
	PictureAbsSUBDlg m_page2;
    ObjectViewSUBDlg m_page3;
	DrawDetectionSUBDlg m_page4;
    CDialog* pDialog[4];

// �Ի�������
	enum { IDD = IDD_VIDEOTEST2_DIALOG };

// ʵ��
protected:
	HICON m_hIcon;
	CEdit		m_wndEditFrameNo1;
	CEdit		m_wndEditInputFrameNo1;
	CEdit		m_wndEditInput_nPara;
	int			m_nInputFrameNo1;
	int         SubMenuCheckedNO;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	bool m_ifStartPro;          ///<�Ƿ���������ժҪ
	bool Generated;///<�û��Ƿ����ˡ����ɡ���ť
	TableParams m_tableParams;
	vector<objectInfo> objDetectedInfos;	///<�洢���ݿ��������Ϣ��������ʾ����ͼ
	BOOL  If_playpiece;//ԭʼ��Ƶ��ʼ����Ƭ���ñ�־λ;
	CString PathName;	
	CVideo* m_videoPro;
	CProgressCtrl* myPro;
	vidPlayer player1;
	vidPlayer player2;
	vector <CvRect> m_objectRectVector;                  ///<���ڴ洢�ں���Ƶ��Ŀ��ROI��CvRect����
	vector <OrigTraceTable> m_objectOrigTraceTableVector;        ///<���ڴ洢�ں���Ƶ��Ŀ��ROI��OrigTraceTable����
	CvRect m_theObjRecClicked;                           ///<��¼����굥����Ŀ��ROI��
	int m_clickedObjRecPosInVec;                        ///<��¼���������Ŀ��ROI����m_objectRectVector�е��±��
	int m_distanceToRecCenter;                          ///<�����λ����ROI���ĵ�ľ���
	int  nHitItem;                                      ///<��ǰѡ�е��е�����
	int preHitItem;                                     ///<��һ��ѡ�е��е�����
	int m_pageSum;							///<��¼һҳ���ٸ�����ͼ
	int m_pageNum;							///<��¼��ǰ����ͼ����ʾ��Ϊ�ڼ�ҳ
	int OriFrame;                           ///allͼƬ�������ԭ��Ƶ
	bool UserClick1;///<�����ж��û����ް�����꣬�޲���ʱΪFALSE���в���ʱΪTRUE
	bool Generated1;///<�û��Ƿ����ˡ����ɡ���ť
	afx_msg void OnBnClickedButtonObject();//��һ��ʾǰ������ť
	afx_msg void OnAbout();
	afx_msg void OnClickObjectViewDlg();
	afx_msg void OnMenuClickedOpen();

	//afx_msg void OnBnClickedBtnGotoFrame();
	//afx_msg void OnBnClickedBtnGotoPara();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnView();
	afx_msg void OnBnClickedButtonSettings();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnexit();
	afx_msg void OnTimer(UINT nIDEvent);           ///<��ʱ�����ڲ������������Լ�ʱ����ʾˢ��
	CTabCtrl m_tab;
    CRect m_rect;
	CRect rcTabRect;                               ///<�Ӵ�������
	POINT old;
	UIbeautify UIBeautifier;                      ///<������������Ķ���
	CButtonBeautify Btn_BTN1_OPEN;
	CButtonBeautify Btn_BTN1_VIEW;
	CButtonBeautify Btn_BTN1_ABOUT;
	CButtonBeautify Btn_BTN1_EXIT;
	CButtonBeautify Btn_BTN1_SAVE;
	CButtonBeautify Btn_BTN1_TITLE;
	CBitmap *BitmapBackGroundStrech;              ///<�����ͼƬ
	CSliderCtrl m_CSliderPlayer1Ctrl;   ///<����һ�������ؼ�����
	CSliderCtrl m_CSliderPlayer2Ctrl;   ///<���ڶ��������ؼ�����
	ObjectViewSUBDlg ObjectDlg;//��һ��ʾǰ������Ĵ���
	WelcomeDlg WelDlg;
	void DetectResultnew();
	void DisplayPageSumImgnew();
	void ShowImage1(IplImage* pSrc, UINT ID);
	void OnAppExit();
	void ShowTime(int m_currentFrameNO,            ///<������ʾ����ʱ��ĺ���
		int totalFrameCount,
		int videoTimeInSecond,
		CWnd *m_pShowTimeWnd, int flag);
	void ShowCurrentFrameNO(int m_currentFrameNO, CEdit* m_wndEditFrameNo1);

};

void cvMouseHandlerInPic1(int eventType, int x, int y, int flags, void *param);
void cvMouseHandlerInPic2(int eventType, int x, int y, int flags, void *param);
