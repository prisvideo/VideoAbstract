#pragma once
#include "afxwin.h"
#include "vidPlayer.h"
#include "LibMySql.h"
#include "ButtonBeautify.h"
#include "UIbeautify.h"


// ObjectViewSUBDlg �Ի���


class ObjectViewSUBDlg : public CDialog
{
	DECLARE_DYNAMIC(ObjectViewSUBDlg)

public:
	ObjectViewSUBDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ObjectViewSUBDlg();
	void ShowImage( IplImage* img, UINT ID,CString WName);    // ID ��Picture Control�ؼ���ID��

// �Ի�������
	enum { IDD = IDD_OBJECT };

	afx_msg void OnBnClickedButtonObject();
	afx_msg void OnBnClickedObjectLeft();
	afx_msg void OnBnClickedObjectRight();
	afx_msg void OnStnClickedStaticObject1();
	afx_msg void OnStnClickedStaticObject2();
	afx_msg void OnStnClickedStaticObject3();
	afx_msg void OnStnClickedStaticObject4();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnClose();

	bool UserClick;///<�����ж��û����ް�����꣬�޲���ʱΪFALSE���в���ʱΪTRUE
	bool Generated;///<�û��Ƿ����ˡ����ɡ���ť
	bool user_click_scrollbar;
	BOOL  If_playpiece;//ԭʼ��Ƶ��ʼ����Ƭ���ñ�־λ;
	int OriFrame;//���ڴ��������Ի����ò�����������Ӧ��֡
	int m_pageSum;							///<��¼һҳ���ٸ�����ͼ
	int m_pageNum;							///<��¼��ǰ����ͼ����ʾ��Ϊ�ڼ�ҳ
	CStatic ObjectPicture_1;
	CDataMySql* m_MysqlVideoHandle;
	CVideo *videoPro;
	vidPlayer oriPlayer;
	vidPlayer ObjectPlayer;
	vector<objectInfo> objDetectedInfos;	///<�洢���ݿ��������Ϣ��������ʾ����ͼ
	CScrollBar* pScrollBar;
	CSliderCtrl m_CSliderPlayerCtrl;
	HICON m_hIcon;
	POINT old;
	CRect m_rect;
	CRect rcTabRect;                               ///<�Ӵ�������
	CBitmap *BitmapBackGroundStrech;              ///<�����ͼƬ
	UIbeautify UIBeautifier;                      ///<������������Ķ���
	CButtonBeautify  BTN_OBJECT_ORI_PLAY;
	CButtonBeautify  BTN_OBJECT_ORI_PAUSE;
	CButtonBeautify  BTN_OBJECT_ORI_STOP;
	
	void DetectResult();
	void DisplayPageSumImg();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
