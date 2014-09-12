
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
	bool Generated;///<�û��Ƿ����ˡ����ɡ���ť
	vidPlayer player1;
	vidPlayer player2;
	void DisplayPageSumImgnew();
	TableParams m_tableParams;
	vector<objectInfo> objDetectedInfos;	///<�洢���ݿ��������Ϣ��������ʾ����ͼ
	void DetectResultnew();
	BOOL  If_playpiece;//ԭʼ��Ƶ��ʼ����Ƭ���ñ�־λ;
	
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedBtnGenerateAbs();

	
	//void DrawPicToHDC(IplImage *img, UINT ID);
	void ShowImage1(IplImage* pSrc, UINT ID);
	afx_msg void OnEnChangeEdit3();
	void OnAppExit();
	//void ShowImage( IplImage* img, UINT ID );    // ID ��Picture Control�ؼ���ID��
	//afx_msg void OnBnClickedBtnexit();
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


	afx_msg void OnBnClickedCheck1();

	CObjectViewDlg ObjectDlg;//��һ��ʾǰ������Ĵ���
	afx_msg void OnBnClickedButtonObject();//��һ��ʾǰ������ť
	afx_msg void OnAbout();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedStaticAbspic1();
	afx_msg void OnStnClickedStaticAbspic2();
	afx_msg void OnClickObjectViewDlg();
	afx_msg void OnMenuClickedOpen();
	afx_msg void OnMenuitemUltrablue();
	afx_msg void OnMenuitemvladstudio();
	afx_msg void OnMenuitemPhenom();
	afx_msg void OnMenuitemAquaos();
};

void cvMouseHandlerInPic1(int eventType, int x, int y, int flags, void *param);
void cvMouseHandlerInPic2(int eventType, int x, int y, int flags, void *param);
