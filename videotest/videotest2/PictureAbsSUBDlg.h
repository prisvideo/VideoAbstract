#pragma once
#include "afxwin.h"
#include "vidPlayer.h"
#include "LibMySql.h"
#include "ButtonBeautify.h"
#include "UIbeautify.h"


// PictureAbsSUBDlg 对话框

class PictureAbsSUBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PictureAbsSUBDlg)

public:
	PictureAbsSUBDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PictureAbsSUBDlg();

// 对话框数据
	enum { IDD = IDD_picsum };
	
	
	int m_pagenum;
	int m_pageSum;
	int OriFrame;
	int m_clickedObjRecPosInVec;                        ///<记录被鼠标点击的目标ROI框在m_objectRectVector中的下标号
	int m_distanceToRecCenter;                          ///<鼠标点击位置与ROI中心点的距离
	BOOL Generated;
	BOOL UserClick;
	BOOL  If_playpiece;//原始视频开始播放片段置标志位;
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
	
	vector <OrigTraceTable> m_objectOrigTraceTableVector;        ///<用于存储融合视频中目标ROI的OrigTraceTable向量
	CDataMySql* Tab2_MysqlVideoParaSearchHandle;
	CVideo* m_videoPro;
	CvRect m_theObjRecClicked;                           ///<记录被鼠标单击的目标ROI框
	CRect m_rect;
	CRect rcTabRect;                                    ///<子窗口坐标
	CBitmap *BitmapBackGroundStrech;              ///<拉伸后图片
	POINT old;

	UIbeautify UIBeautifier;                      ///<用于美化界面的对象
	CButtonBeautify  Btn_TAB2_PLAY;
	CButtonBeautify  Btn_TAB2_PAUSE;
	CButtonBeautify  Btn_TAB2_STOP;
	CButtonBeautify  Btn_TAB2_UP;
	CButtonBeautify  Btn_TAB2_DOWN;

	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	void DisplaySumImg();
	//void ShowTime(int m_currentFrameNO, int totalFrameCount, int videoTimeInSecond, CWnd *m_pShowTimeWnd, int flag);  ///<用于显示播放时间的函数


protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
