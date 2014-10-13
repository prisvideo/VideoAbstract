// PictureAbsSUBDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "videotest2.h"
#include "PictureAbsSUBDlg.h"
#include "afxdialogex.h"


pointForCvMouse mousePosInPic;
BOOL ifClick = FALSE;
void cvMouseHandlerInPic(int eventType, int x, int y, int flags, void *param);
// PictureAbsSUBDlg �Ի���

IMPLEMENT_DYNAMIC(PictureAbsSUBDlg, CDialogEx)

PictureAbsSUBDlg::PictureAbsSUBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(PictureAbsSUBDlg::IDD, pParent)
{
	Tab2_MysqlVideoParaSearchHandle = new CDataMySql;
	m_videoPro = new CVideo;
}

PictureAbsSUBDlg::~PictureAbsSUBDlg()
{
	if(Tab2_MysqlVideoParaSearchHandle != NULL)
	{		delete Tab2_MysqlVideoParaSearchHandle;
	Tab2_MysqlVideoParaSearchHandle = NULL;
	}	
	if(m_videoPro != NULL)
	{
		delete m_videoPro;
		m_videoPro = NULL;
	}
}

void PictureAbsSUBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TAB2_ORI, oriPicture);
	DDX_Control(pDX, IDC_TAB2_ORI_SLIDER,Tab2_CSliderPlayer1Ctrl);
	DDX_Control(pDX, IDC_BTN_TAB2_ORI_PLAY, Btn_TAB2_PLAY);
	DDX_Control(pDX, IDC_BTN_TAB2_ORI_PAUSE, Btn_TAB2_PAUSE);
	DDX_Control(pDX, IDC_BTN_TAB2_ORI_STOP, Btn_TAB2_STOP);
	DDX_Control(pDX, IDC_BTN_TAB2_COMBINEPIC_UP, Btn_TAB2_UP);
	DDX_Control(pDX, IDC_BTN_TAB2_COMBINEPIC_down, Btn_TAB2_DOWN);
}


BEGIN_MESSAGE_MAP(PictureAbsSUBDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_TAB2_COMBINEPIC_UP, &PictureAbsSUBDlg::OnBnClickeddlg2up)
	ON_BN_CLICKED(IDC_BTN_TAB2_COMBINEPIC_down, &PictureAbsSUBDlg::OnBnClickeddlg2down)
//	ON_BN_CLICKED(IDC_BTN_TAB2_COMBINEPIC_GENERATE, &PictureAbsSUBDlg::OnBnClickeddlg2generate)
	ON_BN_CLICKED(IDC_BTN_TAB2_ORI_PLAY, &PictureAbsSUBDlg::OnBnClickedBtnTab2OriPlay)
	ON_BN_CLICKED(IDC_BTN_TAB2_ORI_PAUSE, &PictureAbsSUBDlg::OnBnClickedBtnTab2OriPause)
	ON_BN_CLICKED(IDC_BTN_TAB2_ORI_STOP, &PictureAbsSUBDlg::OnBnClickedBtnTab2OriStop)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


BOOL ifinitDisplay5 = FALSE;

// PictureAbsSUBDlg ��Ϣ�������


void PictureAbsSUBDlg::DisplaySumImg()
{
	DisplayFrame disPlayImage;//������Ƕ���Ŵ��ڵĶ���
	IplImage* image = NULL;
	CString nOldPara1, nOldPara2;
	for (int i = 0; i < m_pageSum; i++)
	{
		CString PicName;
		CString m_tmpFileName1, m_tmpFileName2;
		CString m_tmpFileName0 = playerori_TAB2.m_filePath;
		GetVideoNameFromAbsolutePath1(&m_tmpFileName0, &m_tmpFileName1);
		GetFileNameBeforeDot(&m_tmpFileName1, &m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
		PicName.Format(m_tmpFileName2 + "\\All%d", i + m_pagenum);
		image = cvLoadImage("../" + PicName + ".jpg", 1);
		///��ʾͼƬ
		if (image != NULL)
		{
			///ȡ����Ƶ�и�Ŀ����ʼ֡�ŵ���һ֡

			switch (i)
			{
			case 0:
				if (!ifinitDisplay5){
					CRect rect;
					rect.left = 25.0*UIBeautifier.rcDeskRect.Width() / 1214;
					rect.right = 25.0*UIBeautifier.rcDeskRect.Width() / 1214 + 506.0*UIBeautifier.rcDeskRect.Width() / 1214;
					rect.top = 100.0*UIBeautifier.rcDeskRect.Height() / 760;
					rect.bottom = 100.0*UIBeautifier.rcDeskRect.Height() / 760 + 380.0*UIBeautifier.rcDeskRect.Height() / 760;
					disPlayImage.SetOpenCVWindow(GetDlgItem(IDC_STATIC_TAB2_COMBINEPIC), "displayWindow0",
						rect.left, rect.top, rect.Width(), rect.Height());
					ifinitDisplay5 = true;
				}
				if (image != NULL) // Check for invalid input
				{
					disPlayImage.ShowPicture("displayWindow0", image);
					cvReleaseImage(&image);
				}
				break;
			default:
				break;
			}
		}

	}
}



void PictureAbsSUBDlg::OnBnClickeddlg2up()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_pagenum > 0)
	{
		m_pagenum = m_pagenum - 1;
		DisplaySumImg();
	}
}


void PictureAbsSUBDlg::OnBnClickeddlg2down()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	IplImage* image = NULL;
	CString PicName;
	CString m_tmpFileName1, m_tmpFileName2;
	CString m_tmpFileName0 = playerori_TAB2.m_filePath;
	GetVideoNameFromAbsolutePath1(&m_tmpFileName0, &m_tmpFileName1);
	GetFileNameBeforeDot(&m_tmpFileName1, &m_tmpFileName2);        ///<��ȡ�ļ���(������׺)
	PicName.Format(m_tmpFileName2 + "\\All%d", m_pagenum+1);
	image = cvLoadImage("../" + PicName + ".jpg", 1);
	if (image!=NULL)
	{
		m_pagenum = m_pagenum+1;
		DisplaySumImg();
	}
}


//void PictureAbsSUBDlg::OnBnClickeddlg2generate()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	m_pagenum = 0;
//	Generated = TRUE;
////	DetectResult();
//	DisplaySumImg();
//	//playerori_TAB2.playInitial(GetDlgItem(IDC_STATIC_TAB2_ORI), "ori_displayWindow");//�ó�ʼ����Ҫ���ļ�·��ȷ�Ϻ����
//	playerori_TAB2.play();
//}


BOOL PictureAbsSUBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_pageSum=1;
	m_pagenum = 0;
	UserClick = FALSE;
	Generated = FALSE;
	SetTimer(1, 300, NULL);
	playerori_TAB2.playInitial(GetDlgItem(IDC_STATIC_TAB2_ORI), "ori_displayWindow");
	Tab2_CSliderPlayer1Ctrl.SetRange(0, playerori_TAB2.m_endFrameNO);   ///<��ʼ������һ�Ļ�����
	Tab2_CSliderPlayer1Ctrl.SetPos(0);
	SetTimer(2, 100, NULL);
	SetTimer(3, 100, NULL);
	ifinitDisplay5=FALSE;
	//If_playpiece = FALSE;
	//��������
	UIBeautifier.LoadBackgroundPic(IDB_background);///<����λͼ����
	CWnd* pWnd = CWnd::GetDesktopWindow();
	pWnd->GetClientRect(UIBeautifier.rcDeskRect);///��ȡ�������
	BitmapBackGroundStrech = UIBeautifier.CBitmapResize(UIBeautifier.m_BitmapBackGround, UIBeautifier.rcDeskRect.Width(), UIBeautifier.rcDeskRect.Height());

	GetDlgItem(IDC_STATIC_TAB2_COMBINEPIC)->MoveWindow(25.0*UIBeautifier.rcDeskRect.Width() / 1214, 100.0*UIBeautifier.rcDeskRect.Height() / 760, 506.0*UIBeautifier.rcDeskRect.Width() / 1214, 380.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_STATIC_TAB2_ORI)->MoveWindow(581.0*UIBeautifier.rcDeskRect.Width() / 1214, 100.0*UIBeautifier.rcDeskRect.Height() / 760, 506.0*UIBeautifier.rcDeskRect.Width() / 1214, 380.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_STATIC_TAB2_ORI_TIME)->MoveWindow(691.0*UIBeautifier.rcDeskRect.Width() / 1214, 500.0*UIBeautifier.rcDeskRect.Height() / 760, 80.0*UIBeautifier.rcDeskRect.Width() / 1214, 30.0*UIBeautifier.rcDeskRect.Height() / 760);
	GetDlgItem(IDC_TAB2_ORI_SLIDER)->MoveWindow(771.0*UIBeautifier.rcDeskRect.Width() / 1214, 495.0*UIBeautifier.rcDeskRect.Height() / 760, 296.0*UIBeautifier.rcDeskRect.Width() / 1214, 20.0*UIBeautifier.rcDeskRect.Height() / 760);
	
	UIBeautifier.LoadButtonBitmaps(Btn_TAB2_PLAY, IDB_PLAY_U, IDB_PLAY_D,581.0/ 1214, 490.0 / 760, 611.0 / 1214, 520.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_TAB2_PAUSE,IDB_PAUSE_U, IDB_PAUSE_D, 621.0 / 1214, 490.0 / 760, 651.0 / 1214, 520.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_TAB2_STOP, IDB_STOP_U, IDB_STOP_D, 661.0 / 1214, 490.0 / 760, 691.0 / 1214, 520.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_TAB2_UP, IDB_UP_U, IDB_UP_D, 270.0 / 1214, 40.0 / 760, 330.0 / 1214,80.0 / 760);
	UIBeautifier.LoadButtonBitmaps(Btn_TAB2_DOWN, IDB_DOWN_U, IDB_DOWN_D, 270.0 / 1214, 500.0 / 760, 330.0 / 1214, 540.0 / 760);

	//��ʼ�����Ŵ���λ��
	playerori_TAB2.PlaywindowRect.left = 581.0*UIBeautifier.rcDeskRect.Width() / 1214;
	playerori_TAB2.PlaywindowRect.right = 581.0*UIBeautifier.rcDeskRect.Width() / 1214 + 506.0*UIBeautifier.rcDeskRect.Width() / 1214;
	playerori_TAB2.PlaywindowRect.top = 100.0*UIBeautifier.rcDeskRect.Height() / 760;
	playerori_TAB2.PlaywindowRect.bottom = 100.0*UIBeautifier.rcDeskRect.Height() / 760 + 380.0*UIBeautifier.rcDeskRect.Height() / 760;

	//��ʼ��ͼƬչʾ
	DisplayFrame initImage;
	IplImage* temp_image = cvLoadImage(".\\res\\ori-default.png", CV_LOAD_IMAGE_COLOR);
	initImage.SetOpenCVWindow(GetDlgItem(IDC_STATIC_TAB2_ORI), "ori_displayWindowtmp", playerori_TAB2.PlaywindowRect.left, playerori_TAB2.PlaywindowRect.top, playerori_TAB2.PlaywindowRect.Width(), playerori_TAB2.PlaywindowRect.Height());
	if (temp_image != NULL) // Check for invalid input
	{
		initImage.ShowPicture("ori_displayWindowtmp", temp_image);
		cvReleaseImage(&temp_image);
	}

	temp_image = cvLoadImage(".\\res\\pic-default.png", CV_LOAD_IMAGE_COLOR);
	CRect rect1;
	25.0*UIBeautifier.rcDeskRect.Width() / 1214, 100.0*UIBeautifier.rcDeskRect.Height() / 760, 506.0*UIBeautifier.rcDeskRect.Width() / 1214, 380.0*UIBeautifier.rcDeskRect.Height() / 760;
	rect1.left = 25.0*UIBeautifier.rcDeskRect.Width() / 1214;
	rect1.right = 25.0*UIBeautifier.rcDeskRect.Width() / 1214 + 506.0*UIBeautifier.rcDeskRect.Width() / 1214;
	rect1.top = 100.0*UIBeautifier.rcDeskRect.Height() / 760;
	rect1.bottom = 100.0*UIBeautifier.rcDeskRect.Height() / 760 + 380.0*UIBeautifier.rcDeskRect.Height() / 760;
	initImage.SetOpenCVWindow(GetDlgItem(IDC_STATIC_TAB2_COMBINEPIC), "displayWindow0tmp", rect1.left, rect1.top, rect1.Width(), rect1.Height());
	if (temp_image != NULL) // Check for invalid input
	{
		initImage.ShowPicture("displayWindow0tmp", temp_image);
		cvReleaseImage(&temp_image);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void PictureAbsSUBDlg::OnBnClickedBtnTab2OriPlay()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (playerori_TAB2.m_filePath != "")
	{

		///<ʱ����ʾ׼��
		CString VideoTime;
		int VedioHour = playerori_TAB2.m_videoTimeInSecond / 3600;
		int VedioMinute = playerori_TAB2.m_videoTimeInSecond / 60 - VedioHour * 60;
		int VedioSecond = playerori_TAB2.m_videoTimeInSecond - VedioHour * 3600 - VedioMinute * 60;

		VideoTime.Format(" 0:0:0 / %d:%d:%d ", VedioHour, VedioMinute, VedioSecond);
		GetDlgItem(IDC_STATIC_TAB2_ORI_TIME)->SetWindowText(VideoTime);///<��ʱ����ʾ���ؼ���

		playerori_TAB2.play();

	}
	else
	{
		AfxMessageBox("��ѡ���ļ�");
	}

}


void PictureAbsSUBDlg::OnBnClickedBtnTab2OriPause()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	playerori_TAB2.pause();
}


void PictureAbsSUBDlg::OnBnClickedBtnTab2OriStop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	playerori_TAB2.stop();
}


void PictureAbsSUBDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
	switch (nIDEvent)
	{
	case 1:
		if (Generated == TRUE)
		{
			DisplaySumImg();
		}
	case 2:///<���Ŵ���1�Ľ�������ʱ����ʾˢ��
	{
			   if (If_playpiece)
			   {
				   CSliderCtrl * SliderCtrl = ((CSliderCtrl*)GetDlgItem(IDC_TAB2_ORI_SLIDER));
				   SliderCtrl->SetPos(playerori_TAB2.m_currentFrameNO);
				   If_playpiece = FALSE;
			   }
			   else
			   {
				   CSliderCtrl * SliderCtrl = ((CSliderCtrl*)GetDlgItem(IDC_TAB2_ORI_SLIDER));
				   int CurrentPos = SliderCtrl->GetPos();                            ///<��ȡ��ǰ������λ��
				   int NewCurrentFrameNO = (double)CurrentPos*double(playerori_TAB2.m_endFrameNO - playerori_TAB2.m_startFrameNO)
					   / (double)SliderCtrl->GetRangeMax();     ///<���ݵ�ǰ������λ�ã����¼���֡��

				   if (playerori_TAB2.m_playState != PLAY_STATE_STOP && playerori_TAB2.m_playState != PLAY_STATE_FAST_FORWORD &&playerori_TAB2.m_playState != PLAY_STATE_PLAY_PIECE)///<�������������������Ż���ͣ״̬
				   {
					   if (abs(NewCurrentFrameNO - playerori_TAB2.m_currentFrameNO)>5)
					   {
						   playerori_TAB2.m_currentFrameNO = NewCurrentFrameNO;             ///<�����¼����֡�ţ����ò�����
					   }
				   }
				   SliderCtrl->SetPos(playerori_TAB2.m_currentFrameNO);                   ///<�����¼����֡�ţ����û�����
				   CWnd *pWndTimeDis = GetDlgItem(IDC_STATIC_TAB2_ORI_TIME);
				   if (playerori_TAB2.m_playState != PLAY_STATE_STOP)                     ///<��ֹͣ״̬�£��÷�ʽһ��ʾʱ��
				   {
					   ShowTime(playerori_TAB2.m_currentFrameNO, playerori_TAB2.m_endFrameNO - playerori_TAB2.m_startFrameNO,
						   playerori_TAB2.m_videoTimeInSecond, pWndTimeDis, 1);
				   }
				   else                                                            ///<ֹͣ״̬�£��÷�ʽ����ʾʱ��
				   {
					   SliderCtrl->SetPos(0);
					   ShowTime(playerori_TAB2.m_currentFrameNO, playerori_TAB2.m_endFrameNO - playerori_TAB2.m_startFrameNO,
						   playerori_TAB2.m_videoTimeInSecond, pWndTimeDis, 0);
				   }
			   }

	}
	case 3://���ǰ���ϳ�ͼ����ԭ��Ƶ
	{
				CString m_windowName1 = "displayWindow0"; //��ǰ���̿��Ƶ�CV������
					
				CPoint m_clickPosInCVWnd;///<��¼��������ĵ�
				CPoint m_lBtnUpPosInCVWnd;///<��¼�������ĵ�
				int para=5;
				cvSetMouseCallback(m_windowName1, cvMouseHandlerInPic, &para);

				m_clickPosInCVWnd.x = mousePosInPic.x;
				m_clickPosInCVWnd.y = mousePosInPic.y;
				m_lBtnUpPosInCVWnd.x = mousePosInPic.x1;
				m_lBtnUpPosInCVWnd.y = mousePosInPic.y1;
				//m_gotCVlclick = mousePosInPic.clickInCVwnd;//cv���ڵõ���������㴫��

				if (mousePosInPic.clickInCVwnd)
				{
				
					m_clickedObjRecPosInVec = -1;
					double clickPosXInImg = double(m_lBtnUpPosInCVWnd.x);
					double clickPosYInImg = double(m_lBtnUpPosInCVWnd.y);///<ע���ʱ�ĵ��λ���Ѿ���ԭʼ֡�ߴ������
					m_distanceToRecCenter = 1000000;

					m_objectOrigTraceTableVector.clear();
					///<�����ݿ��ж�ȡROI��Ϣ
					if (!Tab2_MysqlVideoParaSearchHandle->FindROIFromCombineSegsTable(&m_objectOrigTraceTableVector, m_videoPro->m_tableParams.CombineSegsTableName))//////"00015_h_NewTraceTable"
					{
						AfxMessageBox("���ݿ����");
						return;
					}

					for (int i = 0; i < m_objectOrigTraceTableVector.size(); i++)///<��������ROIĿ���
					{
							if (clickPosXInImg < m_objectOrigTraceTableVector[i].nX + m_objectOrigTraceTableVector[i].nWidth && clickPosXInImg > m_objectOrigTraceTableVector[i].nX///<�жϵ���Ƿ��ڵ�ǰ����
								&& clickPosYInImg < m_objectOrigTraceTableVector[i].nY + m_objectOrigTraceTableVector[i].nHeight && clickPosYInImg > m_objectOrigTraceTableVector[i].nY&&m_objectOrigTraceTableVector[i].PicID == m_pagenum)
							{
								int tempDistance = (clickPosXInImg - (m_objectOrigTraceTableVector[i].nX + m_objectOrigTraceTableVector[i].nWidth / 2))*
									(clickPosXInImg - (m_objectOrigTraceTableVector[i].nX + m_objectOrigTraceTableVector[i].nWidth / 2)) +
									(clickPosYInImg - (m_objectOrigTraceTableVector[i].nY + m_objectOrigTraceTableVector[i].nHeight / 2))*
									(clickPosYInImg - (m_objectOrigTraceTableVector[i].nY + m_objectOrigTraceTableVector[i].nHeight / 2));///<������λ���뵱ǰROI���ĵľ���

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
					m_theObjRecClicked.x = m_objectOrigTraceTableVector[m_clickedObjRecPosInVec].nX;
					m_theObjRecClicked.y = m_objectOrigTraceTableVector[m_clickedObjRecPosInVec].nY;
					m_theObjRecClicked.width = m_objectOrigTraceTableVector[m_clickedObjRecPosInVec].nWidth;
					m_theObjRecClicked.height = m_objectOrigTraceTableVector[m_clickedObjRecPosInVec].nHeight;
					int m_theorigFrame = 0;
					if (m_videoPro != NULL)
					{
						int m_origPara = Tab2_MysqlVideoParaSearchHandle->FindOrigParaFromFGTraceTable(m_videoPro->m_tableParams.FGTraceTableName, m_theObjRecClicked);
						m_theorigFrame = Tab2_MysqlVideoParaSearchHandle->FindOrigFrameFromVideoFGTable(m_videoPro->m_tableParams.VideoFGTableName, m_origPara);//m_videoPro->m_tableParams.NewTraceTable

						//m_theorigFrame = Tab2_MysqlVideoParaSearchHandle->FindOrigFrameFromNewTraceTable(m_videoPro->m_tableParams.NewTraceTable,m_theObjRecClicked);//m_videoPro->m_tableParams.NewTraceTable
					}

					if (m_theorigFrame == -1)
					{
						MessageBox("���ݿ�����");
						mousePosInPic.clickInCVwnd = FALSE;
						return;
					};

					playerori_TAB2.m_currentFrameNO = m_theorigFrame;                                 ///<��ʼ��ԭʼ��Ƶ������

					If_playpiece = TRUE;
					mousePosInPic.clickInCVwnd=FALSE;                                       ///<����ȶ���ϣ����õ������־λ�÷�
					ifClick = FALSE;
				}
	}
	default:
		break;
	}
}

void PictureAbsSUBDlg::ShowTime(int m_currentFrameNO, int totalFrameCount, int videoTimeInSecond, CWnd *m_pShowTimeWnd, int flag)
{
	CString CurVideoTime;
	if (flag == 1)
	{
		int CurrentTimeInSecond = (double)m_currentFrameNO / double(totalFrameCount)*videoTimeInSecond;
		int CurVedioHour = CurrentTimeInSecond / 3600;
		int CurVedioMinute = CurrentTimeInSecond / 60 - CurVedioHour * 60;
		int CurVedioSecond = CurrentTimeInSecond - CurVedioHour * 3600 - CurVedioMinute * 60;

		int VedioHour = videoTimeInSecond / 3600;
		int VedioMinute = videoTimeInSecond / 60 - VedioHour * 60;
		int VedioSecond = videoTimeInSecond - VedioHour * 3600 - VedioMinute * 60;

		CurVideoTime.Format(" %d:%d:%d / %d:%d:%d ", CurVedioHour, CurVedioMinute, CurVedioSecond, VedioHour, VedioMinute, VedioSecond);
		m_pShowTimeWnd->SetWindowText(CurVideoTime);
	}
	else if (flag == 0)
	{
		CurVideoTime.Format(" %d:%d:%d / %d:%d:%d ", 0, 0, 0, 0, 0, 0);
		m_pShowTimeWnd->SetWindowText(CurVideoTime);
	}

}


void PictureAbsSUBDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
	cvDestroyWindow( "ori_displayWindow" );
	cvDestroyWindow( "displayWindow0" );
	playerori_TAB2.threadRunOrNot=FALSE;
}


void PictureAbsSUBDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	return;
	//CDialogEx::OnCancel();
	//cvDestroyWindow( "ori_displayWindow" );
	//cvDestroyWindow( "displayWindow0" );
	//playerori_TAB2.threadRunOrNot=FALSE;
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

//void PictureAbsSUBDlg::OnPaint()
//{
//	if (IsIconic())
//	{
//		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
//
//		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
//
//		// ʹͼ���ڹ����������о���
//		int cxIcon = GetSystemMetrics(SM_CXICON);
//		int cyIcon = GetSystemMetrics(SM_CYICON);
//		CRect rect;
//		GetClientRect(&rect);
//		int x = (rect.Width() - cxIcon + 1) / 2;
//		int y = (rect.Height() - cyIcon + 1) / 2;
//
//		// ����ͼ��
//		dc.DrawIcon(x, y, m_hIcon);
//	}
//	else
//	{
//		//this->MoveWindow(UIBeautifier.rcDeskRect.left, UIBeautifier.rcDeskRect.top, UIBeautifier.rcDeskRect.Width(), UIBeautifier.rcDeskRect.Height(), TRUE); ///<��ѡ���λ
//		CDialogEx::OnPaint();
//	}
//}
