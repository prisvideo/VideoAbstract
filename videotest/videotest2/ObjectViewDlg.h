#pragma once
#include "afxwin.h"
#include "vidPlayer.h"
#include "LibMySql.h"
#include "ButtonBeautify.h"
#include "UIbeautify.h"


// CObjectViewDlg �Ի���





class CObjectViewDlg : public CDialog
{
	DECLARE_DYNAMIC(CObjectViewDlg)

public:
	CObjectViewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CObjectViewDlg();
	void ShowImage( IplImage* img, UINT ID,CString WName);    // ID ��Picture Control�ؼ���ID��

// �Ի�������
	enum { IDD = IDD_OBJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedButtonObject();
	afx_msg void OnBnClickedObjectLeft();
	afx_msg void OnBnClickedObjectRight();
	afx_msg void OnStnClickedStaticObject1();
	afx_msg void OnStnClickedStaticObject2();
	afx_msg void OnStnClickedStaticObject3();
	afx_msg void OnStnClickedStaticObject4();
	
	CStatic ObjectPicture_1;
	int m_pageSum;							///<��¼һҳ���ٸ�����ͼ
	int m_pageNum;							///<��¼��ǰ����ͼ����ʾ��Ϊ�ڼ�ҳ
	CDataMySql* m_MysqlVideoHandle;
	CVideo *videoPro;
	vidPlayer oriPlayer;
	void DisplayPageSumImg();
	vector<objectInfo> objDetectedInfos;	///<�洢���ݿ��������Ϣ��������ʾ����ͼ
	void DetectResult();
	bool UserClick;///<�����ж��û����ް�����꣬�޲���ʱΪFALSE���в���ʱΪTRUE
	bool Generated;///<�û��Ƿ����ˡ����ɡ���ť
	int OriFrame;//���ڴ��������Ի����ò�����������Ӧ��֡
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnInitMenu(CMenu* pMenu);
//	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
//	afx_msg void OnUniChar(UINT Char, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnInitDialog();

	CScrollBar* pScrollBar;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	vidPlayer ObjectPlayer;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CSliderCtrl m_CSliderPlayerCtrl; 
	bool user_click_scrollbar;
	BOOL  If_playpiece;//ԭʼ��Ƶ��ʼ����Ƭ���ñ�־λ;
	void ShowTime(int m_currentFrameNO,            ///<������ʾ����ʱ��ĺ���
		int totalFrameCount,
		int videoTimeInSecond, 
		CWnd *m_pShowTimeWnd, int flag);
//	afx_msg void OnClose();
	afx_msg void OnClose();
//	afx_msg void OnCancelMode();
	virtual void OnCancel();
//	afx_msg void OnPaint();
	HICON m_hIcon;

	CRect m_rect;
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	POINT old;  

	UIbeautify UIBeautifier;                      ///<������������Ķ���
	CButtonBeautify  BTN_OBJECT_ORI_PLAY;
	CButtonBeautify  BTN_OBJECT_ORI_PAUSE;
	CButtonBeautify  BTN_OBJECT_ORI_STOP;

	CBitmap *BitmapBackGroundStrech;              ///<�����ͼƬ
	CRect rcTabRect;                                    ///<�Ӵ�������
};
