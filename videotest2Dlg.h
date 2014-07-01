
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


// Cvideotest2Dlg �Ի���
class Cvideotest2Dlg : public CDialogEx
{
// ����
public:
	Cvideotest2Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~Cvideotest2Dlg();
	CDataMySql* m_MysqlVideoParaSearchHandle;

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
private:
	CString PathName;
	CVideo* m_videoPro;
	CProgressCtrl* myPro;
public:
	bool m_ifStartPro;          ///<�Ƿ���������ժҪ
	vidPlayer player1;
	vidPlayer player2;
	BOOL  If_playpiece;//ԭʼ��Ƶ��ʼ����Ƭ���ñ�־λ;
	
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedBtnGenerateAbs();

	
	//void DrawPicToHDC(IplImage *img, UINT ID);
	//void ShowImage(IplImage* pSrc, UINT ID);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit3();
	void OnAppExit();

	afx_msg void OnBnClickedBtnexit();
	afx_msg void OnBnClickedBtnViewAbs();
	afx_msg void OnBnClickedBtn1play();
	afx_msg void OnBnClickedBtn1pause();
	afx_msg void OnBnClickedBtn1stop();
	afx_msg void OnBnClickedBtn2play();
	afx_msg void OnBnClickedBtn2pause();
	afx_msg void OnBnClickedBtn2stop();
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);

//ʱ����ʾ
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
public:
	afx_msg void OnBnClickedBtnGotoFrame();
	afx_msg void OnBnClickedBtnGotoPara();
	vector <CvRect> m_objectRectVector;                  ///<���ڴ洢�ں���Ƶ��Ŀ��ROI��rect����
	CvRect m_theObjRecClicked;                           ///<��¼����굥����Ŀ��ROI��
	int m_clickedObjRecPosInVec;                        ///<��¼���������Ŀ��ROI����m_objectRectVector�е��±��
	int m_distanceToRecCenter;                          ///<�����λ����ROI���ĵ�ľ���
	int  nHitItem;                                      ///<��ǰѡ�е��е�����
	int preHitItem;                                     ///<��һ��ѡ�е��е�����
	afx_msg void OnBnClickedCheck1();
};
