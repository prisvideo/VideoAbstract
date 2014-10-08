
// videotest2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "videotest2.h"
#include "videotest2Dlg.h"
#include "afxdialogex.h"
#include "afxdlgs.h"
#include "ifRebuildDlg.h"
#include "CvvImage.h"
#include "LibMySql.h"
#include "VideoSeg.h"
#include "SkinPPWTL.h"
#include "Dialog1.h"
#include "vidPlayer.h"
#include "picsum.h"
#include "ChangeIniFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)

CDataMySql *m_MysqlHandle = new CDataMySql; ///<���ݿ���
pointForCvMouse mousePosInPic1;
pointForCvMouse mousePosInPic2;
BOOL ifClick3 = FALSE;
BOOL ifClick4 = FALSE;
BOOL ifinitDisplay3=FALSE;	//����3��ʼ����ʶ��
BOOL ifinitDisplay4 = FALSE;    //����4��ʼ����ʶ��



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

public:
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnSize(UINT nType, int cx, int cy);
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
	m_page1.Tab1_ifStartPro = false;
	m_page1.Tab1_playpiece = FALSE;
	m_MysqlVideoParaSearchHandle = new CDataMySql;
	m_videoPro = new CVideo;
	
}

Cvideotest2Dlg::~Cvideotest2Dlg()
	
{
	if(m_videoPro != NULL)
	{
		delete m_videoPro;
		m_videoPro = NULL;
	}
	if(m_MysqlVideoParaSearchHandle != NULL)
	{		delete m_MysqlVideoParaSearchHandle;
	m_MysqlVideoParaSearchHandle = NULL;
	}		   ///<ɾ�����ݿ����ָ��
}

void Cvideotest2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	

	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_BTN_OPEN, Btn_BTN1_OPEN);
	DDX_Control(pDX, IDC_BTN_VIEW, Btn_BTN1_VIEW);
	DDX_Control(pDX, IDC_BTN_ABOUT, Btn_BTN1_ABOUT);
	DDX_Control(pDX, IDC_BTN_exit, Btn_BTN1_EXIT);
	DDX_Control(pDX, IDC_BTN_SAVE, Btn_BTN1_SAVE);
	DDX_Control(pDX, IDC_BTN_TITLE, Btn_BTN1_TITLE);
}

BEGIN_MESSAGE_MAP(Cvideotest2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	
	ON_COMMAND(ID_ABOUT, &Cvideotest2Dlg::OnAbout)
	
	ON_COMMAND(ID_32778, &Cvideotest2Dlg::OnClickObjectViewDlg)
	ON_COMMAND(ID_32772, &Cvideotest2Dlg::OnMenuClickedOpen)
	ON_COMMAND(ID_MENUITEM_UltraBlue, &Cvideotest2Dlg::OnMenuitemUltrablue)
	ON_COMMAND(ID_MENUITEM_vladstudio, &Cvideotest2Dlg::OnMenuitemvladstudio)
	ON_COMMAND(ID_MENUITEM_Phenom, &Cvideotest2Dlg::OnMenuitemPhenom)
	ON_COMMAND(ID_MENUITEM_AquaOS, &Cvideotest2Dlg::OnMenuitemAquaos)
	
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &Cvideotest2Dlg::OnTcnSelchangeTab1)
	
	ON_BN_CLICKED(IDC_BTN_OPEN, &Cvideotest2Dlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_VIEW, &Cvideotest2Dlg::OnBnClickedBtnView)
	ON_BN_CLICKED(IDC_BTN_ABOUT, &Cvideotest2Dlg::OnBnClickedButtonSettings)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_exit, &Cvideotest2Dlg::OnBnClickedBtnexit)
END_MESSAGE_MAP()


// Cvideotest2Dlg ��Ϣ�������

BOOL Cvideotest2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	WelDlg.DoModal();

	skinppRemoveSkin();
	skinppLoadSkin(_T("..\\SkinPlusplus\\Phenom.ssk"));
	Invalidate();

	UIBeautifier.LoadBackgroundPic(IDB_background);///<����λͼ����
	CWnd* pWnd = CWnd::GetDesktopWindow();
	pWnd->GetClientRect(UIBeautifier.rcDeskRect);///��ȡ�������
	BitmapBackGroundStrech=UIBeautifier.CBitmapResize(UIBeautifier.m_BitmapBackGround,UIBeautifier.rcDeskRect.Width(),UIBeautifier.rcDeskRect.Height());


	GetDlgItem(IDC_TAB1)->MoveWindow(50.0*UIBeautifier.rcDeskRect.Width()/1214,110.0*UIBeautifier.rcDeskRect.Height()/760,1120.0*UIBeautifier.rcDeskRect.Width()/1214,610.0*UIBeautifier.rcDeskRect.Height()/760);
	GetDlgItem(IDC_BTN_OPEN)->MoveWindow(20.0*UIBeautifier.rcDeskRect.Width()/1214,25.0*UIBeautifier.rcDeskRect.Height()/760,60.0*UIBeautifier.rcDeskRect.Width()/1214,20.0*UIBeautifier.rcDeskRect.Height()/760);
	GetDlgItem(IDC_BTN_VIEW)->MoveWindow(150.0*UIBeautifier.rcDeskRect.Width()/1214,25.0*UIBeautifier.rcDeskRect.Height()/760,60.0*UIBeautifier.rcDeskRect.Width()/1214,20.0*UIBeautifier.rcDeskRect.Height()/760);
	GetDlgItem(IDC_BTN_ABOUT)->MoveWindow(650.0*UIBeautifier.rcDeskRect.Width()/1214,25.0*UIBeautifier.rcDeskRect.Height()/760,100.0*UIBeautifier.rcDeskRect.Width()/1214,20.0*UIBeautifier.rcDeskRect.Height()/760);
	GetDlgItem(IDC_BTN_exit)->MoveWindow(1050.0*UIBeautifier.rcDeskRect.Width()/1214,25.0*UIBeautifier.rcDeskRect.Height()/760,100.0*UIBeautifier.rcDeskRect.Width()/1214,20.0*UIBeautifier.rcDeskRect.Height()/760);

	UIBeautifier.LoadButtonBitmaps(Btn_BTN1_OPEN, IDB_OPEN_U, IDB_OPEN_D, 67.0 / 1214, 37.0 / 760, 98.0 / 1214, 68.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_BTN1_VIEW, IDB_VIEW_U, IDB_VIEW_D, 157.0 / 1214, 39.0 / 760, 188.0 / 1214, 66.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_BTN1_SAVE, IDB_SAVE_U, IDB_SAVE_D, 247.0 / 1214, 37.0 / 760, 278.0 / 1214, 68.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_BTN1_ABOUT, IDB_ABOUT_U, IDB_ABOUT_D,1022.0 / 1214, 37.0 / 760, 1053.0 / 1214, 68.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_BTN1_EXIT, IDB_EXIT_U, IDB_EXIT_D, 1112.0 / 1214, 37.0 / 760, 1143.0 / 1214, 68.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_BTN1_TITLE, IDB_TITLE, IDB_TITLE, 425.0 / 1214, 5.0 / 760, 805.0 / 1214, 85.0 / 760);
	
	// ��������...���˵�����ӵ�ϵͳ�˵��С�
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
	 TCITEM tc1,tc2,tc3,tc4;
         tc1.mask = TCIF_TEXT;
         tc1.pszText = _T("��ƵժҪ");
         tc2.mask = TCIF_TEXT;
         tc2.pszText = _T("ͼƬժҪ");
		 tc3.mask = TCIF_TEXT;
         tc3.pszText = _T("ǰ��Ŀ��");
		 tc4.mask = TCIF_TEXT;
		 tc4.pszText = _T("�ֻ���");

		 m_tab.SetMinTabWidth(330);

         m_tab.InsertItem(0, &tc1);
         m_tab.InsertItem(1, &tc2); //������ֻ�����������tabҳ
		 m_tab.InsertItem(2, &tc3);
		 m_tab.InsertItem(3, &tc4);

         CRect rec;
         m_tab.GetClientRect(&rec);//���TAB�ؼ�������

         //��λѡ�ҳ��λ�ã�������Ը�������Լ�����ƫ����
         rec.bottom -= 27;
         rec.left += 1;
         rec.top += 27;
         rec.right -= 3;

         //������ҳ��
         m_page1.Create(IDD_DIALOG1,GetDlgItem(IDC_TAB1));
         m_page3.Create(IDD_OBJECT,GetDlgItem(IDC_TAB1));
		 m_page2.Create(IDD_picsum,GetDlgItem(IDC_TAB1));
		 m_page4.Create(IDD_DRAW_DETECT,GetDlgItem(IDC_TAB1));

         //����ҳ���ƶ���ָ����λ��
         m_page1.MoveWindow(&rec);
         m_page2.MoveWindow(&rec);
		 m_page3.MoveWindow(&rec);
		 m_page4.MoveWindow(&rec);
         //��ʾ��ҳ��
         m_page1.ShowWindow(SW_SHOW);
         m_page2.ShowWindow(SW_HIDE);
		 m_page3.ShowWindow(SW_HIDE);
		 m_page4.ShowWindow(SW_HIDE);

		 pDialog[0] = &m_page1;
         pDialog[1] = &m_page2;
		 pDialog[2] = &m_page3;
		 pDialog[3] = &m_page4;
        //��ʾ��ʼҳ��
        pDialog[0]->ShowWindow(SW_SHOW);
        pDialog[1]->ShowWindow(SW_HIDE);
		pDialog[2]->ShowWindow(SW_HIDE);
		pDialog[3]->ShowWindow(SW_HIDE);
        //���浱ǰѡ��
        m_CurSelTab = 0;

	//CBitmap *m_bmp_title=new CBitmap;
	//m_bmp_title->LoadBitmap(IDB_TITLE);
	//HBITMAP hBmp_title;// = HBITMAP(m_bmp);//��CBitmapת��ΪHBITMAP
	//hBmp_title=(HBITMAP)(*m_bmp_title);
	//((CStatic *)GetDlgItem(IDC_STATIC_TITLE))->SetBitmap(hBmp_title);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


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
		this->MoveWindow(UIBeautifier.rcDeskRect.left, UIBeautifier.rcDeskRect.top, UIBeautifier.rcDeskRect.Width(), UIBeautifier.rcDeskRect.Height(), TRUE); ///<��ѡ���λ
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cvideotest2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cvideotest2Dlg::OnTimer(UINT nIDEvent)
{
}

void Cvideotest2Dlg::OnAppExit()
{
	
	SendMessage(WM_CLOSE);
	
}

void cvMouseHandlerInPic1(int eventType, int x, int y, int flags, void *param)
{
	switch (eventType)
	{
	case CV_EVENT_LBUTTONDOWN:///�������     
	{
								  mousePosInPic1.x = x;
								  mousePosInPic1.y = y;
								  mousePosInPic1.x1 = x;
								  mousePosInPic1.y1 = y;
								  mousePosInPic1.clickInCVwnd = TRUE;
								  mousePosInPic1.lBtnUp = FALSE;
	}
		break;
	case CV_EVENT_LBUTTONUP:///�������
	{
								if (mousePosInPic1.clickInCVwnd == TRUE)
								{
 									mousePosInPic1.x1 = x;
									mousePosInPic1.y1 = y;
									mousePosInPic1.lBtnUp = TRUE;
									mousePosInPic1.clickInCVwnd = FALSE;
								}
	}
		break;
	case CV_EVENT_MOUSEMOVE:///����϶�
	{
								if (mousePosInPic1.clickInCVwnd == TRUE && mousePosInPic1.lBtnUp == FALSE)
								{
									mousePosInPic1.x1 = x;
									mousePosInPic1.y1 = y;
								}
	}
		break;
	}
}
void cvMouseHandlerInPic2(int eventType, int x, int y, int flags, void *param)
{
	switch (eventType)
	{
	case CV_EVENT_LBUTTONDOWN:///�������     
	{
		mousePosInPic2.x = x;
		mousePosInPic2.y = y;
		mousePosInPic2.x1 = x;
		mousePosInPic2.y1 = y;
		mousePosInPic2.clickInCVwnd = TRUE;
		mousePosInPic2.lBtnUp = FALSE;
	}
		break;
	case CV_EVENT_LBUTTONUP:///�������
	{
		if (mousePosInPic2.clickInCVwnd == TRUE)
		{
			mousePosInPic2.x1 = x;
			mousePosInPic2.y1 = y;
			mousePosInPic2.lBtnUp = TRUE;
			mousePosInPic2.clickInCVwnd = FALSE;
		}
	}
		break;
	case CV_EVENT_MOUSEMOVE:///����϶�
	{
		if (mousePosInPic2.clickInCVwnd == TRUE && mousePosInPic2.lBtnUp == FALSE)
		{
			mousePosInPic2.x1 = x;
			mousePosInPic2.y1 = y;
		}
	}
		break;
	}
}

void Cvideotest2Dlg::OnAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void Cvideotest2Dlg::OnClickObjectViewDlg()
{
	// TODO: Add your command handler code here
	CString m_strSql;
	MYSQL_RES *m_result;
	m_strSql.Format("select * from %s",m_videoPro->m_tableParams.CombineSegsTableName) ;//00015_h_combinesegstable
	int i=mysql_real_query(&m_MysqlVideoParaSearchHandle->m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength());
	if(i!=0)
	{
		AfxMessageBox("���ȵ������ժҪ");
		return;
	}
	else
	{
		m_result=mysql_store_result(&m_MysqlVideoParaSearchHandle->m_mysql);///<�����ѯ�������ݵ�m_result
		ObjectDlg.oriPlayer=player1;
		ObjectDlg.m_MysqlVideoHandle=m_MysqlVideoParaSearchHandle;
		ObjectDlg.videoPro=m_videoPro;
		SetTimer(6, 100, NULL);
		ObjectDlg.DoModal();
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
		ObjectDlg.Generated=FALSE;
	}
}


void Cvideotest2Dlg::OnMenuClickedOpen()
{
	// TODO: Add your command handler code here
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


void Cvideotest2Dlg::OnMenuitemUltrablue()
{
	// TODO: Add your command handler code here
	if(SubMenuCheckedNO != 2)
	{
		skinppRemoveSkin();
		skinppLoadSkin(_T("..\\SkinPlusplus\\DameK UltraBlue.ssk"));
		Invalidate();
		GetMenu()->GetSubMenu(2)->CheckMenuItem(SubMenuCheckedNO, MF_UNCHECKED|MF_BYPOSITION);
		GetMenu()->GetSubMenu(2)->CheckMenuItem(2, MF_CHECKED|MF_BYPOSITION);
		SubMenuCheckedNO = 2;
	}
}


void Cvideotest2Dlg::OnMenuitemvladstudio()
{
	// TODO: Add your command handler code here
	if(SubMenuCheckedNO != 0)
	{
		skinppRemoveSkin();
		skinppLoadSkin(_T("..\\SkinPlusplus\\vladstudio.ssk"));
		Invalidate();
		GetMenu()->GetSubMenu(2)->CheckMenuItem(SubMenuCheckedNO, MF_UNCHECKED|MF_BYPOSITION);
		GetMenu()->GetSubMenu(2)->CheckMenuItem(0, MF_CHECKED|MF_BYPOSITION);
		SubMenuCheckedNO = 0;
	}
}


void Cvideotest2Dlg::OnMenuitemPhenom()
{
	// TODO: Add your command handler code here
	if(SubMenuCheckedNO != 1)
	{
		skinppRemoveSkin();
		skinppLoadSkin(_T("..\\SkinPlusplus\\Phenom.ssk"));	
		Invalidate();
		GetMenu()->GetSubMenu(2)->CheckMenuItem(SubMenuCheckedNO, MF_UNCHECKED|MF_BYPOSITION);
		GetMenu()->GetSubMenu(2)->CheckMenuItem(1, MF_CHECKED|MF_BYPOSITION);
		SubMenuCheckedNO = 1;
	}
}


void Cvideotest2Dlg::OnMenuitemAquaos()
{
	// TODO: Add your command handler code here
	if(SubMenuCheckedNO != 3)
	{
		skinppRemoveSkin();
		skinppLoadSkin(_T("..\\SkinPlusplus\\AquaOS.ssk"));
		Invalidate();
		GetMenu()->GetSubMenu(2)->CheckMenuItem(SubMenuCheckedNO, MF_UNCHECKED|MF_BYPOSITION);
		GetMenu()->GetSubMenu(2)->CheckMenuItem(3, MF_CHECKED|MF_BYPOSITION);
		SubMenuCheckedNO = 3;
	}
}


/*void Cvideotest2Dlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_dlg1.DoModal();
	m_dlg1.dlg1_MysqlHandle = m_MysqlVideoParaSearchHandle;

	
}
*/

void Cvideotest2Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
    //�õ��µ�ҳ������
    m_CurSelTab = m_tab.GetCurSel();
    //���µ�ҳ����ʾ����
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	//����ҳ����Ӧ
	switch(m_CurSelTab)
	{
	case 0:
	{
		if (m_page2.playerori_TAB2.m_playState == PLAY_STATE_PLAY)
		{///����״̬��
			m_page2.playerori_TAB2.pause();
		}
		if (m_page3.ObjectPlayer.m_playState == PLAY_STATE_PLAY)
		{///����״̬��
			m_page3.ObjectPlayer.pause();
		}
		if (m_page1.Tab1_Player1.m_filePath != "")
		{
			m_page1.Tab1_Player1.play();
		}
		if (m_page4.player.m_playState == PLAY_STATE_PLAY)
		{///����״̬��
			m_page4.player.pause();
		}
		m_page2.playerori_TAB2.play();
		break;
	}
	case 1:
	{
		if(m_page2.playerori_TAB2.m_filePath !="")
		{
			CString m_tmpFileName1, m_tmpFileName2;
			GetVideoNameFromAbsolutePath1(&m_page1.Tab1_Player1.m_filePath, &m_tmpFileName1);///<��ȡ�ļ���(������׺)
			GetFileNameBeforeDot(&m_tmpFileName1, &m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
			CString path = "../" + m_tmpFileName2 + "/" + m_tmpFileName2 + "_fusion.avi";
			if (_access(path, 0) == -1)
			{
				AfxMessageBox("���ȵ������ժҪ");
				return;
			}
			else
			{
				//m_result1=mysql_store_result(&m_MysqlVideoParaSearchHandle->m_mysql);///<�����ѯ�������ݵ�m_result
				//m_page3.oriPlayer=m_page1.Tab1_Player1;
				m_page2.Tab2_MysqlVideoParaSearchHandle=m_MysqlVideoParaSearchHandle;
				m_page2.m_videoPro=m_page1.Tab1_videoPro;
				m_page2.playerori_TAB2.m_filePath = m_page1.Tab1_Player1.m_filePath;
				//if(m_result1!=NULL) mysql_free_result(m_result1);///<�ͷŽ����Դ
				//m_page2.Generated=FALSE;
			}

			//���Ŵ���
			if (m_page1.Tab1_Player1.m_playState == PLAY_STATE_PLAY)
			{///����״̬��
				m_page1.Tab1_Player1.pause();
				m_page1.Tab1_Player2.pause();
			}
			if (m_page3.ObjectPlayer.m_playState == PLAY_STATE_PLAY)
			{///����״̬��
				m_page3.ObjectPlayer.pause();
			}
			if (m_page4.player.m_playState == PLAY_STATE_PLAY)
			{///����״̬��
				m_page4.player.pause();
			}
			m_page2.playerori_TAB2.play();
		}
		break;
	}
	case 2:
	{
		if(m_page2.playerori_TAB2.m_filePath !="")
		{
			CString m_tmpFileName1, m_tmpFileName2;
			GetVideoNameFromAbsolutePath1(&m_page1.Tab1_Player1.m_filePath, &m_tmpFileName1);///<��ȡ�ļ���(������׺)
			GetFileNameBeforeDot(&m_tmpFileName1, &m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
			CString path = "../" + m_tmpFileName2 + "/" + m_tmpFileName2 + "_fusion.avi";
			if (_access(path, 0) == -1)
			{
				//����tab1
				AfxMessageBox("���ȵ������ժҪ");
				return;
			}
			else
			{
				//m_result2=mysql_store_result(&m_MysqlVideoParaSearchHandle->m_mysql);///<�����ѯ�������ݵ�m_result
				//m_page3.oriPlayer=m_page1.Tab1_Player1;
				m_page3.m_MysqlVideoHandle=m_MysqlVideoParaSearchHandle;
				m_page3.videoPro=m_page1.Tab1_videoPro;
				m_page3.oriPlayer.m_filePath=m_page1.Tab1_PathName;
				//if(m_result2!=NULL) mysql_free_result(m_result2);///<�ͷŽ����Դ
				//m_page3.Generated=FALSE;
			}

			//ԭ���鿴btn���е�Object����
			//m_page3.m_pageNum = 0;
			//m_page3.Generated=TRUE;
			//m_page3.DetectResult();
			//m_page3.DisplayPageSumImg();
			////ObjectPlayer.play();
			//m_page3.pScrollBar->SetScrollRange(0,(m_page3.objDetectedInfos.size()-4>0)?m_page3.objDetectedInfos.size()-4:0);//�����ƶ���λ��Ϊ0����100��
		

			//���Ŵ���
			if (m_page1.Tab1_Player1.m_playState == PLAY_STATE_PLAY)
			{///����״̬��
				m_page1.Tab1_Player1.pause();
				m_page1.Tab1_Player2.pause();
			}
			if (m_page2.playerori_TAB2.m_playState == PLAY_STATE_PLAY)
			{///����״̬��
				m_page2.playerori_TAB2.pause();
			}
			if (m_page4.player.m_playState == PLAY_STATE_PLAY)
			{///����״̬��
				m_page4.player.pause();
			}
			m_page3.ObjectPlayer.play();
		}
		break;
	}

	case 3:
	{
		if(m_page4.player.m_filePath !="" && m_page4.player.m_filePath !="")
		{
			CString m_tmpFileName1, m_tmpFileName2;
			GetVideoNameFromAbsolutePath1(&m_page1.Tab1_Player1.m_filePath, &m_tmpFileName1);///<��ȡ�ļ���(������׺)
			GetFileNameBeforeDot(&m_tmpFileName1, &m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
			CString path = "../" + m_tmpFileName2 + "/" + m_tmpFileName2 + "_fusion.avi";
			if (_access(path, 0) == -1)
			{
				//����tab1
				AfxMessageBox("���ȵ������ժҪ");
				return;
			}
			else
			{
				//m_result2=mysql_store_result(&m_MysqlVideoParaSearchHandle->m_mysql);///<�����ѯ�������ݵ�m_result
				//m_page3.oriPlayer=m_page1.Tab1_Player1;
				m_page4.m_MysqlHandle=m_MysqlVideoParaSearchHandle;
				m_page4.draw_videoPro=m_page1.Tab1_videoPro;
				m_page4.player.m_filePath=m_page1.Tab1_PathName;
				m_page4.objtablename=m_page1.Tab1_videoPro->m_tableParams.ObjectTableName;
				m_page4.oriPlayer.objtablename=m_page1.Tab1_videoPro->m_tableParams.ObjectTableName;
				//m_MysqlVideoParaSearchHandle->IfExistTable(m_page1.Tab1_videoPro->m_tableParams.ObjectTableName,&m_page4.m_ifExistProData);
				//if(m_result2!=NULL) mysql_free_result(m_result2);///<�ͷŽ����Դ
				//m_page3.Generated=FALSE;
			}

			//ԭ���鿴btn���е�Object����
			//m_page3.m_pageNum = 0;
			//m_page3.Generated=TRUE;
			//m_page3.DetectResult();
			//m_page3.DisplayPageSumImg();
			////ObjectPlayer.play();
			//m_page3.pScrollBar->SetScrollRange(0,(m_page3.objDetectedInfos.size()-4>0)?m_page3.objDetectedInfos.size()-4:0);//�����ƶ���λ��Ϊ0����100��


			//���Ŵ���
			if (m_page1.Tab1_Player1.m_playState == PLAY_STATE_PLAY)
			{///����״̬��
				m_page1.Tab1_Player1.pause();
				m_page1.Tab1_Player2.pause();
			}
			if (m_page2.playerori_TAB2.m_playState == PLAY_STATE_PLAY)
			{///����״̬��
				m_page2.playerori_TAB2.pause();
			}
			m_page3.ObjectPlayer.play();
			
			if (m_page3.ObjectPlayer.m_playState == PLAY_STATE_PLAY)
			{///����״̬��
				m_page3.ObjectPlayer.pause();
			}
			m_page4.player.play();
		}
		break;
	}
	default:
		break;

	}

	
	*pResult = 0;
}
void Cvideotest2Dlg::OnBnClickedBtnOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Files (*.mp3 *.wma *.dat *.wmv *.avi *.mov *.mmm *.mid *.mpeg)|*.mp3;*.wma;*.dat;*.wmv;*.avi;*.mov;*.mmm;*.mid;*.mpeg|All Files (*.*)|*.*||"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		if (m_page1.Tab1_Player1.m_currentFrameNO != 0)
		{
			m_page1.Tab1_Player1.stopPlay();
		}

		m_page1.Tab1_PathName = dlg.GetPathName();
		m_page1.Tab1_PathName.MakeUpper();

		m_page1.Tab1_Player1.m_filePath = m_page1.Tab1_PathName;

		m_page1.Tab1_Player1.playInitial(m_page1.GetDlgItem(IDC_STATIC_TAB1_ORI), "displayWindow1");//�ó�ʼ����Ҫ���ļ�·��ȷ�Ϻ����
		m_page1.Tab1_CSliderPlayer1Ctrl.SetRange(0, m_page1.Tab1_Player1.m_endFrameNO);
		m_page1.Tab1_CSliderPlayer1Ctrl.SetPos(0);

		//m_page1.Tab1_Player1.play();



		if (m_page2.playerori_TAB2.m_currentFrameNO != 0)
		{
			m_page2.playerori_TAB2.stopPlay();
		}
		m_page2.playerori_TAB2.m_filePath = m_page1.Tab1_Player1.m_filePath;

		m_page2.playerori_TAB2.playInitial(m_page2.GetDlgItem(IDC_STATIC_TAB2_ORI), "ori_displaywindow");//�ó�ʼ����Ҫ���ļ�·��ȷ�Ϻ����
		m_page2.Tab2_CSliderPlayer1Ctrl.SetRange(0, m_page2.playerori_TAB2.m_endFrameNO);
		m_page2.Tab2_CSliderPlayer1Ctrl.SetPos(0);

		//m_page2.playerori_TAB2.play();


		if (m_page3.ObjectPlayer.m_currentFrameNO != 0)
		{
			m_page3.ObjectPlayer.stopPlay();
		}
		m_page3.ObjectPlayer.m_filePath = m_page1.Tab1_PathName;

		m_page3.ObjectPlayer.playInitial(m_page3.GetDlgItem(IDC_STATIC_OBJECT), "ori_window_Tab3");//�ó�ʼ����Ҫ���ļ�·��ȷ�Ϻ����
		m_page3.m_CSliderPlayerCtrl.SetRange(0, m_page3.ObjectPlayer.m_endFrameNO);
		m_page3.m_CSliderPlayerCtrl.SetPos(0);



		if (m_page4.player.m_currentFrameNO != 0)
		{
			m_page4.player.stopPlay();
		}
		m_page4.player.m_filePath = m_page1.Tab1_PathName;

		m_page4.player.playInitial(m_page4.GetDlgItem(IDC_DISPLAY_IN_DRAW_DETECT), "ori_window_Tab4");//�ó�ʼ����Ҫ���ļ�·��ȷ�Ϻ����
		m_page4.m_CSlider_playerCtrl.SetRange(0, m_page4.player.m_endFrameNO);
		m_page4.m_CSlider_playerCtrl.SetPos(0);

		m_page4.oriPlayer.m_filePath = m_page1.Tab1_PathName;

		m_page4.oriPlayer.playInitial(m_page4.GetDlgItem(IDC_DISPLAY_IN_DRAW_DETECT2), "ori_detect_window_Tab4");//�ó�ʼ����Ҫ���ļ�·��ȷ�Ϻ����
		m_page4.m_CSlider_oriplayerCtrl.SetRange(0, m_page4.oriPlayer.m_endFrameNO);
		m_page4.m_CSlider_oriplayerCtrl.SetPos(0);




	}

	else
		return;
		

	CString m_pFilePath = m_page1.Tab1_PathName;
	CString m_tmpFileName1, m_tmpFileName2;
	GetVideoNameFromAbsolutePath1(&m_pFilePath, &m_tmpFileName1);///<��ȡ�ļ���(������׺)
	GetFileNameBeforeDot(&m_tmpFileName1, &m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
	m_page1.Tab1_videoPro->m_tableParams.VideoFGTableName.Format("%s_VideoFGTable", m_tmpFileName2);
	m_page1.Tab1_videoPro->m_tableParams.FGTraceTableName.Format("%s_FGTraceTable", m_tmpFileName2);
	m_page1.Tab1_videoPro->m_tableParams.NewToOldFrameTableName.Format("%s_New2OldFrameTable", m_tmpFileName2);
	m_page1.Tab1_videoPro->m_tableParams.NewTraceTable.Format("%s_NewTraceTable", m_tmpFileName2);
	m_page1.Tab1_videoPro->m_tableParams.CombineSegsTableName.Format("%s_CombineSegsTable", m_tmpFileName2);
	m_page1.Tab1_videoPro->m_tableParams.ObjectTableName.Format("%s_ObjectTable", m_tmpFileName2);


	switch(m_CurSelTab)
	{
	case 0:
		{
			m_page1.Tab1_Player1.play();
			break;
		}
	case 1:
		{
			m_page2.playerori_TAB2.play();
			break;
		}
	case 2:
		{
			m_page3.ObjectPlayer.play();

			CString m_strSql;
			MYSQL_RES *m_result;
			m_strSql.Format("select * from %s",m_page1.Tab1_videoPro->m_tableParams.CombineSegsTableName) ;//00015_h_combinesegstable
			int i=mysql_real_query(&m_MysqlVideoParaSearchHandle->m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength());
			if(i!=0)
			{
				AfxMessageBox("���ȷ��ص�һҳ�������ժҪ");
				return;
			}
			else
			{
				m_result=mysql_store_result(&m_MysqlVideoParaSearchHandle->m_mysql);///<�����ѯ�������ݵ�m_result
				//m_page3.oriPlayer=m_page1.Tab1_Player1;
				m_page3.m_MysqlVideoHandle=m_MysqlVideoParaSearchHandle;
				m_page3.videoPro=m_page1.Tab1_videoPro;
				m_page3.oriPlayer.m_filePath=m_page1.Tab1_PathName;
				if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
				m_page3.Generated=FALSE;
			}

			m_page3.ObjectPlayer.play();
			//ԭ���鿴btn���е�Object����
			//m_page3.m_pageNum = 0;
			//m_page3.Generated=TRUE;
			//m_page3.DetectResult();
			//m_page3.DisplayPageSumImg();
			//m_page3.pScrollBar->SetScrollRange(0,(m_page3.objDetectedInfos.size()-4>0)?m_page3.objDetectedInfos.size()-4:0);//�����ƶ���λ��Ϊ0����100��
		
			break;
		}
	default:
		break;
	}

}

void Cvideotest2Dlg::OnBnClickedBtnView()
{
	// TODO: Add your control notification handler code here
	switch(m_CurSelTab)
	{
	case 0:
		{
			if (m_page1.Tab1_ifStartPro)
			{
				::MessageBox(NULL, _T("ժҪ��δ�������"), _T("error!"), MB_OK);
				return;
			}

			if (m_page1.Tab1_Player1.m_currentFrameNO != 0)
			{
				m_page1.Tab1_Player2.stopPlay();
			}
			CString m_tmpFileName1, m_tmpFileName2;
			GetVideoNameFromAbsolutePath1(&m_page1.Tab1_Player1.m_filePath, &m_tmpFileName1);///<��ȡ�ļ���(������׺)
			GetFileNameBeforeDot(&m_tmpFileName1, &m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
			CString path = "../" + m_tmpFileName2 + "/" + m_tmpFileName2 + "_fusion.avi";
			m_page1.Tab1_Player2.m_filePath = path;
			if (_access(path, 0) == -1)
			{
				AfxMessageBox("�Ҳ����ļ�");
				return;
			}

			m_page1.Tab1_Player2.playInitial(m_page1.GetDlgItem(IDC_STATIC_TAB1_ABS), "displayWindow2");//�ó�ʼ����Ҫ���ļ�·��ȷ�Ϻ����
			m_page1.Tab1_CSliderPlayer2Ctrl.SetRange(0, m_page1.Tab1_Player2.m_endFrameNO);
			m_page1.Tab1_CSliderPlayer2Ctrl.SetPos(0);

			m_page1.Tab1_Player2.play();
			m_page1.Tab1_Player2.m_MysqlVideoParaSearchHandle = m_page1.Tab1_MysqlHandle;
			m_page1.Tab1_Player2.m_videoPro = m_page1.Tab1_videoPro;
			m_page1.Tab1_Player2.timeshow = FALSE;
			break;
		}
	case 1:
		{
			CString m_tmpFileName1, m_tmpFileName2;
			GetVideoNameFromAbsolutePath1(&m_page1.Tab1_Player1.m_filePath, &m_tmpFileName1);///<��ȡ�ļ���(������׺)
			GetFileNameBeforeDot(&m_tmpFileName1, &m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
			CString path = "../" + m_tmpFileName2 + "/" + m_tmpFileName2 + "_fusion.avi";
			if (m_page1.Tab1_ifStartPro||_access(path, 0) == -1)
				{
					AfxMessageBox("���ȷ��ص�һҳ�������ժҪ");
					return;
				}
			m_page2.m_pagenum = 0;
			m_page2.Generated = TRUE;
			m_page2.DisplaySumImg();
			break;
		}
	case 2:
		{
			CString m_tmpFileName1, m_tmpFileName2;
			GetVideoNameFromAbsolutePath1(&m_page1.Tab1_Player1.m_filePath, &m_tmpFileName1);///<��ȡ�ļ���(������׺)
			GetFileNameBeforeDot(&m_tmpFileName1, &m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
			CString path = "../" + m_tmpFileName2 + "/" + m_tmpFileName2 + "_fusion.avi";
			if (m_page1.Tab1_ifStartPro||_access(path, 0) == -1)
				{
					AfxMessageBox("���ȷ��ص�һҳ�������ժҪ");
					return;
				}
			m_page3.m_pageNum = 0;
			m_page3.Generated=TRUE;
			m_page3.DetectResult();
			m_page3.DisplayPageSumImg();
			//ObjectPlayer.play();
			m_page3.pScrollBar->SetScrollRange(0,(m_page3.objDetectedInfos.size()-4>0)?m_page3.objDetectedInfos.size()-4:0);//�����ƶ���λ��Ϊ0����100��
			//m_page3.m_CSliderPlayerCtrl.SetRange(0, m_page3.ObjectPlayer.m_endFrameNO);   ///<��ʼ������һ�Ļ�����
			//m_page3.m_CSliderPlayerCtrl.SetPos(0);
			break;
		}
	default:
		break;
	}
}



void Cvideotest2Dlg::OnBnClickedButtonSettings()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ChangeIniFileDlg m_ChangeIniDlg;
	//m_ChangeIniDlg.DoModal();
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void Cvideotest2Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	//CWnd * pWnd1=GetDlgItem(IDC_TAB1);
	//	if (pWnd1->GetSafeHwnd())
	//	{
	//		pWnd1->MoveWindow(15,15,cx-30,cy-30);
	//	}
}


void Cvideotest2Dlg::OnBnClickedBtnexit()
{
	// TODO: Add your control notification handler code here
	OnAppExit();
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_SIZE()
END_MESSAGE_MAP()


//void CAboutDlg::OnSize(UINT nType, int cx, int cy)
//{
//	CDialogEx::OnSize(nType, cx, cy);
//
//	// TODO: �ڴ˴������Ϣ����������
//
//}
