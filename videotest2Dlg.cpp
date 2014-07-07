
// videotest2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "videotest2.h"
#include "videotest2Dlg.h"
#include "afxdialogex.h"
#include "afxdlgs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)


CDataMySql *m_MysqlHandle;         ///<���ݿ��ⲿָ�����
pointForCvMouse mousePosInPic;
//bool m_gotCVlclick = FALSE;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��

};
/////////////////////////////////////////////////////////2014.6.16
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}




// Cvideotest2Dlg �Ի���


Cvideotest2Dlg::Cvideotest2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cvideotest2Dlg::IDD, pParent)
{
	m_ifStartPro = false;
	m_videoPro = new CVideo;
	m_MysqlVideoParaSearchHandle = new CDataMySql;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

Cvideotest2Dlg::~Cvideotest2Dlg()
	
{
	  delete m_MysqlVideoParaSearchHandle;			   ///<ɾ�����ݿ����ָ��
	  delete m_videoPro;
}

void Cvideotest2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_PLAYER1,m_CSliderPlayer1Ctrl);
	DDX_Control(pDX, IDC_SLIDER_PLAYER2,m_CSliderPlayer2Ctrl);
	DDX_Control(pDX, IDC_EDIT_FRAME_NO, m_wndEditFrameNo1);	
	DDX_Control(pDX, IDC_EDIT_INPUT_FRAME_NO, m_wndEditInputFrameNo1);
	//DDX_Control(pDX, IDC_EDIT_INPUT_nPara_NO, m_wndEditInput_nPara);
	
}

BEGIN_MESSAGE_MAP(Cvideotest2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_OPEN, &Cvideotest2Dlg::OnBnClickedOpen)

	ON_BN_CLICKED(IDC_BTN_GENERATE_ABS, &Cvideotest2Dlg::OnBnClickedBtnGenerateAbs)

	
	ON_BN_CLICKED(IDC_BTN_exit, &Cvideotest2Dlg::OnBnClickedBtnexit)
	ON_BN_CLICKED(IDC_BTN_VIEW_ABS, &Cvideotest2Dlg::OnBnClickedBtnViewAbs)
	ON_BN_CLICKED(IDC_BTN1_play, &Cvideotest2Dlg::OnBnClickedBtn1play)
	ON_BN_CLICKED(IDC_BTN1_pause, &Cvideotest2Dlg::OnBnClickedBtn1pause)
	ON_BN_CLICKED(IDC_BTN1_stop, &Cvideotest2Dlg::OnBnClickedBtn1stop)
	ON_BN_CLICKED(IDC_BTN2_play, &Cvideotest2Dlg::OnBnClickedBtn2play)
	ON_BN_CLICKED(IDC_BTN2_pause, &Cvideotest2Dlg::OnBnClickedBtn2pause)
	ON_BN_CLICKED(IDC_BTN2_stop, &Cvideotest2Dlg::OnBnClickedBtn2stop)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &Cvideotest2Dlg::OnNMCustomdrawProgress1)
	ON_BN_CLICKED(IDC_BTN_GOTO_FRAME, &Cvideotest2Dlg::OnBnClickedBtnGotoFrame)
	//ON_BN_CLICKED(IDC_BTN_GOTO_PARA, &Cvideotest2Dlg::OnBnClickedBtnGotoPara)
	ON_BN_CLICKED(IDC_CHECK1, &Cvideotest2Dlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// Cvideotest2Dlg ��Ϣ�������

BOOL Cvideotest2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	
	m_nInputFrameNo1 = 0;
	player1.m_filePath = "";
	player2.m_filePath = "";
	player1.playInitial(GetDlgItem(IDC_STATIC_ABS), "displayWindow1");//�ó�ʼ����Ҫ���ļ�·��ȷ�Ϻ����
	player1.m_currentFrameNO = player1.m_startFrameNO = 0;
	player1.m_endFrameNO=3000;

	m_CSliderPlayer1Ctrl.SetRange(0, player1.m_endFrameNO);
	m_CSliderPlayer1Ctrl.SetPos(0);

	player2.playInitial(GetDlgItem(IDC_STATIC_ABS), "displayWindow2");//�ó�ʼ����Ҫ���ļ�·��ȷ�Ϻ����
	player2.m_currentFrameNO = player2.m_startFrameNO = 0;		
	player2.m_endFrameNO=3000;

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	///��������ʼ��
	myPro = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	myPro->SetRange(0,500);
	myPro->SetPos(0);

	m_CSliderPlayer1Ctrl.SetRange(0, player1.m_endFrameNO);   ///<��ʼ������һ�Ļ�����
	m_CSliderPlayer1Ctrl.SetPos(0);

	m_CSliderPlayer2Ctrl.SetRange(0, player2.m_endFrameNO);   ///<��ʼ�����ڶ��Ļ�����
	m_CSliderPlayer2Ctrl.SetPos(0);

	SetTimer(1, 100, NULL);///<��������ʼ��
	SetTimer(2, 200, NULL);
	SetTimer(3, 500, NULL);
	SetTimer(4, 100, NULL);

	If_playpiece=FALSE;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
//void Cvideotest2Dlg::InitialPictureControl()
//{
//
//}

void Cvideotest2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cvideotest2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cvideotest2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cvideotest2Dlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//�ļ����͹���*/
	CFileDialog dlg(TRUE, NULL, NULL,OFN_HIDEREADONLY,_T("Files (*.mp3 *.wma *.dat *.wmv *.avi *.mov *.mmm *.mid *.mpeg)|*.mp3;*.wma;*.dat;*.wmv;*.avi;*.mov;*.mmm;*.mid;*.mpeg|All Files (*.*)|*.*||"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		if (player1.m_currentFrameNO!=0)
		{
			player1.stopPlay();
		}
		PathName=dlg.GetPathName();
		SetDlgItemText(IDC_EDIT3, PathName);
		PathName.MakeUpper();

		player1.m_filePath = PathName;
	    player1.playInitial(GetDlgItem(IDC_STATIC2), "displayWindow1");//�ó�ʼ����Ҫ���ļ�·��ȷ�Ϻ����
	
		m_CSliderPlayer1Ctrl.SetRange(0, player1.m_endFrameNO);
		m_CSliderPlayer1Ctrl.SetPos(0);
		
		player1.play();

		CString m_pFilePath=PathName;
		CString m_tmpFileName1, m_tmpFileName2;
		GetVideoNameFromAbsolutePath1(&m_pFilePath,&m_tmpFileName1);///<��ȡ�ļ���(������׺)
		GetFileNameBeforeDot(&m_tmpFileName1,&m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
		m_videoPro->m_tableParams.VideoFGTableName.Format("%s_VideoFGTable",m_tmpFileName2);
		m_videoPro->m_tableParams.FGTraceTableName.Format("%s_FGTraceTable",m_tmpFileName2);
		m_videoPro->m_tableParams.NewToOldFrameTableName.Format("%s_New2OldFrameTable",m_tmpFileName2);
		m_videoPro->m_tableParams.NewTraceTable.Format("%s_NewTraceTable",m_tmpFileName2);
		m_videoPro->m_tableParams.CombineSegsTableName.Format("%s_CombineSegsTable", m_tmpFileName2);

	}
	
}




void Cvideotest2Dlg::OnBnClickedBtnGenerateAbs()
{
	CString a = "\\";
	LPCTSTR m = a;
	CString b = "/";
	LPCTSTR n = b;
	if (m_ifStartPro)
	{
		MessageBox("��������ժҪ����ȴ�");
		return;
	}
	if (PathName != "")
	{
		m_videoPro->m_IfContinue = true;
		m_ifStartPro = true;
	
		PathName.Replace(*m, *n);
		m_videoPro->DoProcessing((LPSTR)(LPCTSTR)PathName);
	}
}



///@brief ��ʱ������������ˢ�½�������ʱ����ʾ
/// 
///@param[in] UINT nIDEvent ��ʱ�����
///@pre  NULL
///@return NULL
///@retval BOOL
///@post NULL

void Cvideotest2Dlg::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
		case 1:///<���Ŵ���1�Ľ�������ʱ����ʾˢ��
	    {
			if (If_playpiece)
			{
				CSliderCtrl * SliderCtrl=((CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAYER1));
				SliderCtrl->SetPos(player1.m_currentFrameNO);
			}
			else
			{
				CSliderCtrl * SliderCtrl=((CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAYER1));
				int CurrentPos=SliderCtrl->GetPos();                            ///<��ȡ��ǰ������λ��
				int NewCurrentFrameNO = (double)CurrentPos*double(player1.m_endFrameNO-player1.m_startFrameNO)
										/(double)SliderCtrl->GetRangeMax();     ///<���ݵ�ǰ������λ�ã����¼���֡��

				if (player1.m_playState!=PLAY_STATE_STOP && player1.m_playState!=PLAY_STATE_FAST_FORWORD &&player1.m_playState!=PLAY_STATE_PLAY_PIECE)///<�������������������Ż���ͣ״̬
				{
					if (abs(NewCurrentFrameNO-player1.m_currentFrameNO)>5)
					{
						player1.m_currentFrameNO=NewCurrentFrameNO;             ///<�����¼����֡�ţ����ò�����
					}
				}
				SliderCtrl->SetPos(player1.m_currentFrameNO);                   ///<�����¼����֡�ţ����û�����
				CWnd *pWndTimeDis = GetDlgItem(IDC_STATIC_TIME_VID1);
				if (player1.m_playState != PLAY_STATE_STOP)                     ///<��ֹͣ״̬�£��÷�ʽһ��ʾʱ��
				{
					ShowTime(player1.m_currentFrameNO, player1.m_endFrameNO - player1.m_startFrameNO,
						     player1.m_videoTimeInSecond, pWndTimeDis, 1);
					ShowCurrentFrameNO(player1.m_currentFrameNO, &m_wndEditFrameNo1);
				}
				else                                                            ///<ֹͣ״̬�£��÷�ʽ����ʾʱ��
				{
					SliderCtrl->SetPos(0);
					ShowTime(player1.m_currentFrameNO, player1.m_endFrameNO - player1.m_startFrameNO,
					         player1.m_videoTimeInSecond, pWndTimeDis, 0);
					ShowCurrentFrameNO(player1.m_currentFrameNO, &m_wndEditFrameNo1);
				}
			}
		}
		case 2:///<ˢ������
		{
			if (!m_ifStartPro)
			{
				myPro->SetPos(0);
				SetDlgItemText(IDC_STATIC, "");//helloworld
			}
			else if (m_videoPro->m_IfDoneFus)///<����Ѿ�����ժҪ��ClistCtrl����Ӧ������ʾΪ��������ժҪ��
			{
				m_ifStartPro = false;
				MessageBox("������ժҪ");
			}
			///����������ɻ�δ�������,ˢ�½������Ϸ�����ʾ����׶�
			else if (m_videoPro->m_IfContinue)
			{
				int VideoPos = (int)m_videoPro->ProcessingSpeed();
				if (VideoPos == 0)
				{
					SetDlgItemText(IDC_STATIC,  "��ƵԤ������");
				}
				if (VideoPos == 1)
				{
					SetDlgItemText(IDC_STATIC,  "�����з���Ƶ����");
				}
				if (VideoPos == 2)
				{
					SetDlgItemText(IDC_STATIC, "��Ƶ����������");
				}
				if (VideoPos == 3)
				{
					SetDlgItemText(IDC_STATIC, "��Ƶǰ��������");
				}
				if (VideoPos == 4)
				{
					SetDlgItemText(IDC_STATIC, "��Ƶ�ںϡ���");
				}
				myPro->SetPos((int)(m_videoPro->ProcessingSpeed()*100.0));
			}
			else
			{
				if ((int)m_videoPro->ProcessingSpeed() == -1)
				{
					m_ifStartPro = false;
					MessageBox( "��Ƶʱ�����̣������ںϴ���");
				
				}
			}
		}
		case 3:
		{
				CSliderCtrl * SliderCtrl=((CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAYER2));
				int CurrentPos=SliderCtrl->GetPos();                            ///<��ȡ��ǰ������λ��
				int NewCurrentFrameNO = (double)CurrentPos*double(player2.m_endFrameNO-player2.m_startFrameNO)
					/(double)SliderCtrl->GetRangeMax();     ///<���ݵ�ǰ������λ�ã����¼���֡��
				if (player2.m_playState!=PLAY_STATE_STOP && player2.m_playState!=PLAY_STATE_FAST_FORWORD)///<�������������������Ż���ͣ״̬
				{
					if (abs(NewCurrentFrameNO-player2.m_currentFrameNO)>5)
					{
						player2.m_currentFrameNO=NewCurrentFrameNO;             ///<�����¼����֡�ţ����ò�����
					}
				}
				SliderCtrl->SetPos(player2.m_currentFrameNO);                   ///<�����¼����֡�ţ����û�����
				CWnd *pWndTimeDis = GetDlgItem(IDC_STATIC_TIME_VID2);
				if (player2.m_playState != PLAY_STATE_STOP)                     ///<��ֹͣ״̬�£��÷�ʽһ��ʾʱ��
				{
					ShowTime(player2.m_currentFrameNO, player2.m_endFrameNO -player2.m_startFrameNO,
						player2.m_videoTimeInSecond, pWndTimeDis, 1);
				}
				else                                                            ///<ֹͣ״̬�£��÷�ʽ����ʾʱ��
				{
					SliderCtrl->SetPos(0);
					ShowTime(player2.m_currentFrameNO,player2.m_endFrameNO - player2.m_startFrameNO,
						player2.m_videoTimeInSecond, pWndTimeDis, 0);

				}
		}
		case 4://ժҪ���ڵ��������
		{
			if (player2.m_gotCVlclick == TRUE)  //&& Abstractplayer.m_playState == PLAY_STATE_PAUSE
			{
				m_clickedObjRecPosInVec = -1;
				CPoint posInWnd = player2.m_lBtnUpPosInCVWnd;///<���������󴫳��ĵ�����꣬��ʱ�ĵ��λ���Ѿ���ԭʼ֡�ߴ������
				double clickPosXInImg = double(posInWnd.x);
				double clickPosYInImg = double(posInWnd.y);///<ע���ʱ�ĵ��λ���Ѿ���ԭʼ֡�ߴ������
				m_distanceToRecCenter = 1000000;

				m_objectRectVector.clear();
				///<�����ݿ��ж�ȡROI��Ϣ
				if(!m_MysqlVideoParaSearchHandle->FindROIFromNewTraceTable(player2.m_currentFrameNO,&m_objectRectVector,m_videoPro->m_tableParams.NewTraceTable))//////"00015_h_NewTraceTable"
				{
					AfxMessageBox("���ݿ����");
					return;
				}

				for (int i=0; i<m_objectRectVector.size(); i++)///<��������ROIĿ���
				{
					if (clickPosXInImg < m_objectRectVector[i].x+m_objectRectVector[i].width && clickPosXInImg > m_objectRectVector[i].x///<�жϵ���Ƿ��ڵ�ǰ����
						&& clickPosYInImg < m_objectRectVector[i].y+m_objectRectVector[i].height && clickPosYInImg > m_objectRectVector[i].y)
					{
						int tempDistance = (clickPosXInImg - (m_objectRectVector[i].x+m_objectRectVector[i].width/2))*
							(clickPosXInImg - (m_objectRectVector[i].x+m_objectRectVector[i].width/2))+
							(clickPosYInImg - (m_objectRectVector[i].y+m_objectRectVector[i].height/2))*
							(clickPosYInImg - (m_objectRectVector[i].y+m_objectRectVector[i].height/2));///<������λ���뵱ǰROI���ĵľ���

						if (tempDistance < m_distanceToRecCenter)
						{
							m_distanceToRecCenter = tempDistance;///<��ǰ����С�ڼ�¼����С���룬����������С����
							m_clickedObjRecPosInVec = i;         ///<����¼��ǰROI�������е��±�ֵ
						}
					}
				}
				if(m_clickedObjRecPosInVec==-1)
				{
					return;
				}
				/*if (m_theObjRecClicked != m_objectRectVector[m_clickedObjRecPosInVec])
				{*/
					m_theObjRecClicked = m_objectRectVector[m_clickedObjRecPosInVec];
					int m_theorigFrame=0;
					if (m_videoPro!=NULL)
					{
						int m_origPara = m_MysqlVideoParaSearchHandle->FindOrigParaFromFGTraceTable(m_videoPro->m_tableParams.FGTraceTableName,m_theObjRecClicked);
						m_theorigFrame = m_MysqlVideoParaSearchHandle->FindOrigFrameFromVideoFGTable(m_videoPro->m_tableParams.VideoFGTableName,m_origPara);//m_videoPro->m_tableParams.NewTraceTable
					
						//m_theorigFrame = m_MysqlVideoParaSearchHandle->FindOrigFrameFromNewTraceTable(m_videoPro->m_tableParams.NewTraceTable,m_theObjRecClicked);//m_videoPro->m_tableParams.NewTraceTable
					}
					
					if (m_theorigFrame == -1)  
					{
						MessageBox("���ݿ�����");
						player2.m_gotCVlclick = FALSE;     
						return;
					};
					//else
					//{
					//	Originalplayer.m_startFrameNO = MAX(0,m_theorigFrame-500);///<δ�ܵõ�֡�ţ���Ĭ�ϲ���ǰ500֡�ͺ�1000֡
					//	Originalplayer.m_endFrameNO   = Originalplayer.m_startFrameNO + 1000;
					//}
		
					//player1.m_filePath = absOriNameTansf(Abstractplayer.m_filePath);				
					player1.m_currentFrameNO=m_theorigFrame;                                 ///<��ʼ��ԭʼ��Ƶ������
				//}
				If_playpiece=TRUE;
				player2.m_gotCVlclick = FALSE;                                       ///<����ȶ���ϣ����õ������־λ�÷�
			}
		}
		case 5://ժҪͼƬ���������
		{
				CString m_windowName = "displayWindow3"; //��ǰ���̿��Ƶ�CV������
					
				CPoint m_clickPosInCVWnd;///<��¼��������ĵ�
				CPoint m_lBtnUpPosInCVWnd;///<��¼�������ĵ�
				int para = 5;
				cvSetMouseCallback(m_windowName, cvMouseHandlerInPic, &para);

				m_clickPosInCVWnd.x = mousePosInPic.x;
				m_clickPosInCVWnd.y = mousePosInPic.y;
				m_lBtnUpPosInCVWnd.x = mousePosInPic.x1;
				m_lBtnUpPosInCVWnd.y = mousePosInPic.y1;
				//m_gotCVlclick = mousePosInPic.clickInCVwnd;//cv���ڵõ���������㴫��

				if (mousePosInPic.clickInCVwnd )
				{
				
					m_clickedObjRecPosInVec = -1;
					double clickPosXInImg = double(m_lBtnUpPosInCVWnd.x);
					double clickPosYInImg = double(m_lBtnUpPosInCVWnd.y);///<ע���ʱ�ĵ��λ���Ѿ���ԭʼ֡�ߴ������
					m_distanceToRecCenter = 1000000;

					m_objectRectVector.clear();
					///<�����ݿ��ж�ȡROI��Ϣ
					if (!m_MysqlVideoParaSearchHandle->FindROIFromCombineSegsTable(&m_objectRectVector, m_videoPro->m_tableParams.CombineSegsTableName))//////"00015_h_NewTraceTable"
					{
						AfxMessageBox("���ݿ����");
						return;
					}

					for (int i = 0; i < m_objectRectVector.size(); i++)///<��������ROIĿ���
					{
						if (clickPosXInImg < m_objectRectVector[i].x + m_objectRectVector[i].width && clickPosXInImg > m_objectRectVector[i].x///<�жϵ���Ƿ��ڵ�ǰ����
							&& clickPosYInImg < m_objectRectVector[i].y + m_objectRectVector[i].height && clickPosYInImg > m_objectRectVector[i].y)
						{
							int tempDistance = (clickPosXInImg - (m_objectRectVector[i].x + m_objectRectVector[i].width / 2))*
								(clickPosXInImg - (m_objectRectVector[i].x + m_objectRectVector[i].width / 2)) +
								(clickPosYInImg - (m_objectRectVector[i].y + m_objectRectVector[i].height / 2))*
								(clickPosYInImg - (m_objectRectVector[i].y + m_objectRectVector[i].height / 2));///<������λ���뵱ǰROI���ĵľ���

							if (tempDistance < m_distanceToRecCenter)
							{
								m_distanceToRecCenter = tempDistance;///<��ǰ����С�ڼ�¼����С���룬����������С����
								m_clickedObjRecPosInVec = i;         ///<����¼��ǰROI�������е��±�ֵ
							}
						}
					}
					if (m_clickedObjRecPosInVec == -1)
					{
						return;
					}
					/*if (m_theObjRecClicked != m_objectRectVector[m_clickedObjRecPosInVec])
					{*/
					m_theObjRecClicked = m_objectRectVector[m_clickedObjRecPosInVec];
					int m_theorigFrame = 0;
					if (m_videoPro != NULL)
					{
						int m_origPara = m_MysqlVideoParaSearchHandle->FindOrigParaFromFGTraceTable(m_videoPro->m_tableParams.FGTraceTableName, m_theObjRecClicked);
						m_theorigFrame = m_MysqlVideoParaSearchHandle->FindOrigFrameFromVideoFGTable(m_videoPro->m_tableParams.VideoFGTableName, m_origPara);//m_videoPro->m_tableParams.NewTraceTable

						//m_theorigFrame = m_MysqlVideoParaSearchHandle->FindOrigFrameFromNewTraceTable(m_videoPro->m_tableParams.NewTraceTable,m_theObjRecClicked);//m_videoPro->m_tableParams.NewTraceTable
					}

					if (m_theorigFrame == -1)
					{
						MessageBox("���ݿ�����");
						mousePosInPic.clickInCVwnd = FALSE;
						return;
					};

					player1.m_currentFrameNO = m_theorigFrame;                                 ///<��ʼ��ԭʼ��Ƶ������

					If_playpiece = TRUE;
					mousePosInPic.clickInCVwnd=FALSE;                                       ///<����ȶ���ϣ����õ������־λ�÷�
				}
		}

		default:
			break;
	}
}

void Cvideotest2Dlg::OnAppExit()
{
	// same as double-clicking on main window close box
	//ASSERT(m_pMainWnd != NULL);
	SendMessage(WM_CLOSE);
	//_CrtDumpMemoryLeaks();
}


void Cvideotest2Dlg::OnBnClickedBtnexit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnAppExit();
	
}


void Cvideotest2Dlg::OnBnClickedBtnViewAbs()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//if(PathName)
	if (m_ifStartPro)
	{
		::MessageBox(NULL,_T("ժҪ��δ�������"),_T("error!"),MB_OK);
		return;
	}
	
	if (player1.m_currentFrameNO!=0)
		{
			player2.stopPlay();
		}
		CString path=PathName;
		path.Replace("avi","AVI");
		path = path+"_fusion.avi";
		player2.m_filePath = path;
		if(_access(path,0)==-1)
		{
			AfxMessageBox("�Ҳ����ļ�");
			return;
		}

		 // Read the file
		IplImage* image= NULL;
		image = cvLoadImage("F://video project//videotest//015_H//All.jpg",1);
		if(image != NULL ) // Check for invalid input
		{
			ShowImage(image,IDC_STATIC_ABS2);
			cvReleaseImage(&image);
		}

		SetTimer(4, 600, NULL); //�¼��ص�Picture Control�ļ�ʱ��

		player2.playInitial(GetDlgItem(IDC_STATIC_ABS), "displayWindow2");//�ó�ʼ����Ҫ���ļ�·��ȷ�Ϻ����
		m_CSliderPlayer2Ctrl.SetRange(0, player2.m_endFrameNO);
		m_CSliderPlayer2Ctrl.SetPos(0);

		player2.play();
		player2.m_MysqlVideoParaSearchHandle=m_MysqlVideoParaSearchHandle;
		player2.m_videoPro=m_videoPro;
		player2.timeshow=FALSE;
}

void Cvideotest2Dlg::ShowImage( IplImage* img, UINT ID )    // ID ��Picture Control�ؼ���ID��
{
	CWnd *m_pWnd = GetDlgItem(ID);
    CDC* pDC = GetDlgItem( ID ) ->GetDC();        // �����ʾ�ؼ��� DC
    HDC hDC = pDC ->GetSafeHdc();                // ��ȡ HDC(�豸���) �����л�ͼ����
	DisplayFrame disPlayImage;//������Ƕ���Ŵ��ڵĶ���
	
    CRect rect;
    GetDlgItem(ID) ->GetClientRect( &rect );
    int rw = rect.right - rect.left;            // ���ͼƬ�ؼ��Ŀ�͸�
    int rh = rect.bottom - rect.top;
    int iw = img->width;                        // ��ȡͼƬ�Ŀ�͸�
    int ih = img->height;
	
	rw = (int)(iw*rh/ih);		//Ӧ��ʾ�������Ŀ��
	int tx = rect.left;
	int ty = rect.top;
    SetRect( rect, tx, ty, tx+rw, ty+rh );

    //CvvImage cimg;
    //cimg.CopyOf( img );                            // ����ͼƬ
    //cimg.DrawToHDC( hDC, &rect );                // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	disPlayImage.SetOpenCVWindow(m_pWnd, "displayWindow3",
		rect.Width(), rect.Height());
	disPlayImage.ShowPicture("displayWindow3", img);

    ReleaseDC( pDC );
}

void Cvideotest2Dlg::OnBnClickedBtn1play()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(player1.m_filePath!="")
	{
		m_CSliderPlayer1Ctrl.SetRange(0, player1.m_endFrameNO);///<��������ʼ��
		
		///<ʱ����ʾ׼��
		CString VideoTime;                                     
		int VedioHour=player1.m_videoTimeInSecond/3600;
		int VedioMinute=player1.m_videoTimeInSecond/60-VedioHour*60;
		int VedioSecond=player1.m_videoTimeInSecond-VedioHour*3600-VedioMinute*60;

		VideoTime.Format(" 0:0:0 / %d:%d:%d ",VedioHour,VedioMinute,VedioSecond);
		GetDlgItem(IDC_STATIC_TIME_VID1)->SetWindowText(VideoTime);///<��ʱ����ʾ���ؼ���

		player1.play();
		
	}
	else
	{
		AfxMessageBox("��ѡ���ļ�");
	}

}


void Cvideotest2Dlg::OnBnClickedBtn1pause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	player1.pause();
	
}


void Cvideotest2Dlg::OnBnClickedBtn1stop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	player1.stop();
	
}


void Cvideotest2Dlg::OnBnClickedBtn2play()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(player2.m_filePath!="")
	{
		m_CSliderPlayer2Ctrl.SetRange(0, player2.m_endFrameNO);///<��������ʼ��
		
		///<ʱ����ʾ׼��
		CString VideoTime;                                     
		int VedioHour=player2.m_videoTimeInSecond/3600;
		int VedioMinute=player2.m_videoTimeInSecond/60-VedioHour*60;
		int VedioSecond=player2.m_videoTimeInSecond-VedioHour*3600-VedioMinute*60;

		VideoTime.Format(" 0:0:0 / %d:%d:%d ",VedioHour,VedioMinute,VedioSecond);
		GetDlgItem(IDC_STATIC_TIME_VID2)->SetWindowText(VideoTime);///<��ʱ����ʾ���ؼ���

		player2.play();
		
	}
	else
	{
		AfxMessageBox("��ѡ���ļ�");
	}
}


void Cvideotest2Dlg::OnBnClickedBtn2pause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	player2.pause();
	/*GetDlgItem(IDC_BUTTON2_pause)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2_play)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2_play)->ShowWindow(TRUE);*/
}


void Cvideotest2Dlg::OnBnClickedBtn2stop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	player2.stop();
}


void Cvideotest2Dlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

///@brief ������ʱ����ʾ����
/// 
///@param[in] int m_currentFrameNO--��ǰ֡��, int totalFrameCount--��֡��, int videoTimeInSecond--��Ƶʱ�䳤�ȣ�s��, CWnd *m_pShowTimeWnd--��ʾ�ؼ����, int flag--��ʾ����
///@pre  NULL
///@return NULL
///@retval BOOL
///@post NULL
void Cvideotest2Dlg::ShowTime(int m_currentFrameNO, int totalFrameCount, 
						   int videoTimeInSecond, CWnd *m_pShowTimeWnd, int flag)
{
	CString CurVideoTime;
	if (flag == 1)
	{	
		int CurrentTimeInSecond = (double)m_currentFrameNO/double(totalFrameCount)*videoTimeInSecond;
		int CurVedioHour=CurrentTimeInSecond/3600;
		int CurVedioMinute=CurrentTimeInSecond/60-CurVedioHour*60;
		int CurVedioSecond=CurrentTimeInSecond-CurVedioHour*3600-CurVedioMinute*60;

		int VedioHour= videoTimeInSecond/3600;
		int VedioMinute= videoTimeInSecond/60-VedioHour*60;
		int VedioSecond= videoTimeInSecond-VedioHour*3600-VedioMinute*60;

		CurVideoTime.Format(" %d:%d:%d / %d:%d:%d ",CurVedioHour,CurVedioMinute,CurVedioSecond,VedioHour,VedioMinute,VedioSecond);
		m_pShowTimeWnd->SetWindowText(CurVideoTime);
	}
	else if (flag == 0)
	{
		CurVideoTime.Format(" %d:%d:%d / %d:%d:%d ",0,0,0,0,0,0);
		m_pShowTimeWnd->SetWindowText(CurVideoTime);
	}

}

///@brief ��ʾCEdit* m_wndEditFrameNo��Ӧ����������ʾ��֡���������鿴��ǰ֡��������֡��ת��ָ��֡
///@QiFeng 
void Cvideotest2Dlg::ShowCurrentFrameNO(int m_currentFrameNO, CEdit* m_wndEditFrameNo)
{
	CString _Str_FrameNo;
	_Str_FrameNo.Format("%d", m_currentFrameNO);
	m_wndEditFrameNo->SetWindowTextA(_T(_Str_FrameNo));
}

void Cvideotest2Dlg::OnBnClickedBtnGotoFrame()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//�����
	CString m_StrInputFrameNo;
	m_wndEditInputFrameNo1.GetWindowTextA(m_StrInputFrameNo);
	m_nInputFrameNo1 = _ttoi(m_StrInputFrameNo);
	//<���ж�������Ƿ�ı���֡��  @QiFeng
	if (m_nInputFrameNo1 != player1.m_currentFrameNO)
	{
			CvCapture *capture = cvCreateFileCapture(PathName);///<��ȡ��Ƶͷָ��
			if (!capture)
			{///��ȡʧ�ܣ������ʾ���
				AfxMessageBox("��Ҫ���ŵ��ļ����𻵻����Ѿ���ԭ·���Ƴ�������\n������ѡ���ļ���");
				//return 0;
			}
			cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, m_nInputFrameNo1);
			player1.m_currentFrameNO = m_nInputFrameNo1; 		
			
			
			IplImage *m_curFrame;//��ǰָ֡��
			m_curFrame = cvQueryFrame(capture);///<��ȡ��ǰ֡ͼ��
			if (!m_curFrame)
				return;
			player1.m_playState = PLAY_STATE_PAUSE;
			player1.disPlayImage.ShowPicture( player1.m_windowName,m_curFrame);
			
			
			player1.bEditIsChange = true;
	}
		
}


void Cvideotest2Dlg::OnBnClickedBtnGotoPara()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����
	CString m_StrInput_nPara;
	m_wndEditInput_nPara.GetWindowTextA(m_StrInput_nPara);
	int m_nPara = _ttoi(m_StrInput_nPara);

	///<���ݿ������Ӧ��֡��

	int m_ParaStartFrame = m_MysqlVideoParaSearchHandle->FindStartFrameFromVideoFGTable(m_nPara, m_videoPro->m_tableParams.VideoFGTableName);		
	int m_ParaEndFrame = m_MysqlVideoParaSearchHandle->FindEndFrameFromVideoFGTable(m_nPara, m_videoPro->m_tableParams.VideoFGTableName);		
		
	if (m_ParaStartFrame == -1)  
	{
			MessageBox("֡����ȡ����");
			return;
	}
	else
	{
			player1.m_startFrameNO = MAX(0,m_ParaStartFrame - 50);          ///<δ�ܴ����ݿ��ж�ȡ֡�ţ���Ĭ�ϲ���ǰ500�ͺ�1000֡
			player1.m_endFrameNO   = m_ParaEndFrame + 300;		
	}					
			player1.playPiece();												///<����ԭʼ�������Ĳ���״̬
				 
			If_playpiece=TRUE;
			player1.m_gotCVlclick = FALSE; 

}




void Cvideotest2Dlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		player2.timeshow=TRUE;
		player2.d_AbsVideoTimeRatio = (player1.m_endFrameNO- player1.m_startFrameNO)/ player1.m_videoTimeInSecond;//totalFrameCount--��֡��*videoTimeInSecond--��Ƶʱ�䳤�ȣ�s��
	}
	else
	{
		player2.timeshow=FALSE;
	}
	
}

void cvMouseHandlerInPic(int eventType, int x, int y, int flags, void *param)
{
	switch (eventType)
	{
	case CV_EVENT_LBUTTONDOWN:///�������     
	{
								  mousePosInPic.x = x;
								  mousePosInPic.y = y;
								  mousePosInPic.x1 = x;
								  mousePosInPic.y1 = y;
								  mousePosInPic.clickInCVwnd = TRUE;
								  mousePosInPic.lBtnUp = FALSE;
	}
		break;
	case CV_EVENT_LBUTTONUP:///�������
	{
								if (mousePosInPic.clickInCVwnd == TRUE)
								{
									mousePosInPic.x1 = x;
									mousePosInPic.y1 = y;
									mousePosInPic.lBtnUp = TRUE;
									mousePosInPic.clickInCVwnd = FALSE;
								}
	}
		break;
	case CV_EVENT_MOUSEMOVE:///����϶�
	{
								if (mousePosInPic.clickInCVwnd == TRUE && mousePosInPic.lBtnUp == FALSE)
								{
									mousePosInPic.x1 = x;
									mousePosInPic.y1 = y;
								}
	}
		break;
	}
}



