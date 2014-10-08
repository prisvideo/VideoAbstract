// drawDetection.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "videotest2.h"
#include "drawDetection.h"
#include "afxdialogex.h"

// drawDetection �Ի���

extern pointForCvMouse mousePosInCVwmd;     ///<�����Ӧ����

IMPLEMENT_DYNAMIC(drawDetection, CDialogEx)

drawDetection::drawDetection(CWnd* pParent /*=NULL*/)
	: CDialogEx(drawDetection::IDD, pParent)
{
	m_ifExistProData = true;
	m_curVideoPath   = "";
	objtablename     = "";
	tracker.m_IfContinue = false;
	player.m_IfStartDetect = false;
	numOfObj = -1;
	m_MysqlHandle= new CDataMySql;
	draw_videoPro = new CVideo;


}

drawDetection::~drawDetection()
{
}

void drawDetection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_IN_DRAW_DETECT,m_CSlider_playerCtrl);
	DDX_Control(pDX, IDC_SLIDER_IN_DRAW_DETECT2,m_CSlider_oriplayerCtrl);

	DDX_Control(pDX, IDC_BTN_PLAY_IN_DRAW_DETECT, Btn_BTN1_DRAW_PLAY);
	DDX_Control(pDX, IDC_BTN_PAUSE_IN_DRAW_DETECT, Btn_BTN1_DRAW_PAUSE);
	DDX_Control(pDX, IDC_BTN_STOP_IN_DRAW_DETECT, Btn_BTN1_DRAW_STOP);
	DDX_Control(pDX, IDC_BTN_PLAY_IN_DRAW_DETECT2, Btn_BTN2_DRAW_PLAY);
	DDX_Control(pDX, IDC_BTN_PAUSE_IN_DRAW_DETECT2, Btn_BTN2_DRAW_PAUSE);
	DDX_Control(pDX, IDC_BTN_STOP_IN_DRAW_DETECT2, Btn_BTN2_DRAW_STOP);
}


BEGIN_MESSAGE_MAP(drawDetection, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PLAY_IN_DRAW_DETECT, &drawDetection::OnBnClickedBtnPlayInDrawDetect)
	ON_BN_CLICKED(IDC_BTN_PAUSE_IN_DRAW_DETECT, &drawDetection::OnBnClickedBtnPauseInDrawDetect)
	ON_BN_CLICKED(IDC_BTN_STOP_IN_DRAW_DETECT, &drawDetection::OnBnClickedBtnStopInDrawDetect)
	ON_BN_CLICKED(IDC_BTN_START_PROCESS__IN_DRAW_DETECT, &drawDetection::OnBnClickedBtnStartProcess)
	ON_BN_CLICKED(IDC_BTN_STOP_PROCESS, &drawDetection::OnBnClickedBtnStopProcess)
	ON_BN_CLICKED(IDC_CHECK_LINE_IN_DRAW_DETECT, &drawDetection::OnBnClickedCheckLineInDrawDetect)
	ON_BN_CLICKED(IDC_CHECK_RECT_IN_DRAW_DETECT, &drawDetection::OnBnClickedCheckRectInDrawDetect)
	ON_BN_CLICKED(IDC_BTN_CLEAR_IN_DRAW_DETECT, &drawDetection::OnBnClickedBtnClearInDrawDetect)
	ON_BN_CLICKED(IDC_BTN_SEARCH_IN_DRAW_DETECT, &drawDetection::OnBnClickedBtnSearchInDrawDetect)
	ON_BN_CLICKED(IDC_BTN_PLAY_IN_DRAW_DETECT2, &drawDetection::OnBnClickedBtnPlayInDrawDetect2)
	ON_BN_CLICKED(IDC_BTN_PAUSE_IN_DRAW_DETECT2, &drawDetection::OnBnClickedBtnPauseInDrawDetect2)
	ON_BN_CLICKED(IDC_BTN_STOP_IN_DRAW_DETECT2, &drawDetection::OnBnClickedBtnStopInDrawDetect2)
	ON_WM_LBUTTONUP()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// drawDetection ��Ϣ�������


BOOL drawDetection::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UIBeautifier.LoadBackgroundPic(IDB_background);///<����λͼ����
	CWnd* pWnd = CWnd::GetDesktopWindow();
	pWnd->GetClientRect(UIBeautifier.rcDeskRect);///��ȡ�������
	BitmapBackGroundStrech = UIBeautifier.CBitmapResize(UIBeautifier.m_BitmapBackGround, UIBeautifier.rcDeskRect.Width(), UIBeautifier.rcDeskRect.Height());


	GetDlgItem(IDC_BTN_START_PROCESS__IN_DRAW_DETECT)->MoveWindow(145.0*UIBeautifier.rcDeskRect.Width() / 1214, 55.0*UIBeautifier.rcDeskRect.Height() / 760, 70.0*UIBeautifier.rcDeskRect.Width() / 1214, 30.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_BTN_STOP_PROCESS)->MoveWindow(145.0*UIBeautifier.rcDeskRect.Width() / 1214, 95.0*UIBeautifier.rcDeskRect.Height() / 760, 70.0*UIBeautifier.rcDeskRect.Width() / 1214, 30.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_PROGRESS_IN_DRAW_DETECT)->MoveWindow(135.0*UIBeautifier.rcDeskRect.Width() / 1214, 20.0*UIBeautifier.rcDeskRect.Height() / 760, 270.0*UIBeautifier.rcDeskRect.Width() / 1214, 20.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_CHECK_LINE_IN_DRAW_DETECT)->MoveWindow(235.0*UIBeautifier.rcDeskRect.Width() / 1214, 55.0*UIBeautifier.rcDeskRect.Height() / 760, 50.0*UIBeautifier.rcDeskRect.Width() / 1214, 30.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_BTN_SEARCH_IN_DRAW_DETECT)->MoveWindow(305.0*UIBeautifier.rcDeskRect.Width() / 1214, 55.0*UIBeautifier.rcDeskRect.Height() / 760, 70.0*UIBeautifier.rcDeskRect.Width() / 1214, 30.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_CHECK_RECT_IN_DRAW_DETECT)->MoveWindow(235.0*UIBeautifier.rcDeskRect.Width() / 1214, 95.0*UIBeautifier.rcDeskRect.Height() / 760, 50.0*UIBeautifier.rcDeskRect.Width() / 1214, 30.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_BTN_CLEAR_IN_DRAW_DETECT)->MoveWindow(305.0*UIBeautifier.rcDeskRect.Width() / 1214, 95.0*UIBeautifier.rcDeskRect.Height() / 760, 70.0*UIBeautifier.rcDeskRect.Width() / 1214, 30.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_DISPLAY_IN_DRAW_DETECT)->MoveWindow(100.0*UIBeautifier.rcDeskRect.Width() / 1214, 140.0*UIBeautifier.rcDeskRect.Height() / 760, 340.0*UIBeautifier.rcDeskRect.Width() / 1214, 255.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_STATIC_TIME_IN_DRAW_DETECT)->MoveWindow(250.0*UIBeautifier.rcDeskRect.Width() / 1214,400.0*UIBeautifier.rcDeskRect.Height() / 760, 80.0*UIBeautifier.rcDeskRect.Width() / 1214, 30.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_SLIDER_IN_DRAW_DETECT)->MoveWindow(330.0*UIBeautifier.rcDeskRect.Width() / 1214, 400.0*UIBeautifier.rcDeskRect.Height() / 760, 110.0*UIBeautifier.rcDeskRect.Width() / 1214, 30.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_DISPLAY_IN_DRAW_DETECT2)->MoveWindow(540.0*UIBeautifier.rcDeskRect.Width() / 1214, 10.0*UIBeautifier.rcDeskRect.Height() / 760, 513.0*UIBeautifier.rcDeskRect.Width() / 1214, 385.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_STATIC_TIME_IN_DRAW_DETECT2)->MoveWindow(690.0*UIBeautifier.rcDeskRect.Width() / 1214, 400.0*UIBeautifier.rcDeskRect.Height() / 760, 100.0*UIBeautifier.rcDeskRect.Width() / 1214, 30.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_SLIDER_IN_DRAW_DETECT2)->MoveWindow(790.0*UIBeautifier.rcDeskRect.Width() / 1214, 400.0*UIBeautifier.rcDeskRect.Height() / 760, 263.0*UIBeautifier.rcDeskRect.Width() / 1214, 30.0*UIBeautifier.rcDeskRect.Height() / 760);

	GetDlgItem(IDC_PIC_CTRL0_IN_DRAW_DETECT)->MoveWindow(7.0*UIBeautifier.rcDeskRect.Width() / 1214, 440.0*UIBeautifier.rcDeskRect.Height() / 760, 158.0*UIBeautifier.rcDeskRect.Width() / 1214, 100.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_PIC_CTRL1_IN_DRAW_DETECT)->MoveWindow(165.0*UIBeautifier.rcDeskRect.Width() / 1214, 440.0*UIBeautifier.rcDeskRect.Height() / 760, 158.0*UIBeautifier.rcDeskRect.Width() / 1214, 100.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_PIC_CTRL2_IN_DRAW_DETECT)->MoveWindow(323.0*UIBeautifier.rcDeskRect.Width() / 1214, 440.0*UIBeautifier.rcDeskRect.Height() / 760, 158.0*UIBeautifier.rcDeskRect.Width() / 1214, 100.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_PIC_CTRL3_IN_DRAW_DETECT)->MoveWindow(481.0*UIBeautifier.rcDeskRect.Width() / 1214, 440.0*UIBeautifier.rcDeskRect.Height() / 760, 158.0*UIBeautifier.rcDeskRect.Width() / 1214, 100.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_PIC_CTRL4_IN_DRAW_DETECT)->MoveWindow(639.0*UIBeautifier.rcDeskRect.Width() / 1214, 440.0*UIBeautifier.rcDeskRect.Height() / 760, 158.0*UIBeautifier.rcDeskRect.Width() / 1214, 100.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_PIC_CTRL5_IN_DRAW_DETECT)->MoveWindow(797.0*UIBeautifier.rcDeskRect.Width() / 1214, 440.0*UIBeautifier.rcDeskRect.Height() / 760, 158.0*UIBeautifier.rcDeskRect.Width() / 1214, 100.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_PIC_CTRL6_IN_DRAW_DETECT)->MoveWindow(955.0*UIBeautifier.rcDeskRect.Width() / 1214, 440.0*UIBeautifier.rcDeskRect.Height() / 760, 158.0*UIBeautifier.rcDeskRect.Width() / 1214, 100.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_DRAW_DETECT_SCROLLBAR)->MoveWindow(7.0*UIBeautifier.rcDeskRect.Width() / 1214, 540.0*UIBeautifier.rcDeskRect.Height() / 760, 1106.0*UIBeautifier.rcDeskRect.Width() / 1214, 25.0*UIBeautifier.rcDeskRect.Height() / 760);

	UIBeautifier.LoadButtonBitmaps(Btn_BTN1_DRAW_PLAY, IDB_PLAY_U, IDB_PLAY_D, 100.0 / 1214, 400.0 / 760, 130.0 / 1214, 430.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_BTN1_DRAW_PAUSE, IDB_PAUSE_U, IDB_PAUSE_D, 150.0 / 1214, 400.0 / 760, 180.0 / 1214, 430.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_BTN1_DRAW_STOP, IDB_STOP_U, IDB_STOP_D, 200.0 / 1214, 400.0/ 760, 230.0 / 1214,430.0/ 760);
	UIBeautifier.LoadButtonBitmaps(Btn_BTN2_DRAW_PLAY, IDB_PLAY_U, IDB_PLAY_D, 540.0 / 1214, 400.0 / 760, 570.0 / 1214, 430.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_BTN2_DRAW_PAUSE, IDB_PAUSE_U, IDB_PAUSE_D, 590.0 / 1214, 400.0 / 760, 620.0 / 1214, 430.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_BTN2_DRAW_STOP, IDB_STOP_U, IDB_STOP_D, 640.0 / 1214, 400.0 / 760, 670.0 / 1214, 430.0 / 760);
	///�󲥷�����ʼ��
	//player.m_filePath = "";
	//player.playInitial(GetDlgItem(IDC_DISPLAY_IN_DRAW_DETECT), "displayWindow1");
	//player.m_startFrameNO = player.m_currentFrameNO = 0;
	player.m_endFrameNO = 0;
	player.m_drawDetectFlag = 0;
	player.m_IfStartDetect = false;

	///�Ҳ�������ʼ��
	oriPlayer.m_filePath = "";
	oriPlayer.playInitial(GetDlgItem(IDC_DISPLAY_IN_DRAW_DETECT2), "displayWindow2");
	oriPlayer.m_startFrameNO = oriPlayer.m_currentFrameNO = 0;
	oriPlayer.m_endFrameNO = 0;
	oriPlayer.m_drawDetectFlag = 0;
	oriPlayer.m_IfStartDetect = false;

	///��������ʼ��
	VTrackPro = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS_IN_DRAW_DETECT);
	VTrackPro->SetRange(0,200);
	VTrackPro->SetPos(0);
	GetDlgItem(IDC_PROGRESS_IN_DRAW_DETECT)->ShowWindow(false);
	GetDlgItem(IDC_BTN_STOP_PROCESS)->ShowWindow(false);

	///���ö�ʱ��
	SetTimer(11,300,NULL);//��ʱ����idΪ11��ʱ����Ϊ300ms
	SetTimer(1,100,NULL);
	SetTimer(2,100,NULL);
	SetTimer(3,100,NULL);

	Draw_Detect_pScrollBar = (CScrollBar*)GetDlgItem(IDC_DRAW_DETECT_SCROLLBAR);

	///��ҳ��ʼ��
	m_pageNum = 0;
	m_pageSum = 7;

	user_click_scrollbar=FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void drawDetection::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1)
	{
		///ˢ�½�����
		CSliderCtrl * SliderCtrl=((CSliderCtrl*)GetDlgItem(IDC_SLIDER_IN_DRAW_DETECT));
		int CurrentPos=SliderCtrl->GetPos();                            ///<��ȡ��ǰ������λ��
		int NewCurrentFrameNO = (double)CurrentPos*double(player.m_endFrameNO-player.m_startFrameNO)
			/(double)SliderCtrl->GetRangeMax();     ///<���ݵ�ǰ������λ�ã����¼���֡��

		if (player.m_playState!=PLAY_STATE_STOP && player.m_playState!=PLAY_STATE_FAST_FORWORD&&player.m_playState!=PLAY_STATE_PLAY_PIECE)///<�������������������Ż���ͣ״̬
		{
			if (abs(NewCurrentFrameNO-player.m_currentFrameNO)>5)
			{
				player.m_currentFrameNO=NewCurrentFrameNO;             ///<�����¼����֡�ţ����ò�����
			}
		}
		SliderCtrl->SetPos(player.m_currentFrameNO);                   ///<�����¼����֡�ţ����û�����
		CWnd *pWndTimeDis = GetDlgItem(IDC_STATIC_TIME_IN_DRAW_DETECT);
		if (player.m_playState != PLAY_STATE_STOP)                     ///<��ֹͣ״̬�£��÷�ʽһ��ʾʱ��
		{
			ShowTime(player.m_currentFrameNO, player.m_endFrameNO - player.m_startFrameNO,
				player.m_videoTimeInSecond, pWndTimeDis, 1);
		}
		else                                                            ///<ֹͣ״̬�£��÷�ʽ����ʾʱ��
		{
			SliderCtrl->SetPos(0);
			ShowTime(player.m_currentFrameNO, player.m_endFrameNO - player.m_startFrameNO,
				player.m_videoTimeInSecond, pWndTimeDis, 0);

		}
	}
	else if(nIDEvent==2)
	{
		///ˢ�½�����
		if (oriPlayer.m_drawDetectFlag != 5)
		{
			CSliderCtrl * SliderCtrl=((CSliderCtrl*)GetDlgItem(IDC_SLIDER_IN_DRAW_DETECT2));
			int n=oriPlayer.m_currentFrameNO;
			int CurrentPos=SliderCtrl->GetPos();
			int NewCurrentFrameNO = (double)CurrentPos*double(oriPlayer.m_endFrameNO-oriPlayer.m_startFrameNO)
				/(double)SliderCtrl->GetRangeMax();//����˵�ǰ�϶�����ָ��֡

			if (oriPlayer.m_playState!=PLAY_STATE_STOP && oriPlayer.m_playState!=PLAY_STATE_FAST_FORWORD&&oriPlayer.m_playState!=PLAY_STATE_PLAY_PIECE)
			{
				if (abs(NewCurrentFrameNO-oriPlayer.m_currentFrameNO)>5)
				{
					oriPlayer.m_currentFrameNO=NewCurrentFrameNO;
				}
			}

			SliderCtrl->SetPos(oriPlayer.m_currentFrameNO);
			CWnd *pWndTimeDis = GetDlgItem(IDC_STATIC_TIME_IN_DRAW_DETECT2);
			if (oriPlayer.m_playState != PLAY_STATE_STOP)
			{ 
				ShowTime(oriPlayer.m_currentFrameNO, oriPlayer.m_endFrameNO - oriPlayer.m_startFrameNO, 
					oriPlayer.m_videoTimeInSecond, pWndTimeDis, 1);
			}
			else
			{
				SliderCtrl->SetPos(0);
				ShowTime(oriPlayer.m_currentFrameNO, oriPlayer.m_endFrameNO - oriPlayer.m_startFrameNO, 
					oriPlayer.m_videoTimeInSecond, pWndTimeDis, 0);
			}
		}
		else 
		{
			CSliderCtrl * SliderCtrl=((CSliderCtrl*)GetDlgItem(IDC_SLIDER_IN_DRAW_DETECT2));
			SliderCtrl->SetPos(oriPlayer.m_currentFrameNO);
			CWnd *pWndTimeDis = GetDlgItem(IDC_STATIC_TIME_IN_DRAW_DETECT2);
			ShowTime(oriPlayer.m_currentFrameNO,Video_FrameCount, oriPlayer.m_videoTimeInSecond, pWndTimeDis, 1);

		}
	}
	else if(nIDEvent==11)
	{
		if (m_ifExistProData)
			return;
		int speed = tracker.VTrackSpeed()*100;
		VTrackPro->SetPos(speed);
		if (speed>=200 && tracker.m_IfContinue)
		{
			///��������������ʱ
			tracker.m_IfContinue = false;///<���������־λ�÷�
			MessageBox("��ɴ���");///<������ʾ����ɴ���
			m_ifExistProData = true;///<���ݿ��������־λΪtrue
			///�޸Ľ���ؼ�����
			GetDlgItem(IDC_PROGRESS_IN_DRAW_DETECT)->ShowWindow(false);
			GetDlgItem(IDC_BTN_STOP_PROCESS)->ShowWindow(false);
			GetDlgItem(IDC_CHECK_LINE_IN_DRAW_DETECT)->EnableWindow(true);
			GetDlgItem(IDC_CHECK_RECT_IN_DRAW_DETECT)->EnableWindow(true);
		}
	}
	else if (nIDEvent==3)
	{
		if (user_click_scrollbar==TRUE)
		{
			m_pageNum=Draw_Detect_pScrollBar->GetScrollPos();
			DisplayPageSumImg();
			user_click_scrollbar = FALSE;
		}
	}
}



void drawDetection::ShowTime(int m_currentFrameNO, int totalFrameCount, 
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

		CurVideoTime.Format(" %d::%d::%d / %d::%d::%d ",CurVedioHour,CurVedioMinute,CurVedioSecond,VedioHour,VedioMinute,VedioSecond);
		m_pShowTimeWnd->SetWindowText(CurVideoTime);
	}
	else if (flag == 0)
	{
		CurVideoTime.Format(" %d::%d::%d / %d::%d::%d ",0,0,0,0,0,0);
		m_pShowTimeWnd->SetWindowText(CurVideoTime);
	}
}


void drawDetection::OnBnClickedBtnPlayInDrawDetect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	///�ж���Ƶ�Ƿ���ȷ��ȡ
	if (player.m_filePath=="")
	{
		AfxMessageBox("��ѡ��Ҫ���ŵ��ļ�������");
		return;
	}
	///�ж���Ƶ�Ƿ���ɴ���
	if (tracker.m_IfContinue)
	{
		MessageBox("���ڶ���Ƶ���д�����ȴ�...");
		return;
	}

	m_CSlider_playerCtrl.SetRange(0, player.m_endFrameNO);///<��������ʼ��
	Video_FrameCount=player.m_endFrameNO;
	CString VideoTime;                                     ///<ʱ����ʾ׼��
	int VedioHour=player.m_videoTimeInSecond/3600;
	int VedioMinute=player.m_videoTimeInSecond/60-VedioHour*60;
	int VedioSecond=player.m_videoTimeInSecond-VedioHour*3600-VedioMinute*60;

	VideoTime.Format(" 0::0::0 / %d::%d::%d ",VedioHour,VedioMinute,VedioSecond);
	GetDlgItem(IDC_STATIC_TIME_IN_DRAW_DETECT)->SetWindowText(VideoTime);///<��ʱ����ʾ���ؼ���


	///�޸Ľ���ؼ�����
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT)->ShowWindow(false);
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT)->ShowWindow(TRUE);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT)->EnableWindow(TRUE);
	///�޸��ֻ���״̬
	if ( BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_LINE_IN_DRAW_DETECT)&&
		IsDlgButtonChecked(IDC_CHECK_RECT_IN_DRAW_DETECT) != BST_CHECKED )
	{
		player.m_drawDetectFlag = 1;   ///<����ʱ��״̬=1
		player.objectIDs.clear();	   ///<���򡢻��߸ı�����ʱ�����objectIDs
	}	
	else if ( BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_RECT_IN_DRAW_DETECT)&&
		IsDlgButtonChecked(IDC_CHECK_LINE_IN_DRAW_DETECT) != BST_CHECKED )
	{
		player.m_drawDetectFlag = 2;   ///<����ʱ��״̬=2
		player.objectIDs.clear();	   ///<���򡢻��߸ı�����ʱ�����objectIDs
	}

	///�������λ��
	mousePosInCVwmd.x = tempDrewPoint1.x;
	mousePosInCVwmd.y = tempDrewPoint1.y;
	mousePosInCVwmd.x1 = tempDrewPoint2.x;
	mousePosInCVwmd.y1 = tempDrewPoint2.y;
	player.play();///<��Ƶ����    //�ڴ˴������߳�
}

///@brief drawDetection���ԭʼ��Ƶ���ڵ���ͣ��ť��Ӧ����
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void drawDetection::OnBnClickedBtnPauseInDrawDetect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (player.m_filePath=="")
	{
		return;
	}
	if (tracker.m_IfContinue)
	{
		MessageBox("���ڶ���Ƶ���д�����ȴ�...");
		return;
	}
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT)->ShowWindow(TRUE);
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT)->ShowWindow(false);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT)->EnableWindow(false);
	tempDrewPoint1 = player.m_clickPosInCVWnd;//�������ĵ�
	tempDrewPoint2 = player.m_lBtnUpPosInCVWnd;//�������ĵ�

	if ( BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_LINE_IN_DRAW_DETECT)&&
		IsDlgButtonChecked(IDC_CHECK_RECT_IN_DRAW_DETECT) != BST_CHECKED )
	{
		player.m_drawDetectFlag = 3;///<����ʱ��״̬=3
	}	
	else if ( BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_RECT_IN_DRAW_DETECT)&&
		IsDlgButtonChecked(IDC_CHECK_LINE_IN_DRAW_DETECT) != BST_CHECKED )
	{
		player.m_drawDetectFlag = 4;///<����ʱ��״̬=4
	}

	player.pause();///<��Ƶ��ͣ
}


///@brief drawDetection���ԭʼ��Ƶ���ڵ���ֹ��ť��Ӧ����
/// 
///@param[in|out] NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void drawDetection::OnBnClickedBtnStopInDrawDetect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (player.m_filePath=="")
	{
		AfxMessageBox("����δ�����κ���Ƶ������");
		return;
	}
	if (tracker.m_IfContinue)
	{
		MessageBox("���ڶ���Ƶ���д�����ȴ�...");
		return;
	}
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT)->ShowWindow(TRUE);
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT)->ShowWindow(false);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT)->EnableWindow(false);
	player.m_drawDetectFlag = 0;///<״̬��������
	cvWaitKey(5);	            ///<��ʱ����
	///���vector����
	player.RectToShow.swap(vector<CRect>());
	player.pointsToShow.swap(vector<CPoint>());
	player.objectIDs.swap(vector<int>());
	//numOfObj = -1;//ע��֮������ʾ��⵽�����壬�޻ƿ�
	player.stop();///<��Ƶ��ֹ
	player.m_IfStartDetect = false;///<��Ƶ����־λ�÷�
}



void drawDetection::OnBnClickedBtnStartProcess()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_curVideoPath=player.m_filePath;
	if(m_curVideoPath=="")
		return;
	CString m_curVideoNameText;
	//m_curVideoNameText=video
	objtablename = draw_videoPro->m_tableParams.ObjectTableName;//m_curVideoNameText.Left(m_curVideoNameText.Find(".")) + "_ObjectTable";
	player.objtablename=objtablename;
	oriPlayer.objtablename=objtablename;
	if(!m_MysqlHandle->IfExistTable(objtablename,&m_ifExistProData))
	{
		AfxMessageBox("���ݿ��ѯ������");//debug��
		return;
	}
	if(m_ifExistProData)
	{///�������ݱ���������������
		MessageBox("����Ƶ��������");
		return ;
	}
	vector<CString> oriVideoName;
	if (player.m_filePath == m_curVideoPath)
	{
		player.m_drawDetectFlag = 0;
		oriPlayer.m_drawDetectFlag = 0;
		player.stopPlay();
		oriPlayer.stopPlay();
		GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT2)->EnableWindow(FALSE);
	}
	char *filename = m_curVideoPath.GetBuffer(m_curVideoPath.GetLength());///��ȡ����·��
	tracker.DoProcessing(filename,objtablename);///<��ʼ���ټ�⴦��

	GetDlgItem(IDC_PROGRESS_IN_DRAW_DETECT)->ShowWindow(true);
	GetDlgItem(IDC_BTN_STOP_PROCESS)->ShowWindow(true);
	GetDlgItem(IDC_CHECK_LINE_IN_DRAW_DETECT)->EnableWindow(false);
	GetDlgItem(IDC_CHECK_RECT_IN_DRAW_DETECT)->EnableWindow(false);
}





void drawDetection::OnBnClickedBtnStopProcess()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	tracker.StopProcessing();
	GetDlgItem(IDC_PROGRESS_IN_DRAW_DETECT)->ShowWindow(false);
	GetDlgItem(IDC_BTN_STOP_PROCESS)->ShowWindow(false);
	GetDlgItem(IDC_CHECK_LINE_IN_DRAW_DETECT)->EnableWindow(true);
	GetDlgItem(IDC_CHECK_RECT_IN_DRAW_DETECT)->EnableWindow(true);
}




void drawDetection::OnBnClickedCheckLineInDrawDetect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_MysqlHandle->IfExistTable(objtablename,&m_ifExistProData);
	if(!m_ifExistProData)
	{///�������ݱ���������������
		MessageBox("���ȶ���Ƶ������");
		GetDlgItem(IDC_CHECK_LINE_IN_DRAW_DETECT)->SendMessage(BM_SETCHECK, BST_UNCHECKED, NULL);  
		player.m_drawDetectFlag = 0;
		return ;
	}
	///���й�ѡ������״̬�����޸Ŀ�ʼ����־λ
	if ( BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_LINE_IN_DRAW_DETECT)&&
		IsDlgButtonChecked(IDC_CHECK_RECT_IN_DRAW_DETECT) != BST_CHECKED )
	{
		player.m_IfStartDetect  = false;
		player.m_drawDetectFlag = 1;
	}	
	else if ( BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_RECT_IN_DRAW_DETECT)&&
		IsDlgButtonChecked(IDC_CHECK_LINE_IN_DRAW_DETECT) != BST_CHECKED )
	{
		player.m_IfStartDetect  = false;
		player.m_drawDetectFlag = 2;
	}
	///�������vector����
	else /*if ( BST_CHECKED != IsDlgButtonChecked(IDC_CHECK_RECT_IN_DRAW_DETECT)&&
		IsDlgButtonChecked(IDC_CHECK_LINE_IN_DRAW_DETECT) != BST_CHECKED )*/
	{
		player.m_drawDetectFlag = 0;
		cvWaitKey(5);
		player.RectToShow.swap(vector<CRect>());
		player.pointsToShow.swap(vector<CPoint>());
		player.objectIDs.swap(vector<int>());
		numOfObj = -1;
		player.m_IfStartDetect  = false;
	}
}




void drawDetection::OnBnClickedCheckRectInDrawDetect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		if(!m_ifExistProData)
	{///�������ݱ���������������
		MessageBox("���ȶ���Ƶ������");
		player.m_drawDetectFlag = 0;
		GetDlgItem(IDC_CHECK_RECT_IN_DRAW_DETECT)->SendMessage(BM_SETCHECK, BST_UNCHECKED, NULL);  
		return ;
	}
	///���й�ѡ������״̬�����޸Ŀ�ʼ����־λ
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_RECT_IN_DRAW_DETECT)&&
		IsDlgButtonChecked(IDC_CHECK_LINE_IN_DRAW_DETECT) != BST_CHECKED)
	{
		player.m_IfStartDetect  = false;
		player.m_drawDetectFlag = 2;
	}	
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_LINE_IN_DRAW_DETECT)&&
		IsDlgButtonChecked(IDC_CHECK_RECT_IN_DRAW_DETECT) != BST_CHECKED)
	{
		player.m_IfStartDetect  = false;
		player.m_drawDetectFlag = 1;
	}
	
	///�������vector����
	else /*if ( BST_CHECKED != IsDlgButtonChecked(IDC_CHECK_RECT_IN_DRAW_DETECT)&&
		IsDlgButtonChecked(IDC_CHECK_LINE_IN_DRAW_DETECT) != BST_CHECKED )*/
	{
		player.m_drawDetectFlag = 0;
		cvWaitKey(5);
		player.RectToShow.swap(vector<CRect>());
		player.pointsToShow.swap(vector<CPoint>());
		player.objectIDs.swap(vector<int>());
		numOfObj = -1;
		player.m_IfStartDetect  = false;
	}
}






void drawDetection::OnBnClickedBtnClearInDrawDetect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (tracker.m_IfContinue)
	{
		MessageBox("���ڶ���Ƶ���д�����ȴ�...");
		return;
	}
	oriPlayer.stopPlay();///<�������Ƶֹͣ����
	oriPlayer.m_drawDetectFlag = 0;
	oriPlayer.m_IfStartDetect = false;
	player.m_drawDetectFlag = 0;
	player.m_IfStartDetect = false;
	player.m_playState = PLAY_STATE_PLAY;
	numOfObj = -1;
	cvWaitKey(5);
	///���vector����
	player.pointsToShow.swap(vector<CPoint>());
	player.RectToShow.swap(vector<CRect>());
	player.objectIDs.swap(vector<int>());
	oriPlayer.pointsToShow.swap(vector<CPoint>()); 
	oriPlayer.RectToShow.swap(vector<CRect>());

	mousePosInCVwmd.x=0;
	mousePosInCVwmd.x1=0;
	mousePosInCVwmd.y=0;
	mousePosInCVwmd.y1=0;
	///����ؼ������޸�
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT2)->ShowWindow(TRUE);
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT2)->ShowWindow(false);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT2)->EnableWindow(false);
	GetDlgItem(IDC_CHECK_LINE_IN_DRAW_DETECT)->SendMessage(BM_SETCHECK, BST_UNCHECKED, NULL);  
	GetDlgItem(IDC_CHECK_RECT_IN_DRAW_DETECT)->SendMessage(BM_SETCHECK, BST_UNCHECKED, NULL);  
}




void drawDetection::OnBnClickedBtnSearchInDrawDetect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_curVideoPath=player.m_filePath;
	if (m_curVideoPath == "")
		return;
	if (tracker.m_IfContinue)
	{
		MessageBox("���ڶ���Ƶ���д�����ȴ�...");
		return;
	}
	if ( BST_CHECKED != IsDlgButtonChecked(IDC_CHECK_LINE_IN_DRAW_DETECT) && IsDlgButtonChecked(IDC_CHECK_RECT_IN_DRAW_DETECT) != BST_CHECKED )
	{
		MessageBox("��ѡ��������");
		return;
	}
	m_MysqlHandle->IfExistTable(objtablename,&m_ifExistProData);
	if (!m_ifExistProData)
	{///�������ݱ���������������
		MessageBox("���ȶ���Ƶ���д���");
		return;
	}
	if (player.m_clickPosInCVWnd.x <0 || player.m_lBtnUpPosInCVWnd.x <0)
	{///�޼�������򷵻�
		MessageBox("�뻭����ⷶΧ");
		return;
	}
	numOfObj = m_MysqlHandle->GetTableDistinctNum(objtablename);///<��ȡ����Ƶ�˶���������

	if (numOfObj == -1)
	{
		MessageBox("ObjectTable����");
		return;
	}
	///��ʼ���ֻ������
	if (player.m_IfStartDetect && player.pointsToShow.size()!=0)
	{
		return;//˵���������û�иı�--------------2013.3.7 luying
	}
	player.m_IfStartDetect = false;
	player.objectIDs.swap(vector<int>());
	objDetectedInfos.swap(vector<objectInfo>());
	oriPlayer.RectToShow.swap(vector<CRect>());
	oriPlayer.pointsToShow.swap(vector<CPoint>());
	player.RectToShow.swap(vector<CRect>());
	player.pointsToShow.swap(vector<CPoint>());
	DetectResult();                 ///<��ȡ�����
	m_pageNum = 0;
	DisplayPageSumImg();			///<������ͼ����ʾ��⵽��Ŀ����Ϣ
	player.m_IfStartDetect = true;
	Draw_Detect_pScrollBar->SetScrollRange(0,(objDetectedInfos.size()-7>0)?objDetectedInfos.size()-7:0);
}


void drawDetection::DisplayPageSumImg()
{
	CvCapture *capture = cvCreateFileCapture(oriPlayer.m_filePath);
	if (!capture)
		return;

	int num = m_pageSum;
	if (objDetectedInfos.size() > m_pageNum+7)		//����ǰҳ��Ϊ���һҳ
		num = m_pageSum;									//��ʾ����ͼ
	else
		num = objDetectedInfos.size();			//Ϊ���һҳ����ʾʣ���ͼ

	IplImage* image = NULL;
	for (int i = 0; i < m_pageSum; i++)
	{	
		///��ʾͼƬ
		if(i < num)											
		{
			///ȡ����Ƶ�и�Ŀ����ʼ֡�ŵ���һ֡
			cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,objDetectedInfos.at(m_pageNum +i).firstFrameID);
			image = cvQueryFrame(capture);
			if(image == NULL)
				continue;
			///����һ֡�л�ROI������Ŀ��λ��
			CRect rect = objDetectedInfos.at(m_pageNum + i).C_roi;
			cvRectangle(image,cvPoint(rect.left,rect.top),cvPoint(rect.right,rect.bottom),CV_RGB(200,200,0),5,8,0);
		}
		else											///��Ϊ���һҳ������closeup.bmp���
			image = cvLoadImage("closeup.bmp",CV_LOAD_IMAGE_COLOR);

		///������ͼ����ʾ
		CRect rt;
		CDC* pDC = GetDC();
		HDC hDC = pDC->m_hDC;
		GetDlgItem(IDC_PIC_CTRL0_IN_DRAW_DETECT + i)->GetClientRect(rt);   
		CClientDC dc(GetDlgItem(IDC_PIC_CTRL0_IN_DRAW_DETECT + i));
		m_ShowResult.ShowPictureHolderBMP(image,hDC,rt,dc);	
		ReleaseDC(pDC);
	}
	cvReleaseCapture(&capture);
}

void drawDetection::DetectResult()
{
	///�õ����߻���������������Ϣ
	CPoint drewPoit1, drewPoit2;
	drewPoit1 = player.m_clickPosInCVWnd;
	drewPoit2 = player.m_lBtnUpPosInCVWnd;
	int flag = player.m_drawDetectFlag;
	player.m_drawDetectFlag = 0;

	vector <CPoint> centersOfObj;	///����װ��ĳһĿ���center����
	int objCount = 0;
	int count = 0;					///���������Ƶ�m_pageSum�ţ��͹���ʾ��ҳ������ͼ�ˣ�������ѭ��
	if (!objDetectedInfos.empty())
		///�����ǵ�һҳ��m_pageSum��ͼ������objCountΪ���ȡ��m_pageSum��Ŀ�꣬����������ͼ����ʾ
		objCount = objDetectedInfos.at(objDetectedInfos.size() - 1).objectID + 1;		

	switch (flag)
	{
	case 1:
	case 3:
		{
			double disP1P2 = sqrt(double((drewPoit1.x-drewPoit2.x)*(drewPoit1.x-drewPoit2.x) +
				(drewPoit1.y-drewPoit2.y)*(drewPoit1.y-drewPoit2.y)));///���������߶�p1p2����
			int rCloseCount = 0;
			for (; objCount<numOfObj; objCount++)
			{
				///�����潫��objCount��Ŀ��Ĺ켣�����centersOfObj��
				centersOfObj.clear();
				m_MysqlHandle->GetCenterFromObjectTable(objCount,objtablename,&centersOfObj);
				int numOfCenter = centersOfObj.size();
				rCloseCount = 0;//��¼�ھ����ڳ��ֵ�������
				for(int centerCount=0; centerCount<numOfCenter; centerCount++)
				{
					int centerX = centersOfObj[centerCount].x;
					int centerY = centersOfObj[centerCount].y;
					///�����жϵ�ǰĿ�����ĵ��Ƿ��� ��������Ӧ�ľ�����
					if (((centerX<=drewPoit1.x&&centerX>=drewPoit2.x)||(centerX<=drewPoit2.x&&centerX>=drewPoit1.x)) &&
						((centerY<=drewPoit1.y&&centerY>=drewPoit2.y)||(centerY<=drewPoit2.y&&centerY>=drewPoit1.y)))//�û������εķ�ʽ��ͬ
					{
						double disP1C = sqrt(double((drewPoit1.x-centerX)*(drewPoit1.x-centerX) +
							(drewPoit1.y-centerY)*(drewPoit1.y-centerY)));
						double disP2C = sqrt(double((drewPoit2.x-centerX)*(drewPoit2.x-centerX) +
							(drewPoit2.y-centerY)*(drewPoit2.y-centerY)));//�������ĵ����������֮��ľ���
						if ((disP2C+disP1C-disP1P2) < 5)//����жϷ�ʽ����
						{
							rCloseCount += 1;
							if (rCloseCount > 1)
							{
								///��������ܽӽ��߶�p1p2����Ϊ����
								///��Խ���ߵ�Ŀ����Ϣ������
								objectInfo tempInfo;		///��ʱ�����������洢Խ��Ŀ����ֵĵ�һ֡֡�š���һ֡�е�λ�ü����һ֡֡��
								m_MysqlHandle->GetObjectInfoFromDrawObjectTable(objCount,objtablename,&tempInfo);
								objDetectedInfos.push_back(tempInfo);
								//if (++count == m_pageSum)				///ÿ��ȡ��m_pageSum�ţ��򷵻�
								//{
								//	centersOfObj.swap(vector<CPoint>());
								//	player.m_drawDetectFlag = flag;
								//	return;
								//}
								break;
							}
						}
					}
				}
			}
		}
		break;
	case 2:			///������
	case 4:
		{
			for (; objCount<numOfObj; objCount++)
			{
				///�����潫��objCount��Ŀ��Ĺ켣�����centersOfObj��
				centersOfObj.swap(vector<CPoint>());
				m_MysqlHandle->GetCenterFromObjectTable(objCount,objtablename,&centersOfObj);
				int numOfCenter = centersOfObj.size();
				for(int centerCount=0; centerCount<numOfCenter; centerCount++)
				{
					int centerX = centersOfObj[centerCount].x;
					int centerY = centersOfObj[centerCount].y;
					if (((centerX<=drewPoit1.x&&centerX>=drewPoit2.x)||(centerX<=drewPoit2.x&&centerX>=drewPoit1.x)) &&
						((centerY<=drewPoit1.y&&centerY>=drewPoit2.y)||(centerY<=drewPoit2.y&&centerY>=drewPoit1.y)))
					{
						objectInfo tempInfo;					///��Խ���ߵ�Ŀ����Ϣ������
						m_MysqlHandle->GetObjectInfoFromDrawObjectTable(objCount,objtablename,&tempInfo);
						objDetectedInfos.push_back(tempInfo);
						//if (++count == m_pageSum)				///ÿ��ȡ��m_pageSum�ţ��򷵻�
						//{
						//	centersOfObj.clear();
						//	player.m_drawDetectFlag = flag;
						//	return;
						//}
						break;

					}
				}
			}
		}
		break;
	default:
		break;
	}
	centersOfObj.swap(vector<CPoint>());
	player.m_drawDetectFlag = flag;
}

void drawDetection::OnBnClickedBtnPlayInDrawDetect2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (tracker.m_IfContinue)
	{
		MessageBox("���ڶ���Ƶ���д�����ȴ�...");
		return;
	}
	if (player.m_IfStartDetect == false)
	{
		MessageBox("δ��ʼ���");
		return;
	}
	m_CSlider_oriplayerCtrl.SetRange(0,Video_FrameCount);///<��������ʼ��
	CString VideoTime;                                     ///<ʱ����ʾ׼��
	int VedioHour=oriPlayer.m_videoTimeInSecond/3600;
	int VedioMinute=oriPlayer.m_videoTimeInSecond/60-VedioHour*60;
	int VedioSecond=oriPlayer.m_videoTimeInSecond-VedioHour*3600-VedioMinute*60;
	VideoTime.Format(" 0::0::0 / %d::%d::%d ",VedioHour,VedioMinute,VedioSecond);
	GetDlgItem(IDC_STATIC_TIME_IN_DRAW_DETECT)->SetWindowText(VideoTime);///<��ʱ����ʾ���ؼ���


	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT2)->ShowWindow(false);
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT2)->EnableWindow(false);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT2)->ShowWindow(TRUE);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT2)->EnableWindow(TRUE);
	//oriPlayer.m_playState=PLAY_STATE_PLAY;
	oriPlayer.play();
}



void drawDetection::OnBnClickedBtnPauseInDrawDetect2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (tracker.m_IfContinue)
	{
		MessageBox("���ڶ���Ƶ���д�����ȴ�...");
		return;
	}
	if (player.m_IfStartDetect == false)
	{
		MessageBox("δ��ʼ���");
		return;
	}
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT2)->ShowWindow(TRUE);
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT2)->ShowWindow(false);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT2)->EnableWindow(false);
	oriPlayer.pause();
}




void drawDetection::OnBnClickedBtnStopInDrawDetect2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (tracker.m_IfContinue)
	{
		MessageBox("���ڶ���Ƶ���д�����ȴ�...");
		return;
	}
	if (player.m_IfStartDetect == false)
	{
		MessageBox("δ��ʼ���");
		return;
	}
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT2)->ShowWindow(TRUE);
	GetDlgItem(IDC_BTN_PLAY_IN_DRAW_DETECT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT2)->ShowWindow(false);
	GetDlgItem(IDC_BTN_PAUSE_IN_DRAW_DETECT2)->EnableWindow(false);
	oriPlayer.m_drawDetectFlag = 0;
	oriPlayer.stop();
}




void drawDetection::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int num = m_pageSum;
	//if (objDetectedInfos.size()/m_pageSum > m_pageNum)	   ///����ǰҳ��Ϊ���һҳ
	//num = m_pageSum;
	//else
	//	num = objDetectedInfos.size()%m_pageSum;		   ///Ϊ���һҳ����ʾʣ���ͼ
	CRect rec;
	for (int i = 0; i < num; i++)						   ///ͨ����֤�����������Ϊ����ͼƬ������������choiceΪѡ������
	{
		GetDlgItem(IDC_PIC_CTRL0_IN_DRAW_DETECT + i)->GetWindowRect(rec);
		ScreenToClient(rec);					
		if (rec.PtInRect(point))
		{
			///���Ҳ�Ĳ��Ŵ����в���ѡ�е�Ŀ��������Ƶ
			oriPlayer.m_drawDetectFlag = 0;
			objectInfo tempInfo = objDetectedInfos.at(m_pageNum + i);
			///�ڴ˲�����ƵƬ��
			oriPlayer.play();
			oriPlayer.m_currentFrameNO=oriPlayer.m_startFrameNO = tempInfo.firstFrameID;//201303013½���ģ���������б����ʱ������ұ߿���ʾ��������
			oriPlayer.m_endFrameNO = tempInfo.lastFrameID - 2;
			oriPlayer.m_playState = PLAY_STATE_PLAY_PIECE;
			oriPlayer.m_clickObjectID = tempInfo.objectID;
			oriPlayer.m_drawDetectFlag = 5;
			break;
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}



void drawDetection::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int TempPos = pScrollBar->GetScrollPos();
	switch(nSBCode)
	{
	case SB_THUMBPOSITION://�϶�����
		if(nPos<objDetectedInfos.size()-6)
		{
			pScrollBar->SetScrollPos(nPos);
			user_click_scrollbar=TRUE;
		}
		//pScrollBar->SetScrollPos(nPos);
		break;
	case SB_THUMBTRACK://�϶�����
		if(nPos<objDetectedInfos.size()-6)
		{

			pScrollBar->SetScrollPos(nPos);
			user_click_scrollbar=TRUE;
		}

		//pScrollBar->SetScrollPos(nPos);
		break;
	case SB_LINELEFT://����ϱߵļ�ͷ
		if(TempPos > 0)
		{
			TempPos--;
		}
		pScrollBar->SetScrollPos(TempPos);
		user_click_scrollbar=TRUE;
		break;
	case SB_LINERIGHT://����±ߵļ�ͷ
		if(TempPos<objDetectedInfos.size()-7)
		{
			TempPos++;
		}
		pScrollBar->SetScrollPos(TempPos);
		user_click_scrollbar=TRUE;
		break;
	} 
	//int i=pScrollBar->GetScrollPos();
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
