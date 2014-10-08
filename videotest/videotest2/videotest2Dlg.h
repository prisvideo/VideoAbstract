
// videotest2Dlg.h : ͷ�ļ�
/* ȥ��CWMPControls�ؼ��й�ͷ�ļ�
@version �汾��(0.0)
*@data 2014-6-4
*/

#pragma once
#include "publicheader.h"
#include "CvvImage.h"
#include "afxwin.h"  
#include "afxcmn.h"
#include "VideoSeg.h"
#include "Resource.h"
#include "vidPlayer.h"
#include "ObjectViewDlg.h"
#include "LibMySql.h"
#include "Dialog1.h"
#include "picsum.h"
#include "ButtonBeautify.h"
#include "UIbeautify.h"
#include "WelcomeDlg.h"
#include "drawDetection.h"


// Cvideotest2Dlg �Ի���
class Cvideotest2Dlg : public CDialogEx
{
// ����
public:
	Cvideotest2Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~Cvideotest2Dlg();
	CDataMySql* m_MysqlVideoParaSearchHandle;
	int m_CurSelTab; 
    Dialog1 m_page1;
	//vidPlayer playVideo;
	picsum m_page2;
    CObjectViewDlg m_page3;
	drawDetection m_page4;
    CDialog* pDialog[4];

// �Ի�������
	enum { IDD = IDD_VIDEOTEST2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool m_ifStartPro;          ///<�Ƿ���������ժҪ
	bool Generated;///<�û��Ƿ����ˡ����ɡ���ť
	void DisplayPageSumImgnew();
	TableParams m_tableParams;
	vector<objectInfo> objDetectedInfos;	///<�洢���ݿ��������Ϣ��������ʾ����ͼ
	void DetectResultnew();
	BOOL  If_playpiece;//ԭʼ��Ƶ��ʼ����Ƭ���ñ�־λ;
	CString PathName;	
	CVideo* m_videoPro;
	CProgressCtrl* myPro;
	vidPlayer player1;
	vidPlayer player2;
	
	void ShowImage1(IplImage* pSrc, UINT ID);
	void OnAppExit();
	
public:
	afx_msg void OnTimer(UINT nIDEvent);           ///<��ʱ�����ڲ������������Լ�ʱ����ʾˢ��
	void ShowTime(int m_currentFrameNO,            ///<������ʾ����ʱ��ĺ���
				  int totalFrameCount,
				  int videoTimeInSecond, 
				  CWnd *m_pShowTimeWnd, int flag);
	void ShowCurrentFrameNO(int m_currentFrameNO, CEdit* m_wndEditFrameNo1);

public:
	///2�����Ŵ��ڵĻ��������Ʊ�������
	CSliderCtrl m_CSliderPlayer1Ctrl;   ///<����һ�������ؼ�����
	CSliderCtrl m_CSliderPlayer2Ctrl;   ///<���ڶ��������ؼ�����

	
protected:
	CEdit		m_wndEditFrameNo1;
	CEdit		m_wndEditInputFrameNo1;
	CEdit		m_wndEditInput_nPara;
	int			m_nInputFrameNo1;
	int         SubMenuCheckedNO;
public:
	afx_msg void OnBnClickedBtnGotoFrame();
	afx_msg void OnBnClickedBtnGotoPara();
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


	//afx_msg void OnBnClickedCheck1();

	CObjectViewDlg ObjectDlg;//��һ��ʾǰ������Ĵ���
	//Dialog1 m_dlg1;//test0916
	WelcomeDlg WelDlg;
	afx_msg void OnBnClickedButtonObject();//��һ��ʾǰ������ť
	afx_msg void OnAbout();
	afx_msg void OnClickObjectViewDlg();
	afx_msg void OnMenuClickedOpen();
	afx_msg void OnMenuitemUltrablue();
	afx_msg void OnMenuitemvladstudio();
	afx_msg void OnMenuitemPhenom();
	afx_msg void OnMenuitemAquaos();
	
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnView();

	CRect m_rect;
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	POINT old;  
	UIbeautify UIBeautifier;                      ///<������������Ķ���
	CButtonBeautify Btn_BTN1_OPEN;
	CButtonBeautify Btn_BTN1_VIEW;
	CButtonBeautify Btn_BTN1_ABOUT;
	CButtonBeautify Btn_BTN1_EXIT;
	CButtonBeautify Btn_BTN1_SAVE;
	CButtonBeautify Btn_BTN1_TITLE;
	CBitmap *BitmapBackGroundStrech;              ///<�����ͼƬ
	CRect rcTabRect;                                    ///<�Ӵ�������
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonSettings();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnexit();
};

void cvMouseHandlerInPic1(int eventType, int x, int y, int flags, void *param);
void cvMouseHandlerInPic2(int eventType, int x, int y, int flags, void *param);
