/**
*@file  vidPlayer.cpp
*@brief ��Ƶ������Ķ��塣
*
*���ļ���������Ƶ���������ع��ܡ�
*@data 2014-06-04
*/

#include "stdafx.h"
#include "vidPlayer.h"
#include <afx.h>


pointForCvMouse mousePosInCVwmd;

vidPlayer::vidPlayer()
{
	threadRunOrNot = FALSE;
	m_playState = PLAY_STATE_STOP;
	m_CurrentTimeInSecond=0;
	bEditIsChange = false;
}

vidPlayer::~vidPlayer()
{
}

///@brief vidPlayer��Ĳ��ų�ʼ����������ʼ����Ƶ����
/// 
///@param[in] ��Ƶ��ʾ���ھ������Ƶ��ʾ��������
///@pre    NULL
///@return BOOL
///@retval NULL
///@post   NULL
BOOL vidPlayer::playInitial(CWnd *pWnd, CString windowName)
{
	m_pWnd = pWnd;
	m_windowName = windowName;
	timeshow=FALSE;
	
	CvCapture *capture = cvCreateFileCapture(m_filePath);///<��ȡ��Ƶͷָ��
	if (capture == NULL)
	{///��ȡʧ���򷵻�
		return FALSE;
	}
	m_size.width = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);  ///<��ȡ��Ƶ֡���
	m_size.height = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);///<��ȡ��Ƶ֡�߶�
	m_fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);///<��ȡ��Ƶ֡��
	m_startFrameNO = m_currentFrameNO = 0;///<��ʼ����Ƶ��ʼ֡�ź͵�ǰ֡��
	m_endFrameNO = m_lastFrameNO = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);///<��ʼ����Ƶ����֡�ź���һ�β���֡��
	m_timeGap = 1000.0/m_fps;///<��ʼ����Ƶʱ����
	m_videoTimeInSecond = double(m_endFrameNO - m_startFrameNO)/m_fps;///<��ʼ����Ƶ�������
	cvReleaseCapture(&capture);///<�ͷ���Ƶͷָ��

	return TRUE;

}


///@brief vidPlayer��Ĳ����߳̿��ƺ���
/// 
///@param[in|out] NULL
///@pre    NULL
///@return UINT
///@retval NULL
///@post   NULL
UINT vidPlayer::playProcess()
{
	const char *path = (LPCTSTR)m_filePath;
	CvCapture *capture = cvCreateFileCapture(path);///<��ȡ��Ƶͷָ��
	if (!capture)
	{///��ȡʧ�ܣ������ʾ���
		AfxMessageBox("��Ҫ���ŵ��ļ����𻵻����Ѿ���ԭ·���Ƴ�������\n������ѡ���ļ���");
		return 0;
	}
	cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, m_currentFrameNO);///<������Ƶ��ǰ֡λ��
	//frameCopyForDraw = cvCreateImage(m_size,IPL_DEPTH_8U, 3);///<��ʼ����ʾͼ��֡
	m_curFrame = cvCreateImage(m_size,IPL_DEPTH_8U, 3);
	m_curFrameCopy = cvCreateImage(m_size,IPL_DEPTH_8U, 3);
	while (threadRunOrNot)
	{
//		int para = 5;
//		//if (m_windowName == "displayWindow1")//luying 10.29 Ϊ���������޷���ʱ��Ӧ������
//		{
//			cvSetMouseCallback(m_windowName, cvMouseHandler, &para);///<���������Ӧ
//		}
		//if (m_playState != PLAY_STATE_PAUSE)
		//{///����ͣ״̬�£������������Ӧ
		//	mousePosInCVwmd.clickInCVwnd = FALSE;
		//	m_gotCVlclick = FALSE;
		//}

		if(m_playState == PLAY_STATE_PLAY)///����
		{
			while((m_currentFrameNO < m_endFrameNO)&& (m_playState == PLAY_STATE_PLAY))
			{
				if (threadRunOrNot == FALSE)
					break;///<�߳�״̬ΪFALSEʱ������ѭ��
				
				if (m_currentFrameNO < m_startFrameNO)
				{///��ǰ֡С����ʼ֡����������ʼ֡
					cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, m_startFrameNO);
					m_currentFrameNO = m_startFrameNO;
					m_lastFrameNO = m_currentFrameNO;
				}
				if ( (abs(m_lastFrameNO-m_currentFrameNO)>=4) || bEditIsChange)
				{///�϶������������ǰһ֡�뵱ǰ֡�����������õ�ǰ֡
					cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, m_currentFrameNO);
					m_lastFrameNO=m_currentFrameNO;
					bEditIsChange = false;
				}
				m_curFrame = cvQueryFrame(capture);///<��ȡ��ǰ֡ͼ��

				
				if (!m_curFrame)
					continue;

				if(timeshow==TRUE)//��ʾʱ��
				{
					TimePosition.clear();
					Time.clear();
					ROI.clear();
					m_MysqlVideoParaSearchHandle->FindTimePositionFromNewTraceTable(m_currentFrameNO, &TimePosition, &Time, m_videoPro->m_tableParams.NewTraceTable);
					m_MysqlVideoParaSearchHandle->FindROIFromNewTraceTable(m_currentFrameNO, &ROI, m_videoPro->m_tableParams.NewTraceTable);

					CvFont font;
					cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1.0, 1.0, 0, 2, 1); 
					int i=0;
					
					while (i<Time.size())
					{
						CString str_TargetVideoTime;  //
						//d_AbsVideoTimeRatio = (player1.m_endFrameNO- player1.m_startFrameNO)* player1.m_videoTimeInSecond;
						m_origPara = m_MysqlVideoParaSearchHandle->FindOrigParaFromFGTraceTable(m_videoPro->m_tableParams.FGTraceTableName, ROI[i]);
						int TargetTimeInSecond = (double)Time[i]/(double)d_AbsVideoTimeRatio;
						int TargetVedioHour=TargetTimeInSecond/3600;
						int TargetVedioMinute=TargetTimeInSecond/60-TargetVedioHour*60;
						int TargetVedioSecond=TargetTimeInSecond-TargetVedioHour*3600-TargetVedioMinute*60;

						str_TargetVideoTime.Format("%d  %d:%d:%d",m_origPara,TargetVedioHour,TargetVedioMinute,TargetVedioSecond);
						
						cvPutText(m_curFrame,str_TargetVideoTime,TimePosition[i], &font, CV_RGB(255, 255, 255));//TimePosition[i]
						i++;
					}
				}
				disPlayImage.ShowPicture(m_windowName, m_curFrame);
               
				//playInDrawDetection();///<�ֻ�Ŀ����
				//m_currentFrameNO = m_lastFrameNO; //trun to 0;
				m_lastFrameNO = m_currentFrameNO;
				m_currentFrameNO ++;

				cvWaitKey(1);
				Sleep(m_timeGap);///<��ʱ����

				int para = 5;
				cvSetMouseCallback(m_windowName, cvMouseHandler, &para);

				m_clickPosInCVWnd.x = mousePosInCVwmd.x;
				m_clickPosInCVWnd.y = mousePosInCVwmd.y;
				m_lBtnUpPosInCVWnd.x = mousePosInCVwmd.x1;
				m_lBtnUpPosInCVWnd.y = mousePosInCVwmd.y1;
				m_gotCVlclick = mousePosInCVwmd.clickInCVwnd;//cv���ڵõ���������㴫��
			}
		}
		else if(m_playState == PLAY_STATE_PLAY_PIECE)///����Ƭ��
		{
			cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,m_startFrameNO);///������ʼ֡
			m_currentFrameNO = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES);
			m_lastFrameNO = m_currentFrameNO;
			m_playState = PLAY_STATE_PLAY;///<��Ƶ״̬תΪ����
		}
		else if(m_playState == PLAY_STATE_PAUSE)///��ͣ
		{
			if (threadRunOrNot == FALSE)
				break;///<�߳�״̬ΪFALSEʱ������ѭ��
			
			if (abs(m_lastFrameNO-m_currentFrameNO)>=4)
			{///�϶������������ǰһ֡�뵱ǰ֡�����������õ�ǰ֡
				cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, m_currentFrameNO);
				m_lastFrameNO=m_currentFrameNO;
				m_curFrame = cvQueryFrame(capture);	///<��ȡ��ǰ֡ͼ��
				if (!m_curFrame)
					continue;
				
				disPlayImage.ShowPicture(m_windowName, m_curFrame);///<��ʾ��ǰ֡ͼ��

				cvWaitKey(1);
				Sleep(m_timeGap);///<��ʱ����
			}

			int para = 5;
			cvSetMouseCallback(m_windowName, cvMouseHandler, &para);

			m_clickPosInCVWnd.x = mousePosInCVwmd.x;
			m_clickPosInCVWnd.y = mousePosInCVwmd.y;
			m_lBtnUpPosInCVWnd.x = mousePosInCVwmd.x1;
			m_lBtnUpPosInCVWnd.y = mousePosInCVwmd.y1;
			m_gotCVlclick = mousePosInCVwmd.clickInCVwnd;//cv���ڵõ���������㴫��

			//pauseInDrawDetection();///<�ֻ�Ŀ����
			cvWaitKey(1);          //20130313½���� ��ˢ��̫��
			Sleep(m_timeGap);///<��ʱ����
		}
		else if(m_playState == PLAY_STATE_FAST_FORWORD)///���
		{
			while((m_currentFrameNO < m_endFrameNO)&&(m_playState == PLAY_STATE_FAST_FORWORD))
			{
				if (threadRunOrNot == FALSE)
					break;///<�߳�״̬ΪFALSEʱ������ѭ��
				
				m_curFrame = cvQueryFrame(capture);///<��ȡ��ǰ֡ͼ��
				if (!m_curFrame)
					continue;
				
				disPlayImage.ShowPicture(m_windowName, m_curFrame);///<��ʾ��ǰ֡ͼ��
				m_currentFrameNO ++;///<��ǰ֡�ŵ���һ
				cvWaitKey(1);
				Sleep(m_timeGap/4);///<1/4��ʱ����
			}

		}
		else if (m_playState == PLAY_STATE_FAST_BACKWORD)///����
		{
			while((m_currentFrameNO >= m_startFrameNO)&&(m_playState == PLAY_STATE_FAST_BACKWORD))
			{
				if (threadRunOrNot == FALSE)
					break;///<�߳�״̬ΪFALSEʱ������ѭ��
				
				m_curFrame = cvQueryFrame(capture);///<��ȡ��ǰ֡ͼ��
				if (!m_curFrame)
					continue;
				
				disPlayImage.ShowPicture(m_windowName, m_curFrame);///<��ʾ��ǰ֡ͼ��
				m_currentFrameNO --;///<��ǰ֡�ŵݼ�һ
				cvWaitKey(1);
				Sleep(m_timeGap/4);///<1/4��ʱ����
			}

		}
		else if(m_playState == PLAY_STATE_FRAME_FAST_FORWORD)///��֡���
		{
			if(m_currentFrameNO < m_endFrameNO && m_currentFrameNO > m_startFrameNO)
			{
				if (threadRunOrNot == FALSE)
					break;///<�߳�״̬ΪFALSEʱ������ѭ��

				m_curFrame = cvQueryFrame(capture);	///<��ȡ��ǰ֡ͼ��
				if (!m_curFrame)
					continue;
				
				disPlayImage.ShowPicture(m_windowName, m_curFrame);///<��ʾ��ǰ֡ͼ��

				m_lastFrameNO=m_currentFrameNO;///<ǰһ֡�ŵ��ڵ�ǰ֡��
				m_currentFrameNO ++;///<��ǰ֡�ŵ���һ

				m_playState = PLAY_STATE_PAUSE;///<��Ƶ״̬תΪ��ͣ
			}
		}
		else if (m_playState == PLAY_STATE_FRAME_FAST_BACKWORD)///��֡����
		{
			if(m_currentFrameNO < m_endFrameNO && m_currentFrameNO > m_startFrameNO)
			{
				if (threadRunOrNot == FALSE)
					break;///<�߳�״̬ΪFALSEʱ������ѭ��
				
				m_currentFrameNO --;///<��ǰ֡�ŵݼ�һ
				cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, m_currentFrameNO);///<���õ�ǰ֡
				m_curFrame = cvQueryFrame(capture);	///<��ȡ��ǰ֡ͼ��
				if (!m_curFrame)
					continue;
				
				disPlayImage.ShowPicture(m_windowName, m_curFrame);///<��ʾ��ǰ֡ͼ��
				m_playState = PLAY_STATE_PAUSE;///<��Ƶ״̬תΪ��ͣ
			}

		}
		else if (m_playState == PLAY_STATE_STOP)///��ֹ����
		{
			if (threadRunOrNot == FALSE)
				break;///<�߳�״̬ΪFALSEʱ������ѭ��
			
			m_currentFrameNO = m_startFrameNO;///<�Ƚ�֡�����㣬Ȼ��ȴ����Ű�����Ӧ  //2013½���� ֡����λ0�ĳ�startframe,������Ƭ�����
			cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, m_currentFrameNO);///<���õ�ǰ֡Ϊ��Ƶ��֡
			m_curFrame = cvQueryFrame(capture);	///<��ȡ��ǰ֡ͼ��
			disPlayImage.ShowPicture(m_windowName, m_curFrame);///<��ʾ��ǰ֡ͼ��
			cvWaitKey(1);        //20130313½���� ��ˢ��̫��
			Sleep(m_timeGap/4);///<1/4��ʱ����
		}
		else if (m_playState == PLAY_STATE_SCREEN_SHOT)///��ͼ
		{
			///������ͣ״̬�����ȴ�����������Ӧ
			if (threadRunOrNot == FALSE)
				break;///<�߳�״̬ΪFALSEʱ������ѭ��
			
			m_playState = PLAY_STATE_PAUSE;///<��Ƶ״̬תΪ��ͣ
		}	
		if(m_currentFrameNO >= m_endFrameNO)
		{m_playState =PLAY_STATE_PAUSE;
		 m_currentFrameNO=m_startFrameNO;
		}
		     
	}
	cvReleaseCapture(&capture);///<�ͷ���Ƶͷָ��
	
	return 0;

}


///@brief vidPlayer�����Ƶ����,�߳̿�������
BOOL vidPlayer::play()
{
	if(threadRunOrNot == FALSE)
	{
		threadRunOrNot = TRUE;
		CRect rec;
		m_pWnd->GetClientRect(rec);

		disPlayImage.SetOpenCVWindow(m_pWnd, m_windowName, 
			rec.Height()*m_size.width/m_size.height, rec.Height());
		m_threadControl = ::AfxBeginThread(RunPlayProcess,this);
	}
	m_playState = PLAY_STATE_PLAY;

	return TRUE;
}

BOOL vidPlayer::playPiece()
{
	m_playState = PLAY_STATE_PLAY_PIECE;
	return TRUE;
}

BOOL vidPlayer::pause()
{
	m_playState = PLAY_STATE_PAUSE;
	return TRUE;
}

BOOL vidPlayer::fastForward()
{
	m_playState = PLAY_STATE_FAST_FORWORD;
	return TRUE;
}

BOOL vidPlayer::fastBackward()
{
	m_playState = PLAY_STATE_FAST_BACKWORD;
	return TRUE;
}

BOOL vidPlayer::fastForwardByFrame()
{
	m_playState = PLAY_STATE_FRAME_FAST_FORWORD;
	return TRUE;
}

BOOL vidPlayer::fastBackwardByFrame()
{
	m_playState = PLAY_STATE_FRAME_FAST_BACKWORD;
	return TRUE;
}
BOOL vidPlayer::stop()
{
	m_playState = PLAY_STATE_STOP;
	return TRUE;
}

IplImage *vidPlayer::screenShot()
{
	m_playState = PLAY_STATE_SCREEN_SHOT;
	return m_curFrame;
}

BOOL vidPlayer::stopPlay()
{

	if (threadRunOrNot == TRUE)
	{
		TRACE("threadRunOrNot = FALSE\n");
		threadRunOrNot = FALSE;
		WaitForSingleObject(m_threadControl->m_hThread,INFINITE);
		TRACE("before cvDestroyWindow\n");
		cvDestroyWindow(m_windowName);
	}
	return TRUE;
}

UINT RunPlayProcess(LPVOID controlNO)
{
	vidPlayer *OpenPlayHandle = (vidPlayer *)controlNO;

	OpenPlayHandle->playProcess();
	return 0;
}

BOOL vidPlayer::drawROI(vector <CRect> rect, CvScalar rectColor, int thickness)//���ڻ���Ŀ���
{
	int rectCount = rect.size();
	cvCopy(m_curFrame, m_curFrameCopy);
	CvPoint point1, point2;
	for (int i = 0; i<rectCount; i++)
	{
		point1.x = rect[i].left; point1.y = rect[i].top;
		point2.x = rect[i].left; point2.y = rect[i].bottom;
		cvLine(m_curFrameCopy, point1, point2, rectColor, thickness);//���

		point1.x = rect[i].left; point1.y = rect[i].top;
		point2.x = rect[i].right; point2.y = rect[i].top;
		cvLine(m_curFrameCopy, point1, point2, rectColor, thickness);//�ϱ�

		point1.x = rect[i].right; point1.y = rect[i].bottom;
		point2.x = rect[i].left; point2.y = rect[i].bottom;
		cvLine(m_curFrameCopy, point1, point2, rectColor, thickness);//�±�

		point1.x = rect[i].right; point1.y = rect[i].top;
		point2.x = rect[i].right; point2.y = rect[i].bottom;
		cvLine(m_curFrameCopy, point1, point2, rectColor, thickness);//�ұ�		
	}
	disPlayImage.ShowPicture(m_windowName, m_curFrameCopy);

	return TRUE;
}





void vidPlayer::ShowTime()
{
	CString CurVideoTime;
	int CurVedioHour=m_CurrentTimeInSecond/3600;
	int CurVedioMinute=m_CurrentTimeInSecond/60-CurVedioHour*60;
	int CurVedioSecond=m_CurrentTimeInSecond-CurVedioHour*3600-CurVedioMinute*60;

	int VedioHour=m_videoTimeInSecond/3600;
	int VedioMinute=m_videoTimeInSecond/60-VedioHour*60;
	int VedioSecond=m_videoTimeInSecond-VedioHour*3600-VedioMinute*60;

	CurVideoTime.Format(" %d::%d::%d / %d::%d::%d ",CurVedioHour,CurVedioMinute,CurVedioSecond,VedioHour,VedioMinute,VedioSecond);
	m_pShowTimeWnd->SetWindowText(CurVideoTime);
}

void cvMouseHandler(int eventType,int x,int y,int flags, void *param)
{
	switch (eventType)
	{
	case CV_EVENT_LBUTTONDOWN:///�������     
		{
			mousePosInCVwmd.x = x;
			mousePosInCVwmd.y = y;
			mousePosInCVwmd.x1 = x;
			mousePosInCVwmd.y1 = y;
			mousePosInCVwmd.clickInCVwnd = TRUE;
			mousePosInCVwmd.lBtnUp = FALSE;
		}
		break;
	case CV_EVENT_LBUTTONUP:///�������
		{
			if (mousePosInCVwmd.clickInCVwnd == TRUE)
			{
				mousePosInCVwmd.x1 = x;
				mousePosInCVwmd.y1 = y;
				mousePosInCVwmd.lBtnUp = TRUE;
				mousePosInCVwmd.clickInCVwnd = FALSE;
			}
		}
		break;
	case CV_EVENT_MOUSEMOVE:///����϶�
		{
			if (mousePosInCVwmd.clickInCVwnd == TRUE && mousePosInCVwmd.lBtnUp == FALSE)
			{
				mousePosInCVwmd.x1 = x;
				mousePosInCVwmd.y1 = y;
			}		
		}
		break;
	}
}

CString absOriNameTansf(CString nameIn)
{
	CString nameOut;
	int isAvi = nameIn.Find(".avi");
	if (isAvi != -1)
	{
		int isAviFusion = nameIn.Find("_fusion.avi");
		if (isAviFusion != -1 )
		{
			nameOut = nameIn.Left(isAviFusion);
		}
		else
		{
			nameOut = nameIn;
			nameOut.Append("_fusion.avi");
		}
	}
	return nameOut;
}
