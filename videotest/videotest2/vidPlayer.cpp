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
	m_MysqlObjHandle = new CDataMySql;
}

vidPlayer::~vidPlayer()
{
	delete m_MysqlObjHandle;
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

				playInDrawDetection();///<�ֻ�Ŀ����

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

			pauseInDrawDetection();///<�ֻ�Ŀ����
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
	if (threadRunOrNot == FALSE)
	{
		threadRunOrNot = TRUE;
		if (PlaywindowRect.Height()*m_size.width / m_size.height <= PlaywindowRect.Width())
		{
			int nTar = PlaywindowRect.Width() - PlaywindowRect.Height()*m_size.width / m_size.height;
			disPlayImage.SetOpenCVWindow(m_pWnd, m_windowName, PlaywindowRect.left + nTar / 2, PlaywindowRect.top,
				PlaywindowRect.Height()*m_size.width / m_size.height, PlaywindowRect.Height());
		}
		else
		{
			int nTar = PlaywindowRect.Height() - PlaywindowRect.Width()*m_size.height / m_size.width;
			disPlayImage.SetOpenCVWindow(m_pWnd, m_windowName, PlaywindowRect.left, PlaywindowRect.top + nTar / 2,
				PlaywindowRect.Width(), PlaywindowRect.Width()*m_size.height / m_size.width);
		}

		m_threadControl = ::AfxBeginThread(RunPlayProcess, this);
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

//BOOL vidPlayer::drawROI(vector <CRect> rect, CvScalar rectColor, int thickness)//���ڻ���Ŀ���
//{
//	int rectCount = rect.size();
//	cvCopy(m_curFrame, m_curFrameCopy);
//	CvPoint point1, point2;
//	for (int i = 0; i<rectCount; i++)
//	{
//		point1.x = rect[i].left; point1.y = rect[i].top;
//		point2.x = rect[i].left; point2.y = rect[i].bottom;
//		cvLine(m_curFrameCopy, point1, point2, rectColor, thickness);//���
//
//		point1.x = rect[i].left; point1.y = rect[i].top;
//		point2.x = rect[i].right; point2.y = rect[i].top;
//		cvLine(m_curFrameCopy, point1, point2, rectColor, thickness);//�ϱ�
//
//		point1.x = rect[i].right; point1.y = rect[i].bottom;
//		point2.x = rect[i].left; point2.y = rect[i].bottom;
//		cvLine(m_curFrameCopy, point1, point2, rectColor, thickness);//�±�
//
//		point1.x = rect[i].right; point1.y = rect[i].top;
//		point2.x = rect[i].right; point2.y = rect[i].bottom;
//		cvLine(m_curFrameCopy, point1, point2, rectColor, thickness);//�ұ�		
//	}
//	disPlayImage.ShowPicture(m_windowName, m_curFrameCopy);
//
//	return TRUE;
//}





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
			mousePosInCVwmd.canDraw = 111;
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


inline BOOL vidPlayer::playInDrawDetection()
{
	CvPoint point1, point2;
	CRect rect;
	//cvCopy(m_curFrame, frameCopyForDraw);///<���Ƶ�ǰͼ��֡
	frameCopyForDraw=m_curFrame; //ֹͣ�����²��ű����ĳ�=������
	switch(m_drawDetectFlag)
	{
	case 0:///δ����״̬
		break;
	case 1:///����״̬
	case 2:///����״̬
		if (m_IfStartDetect == true)///��ʼ���
		{
			UpdatePlayData(m_drawDetectFlag);///<vector��ʾ���ݸ���
			for (int i = 0; i<RectToShow.size() ; i++)
			{///�����˶�Ŀ��Rect���ϲ����ƿ�
				rect = RectToShow.at(i);
				point1.x = rect.left;  point1.y = rect.top;
				point2.x = rect.right; point2.y = rect.bottom;
				cvRectangle(frameCopyForDraw, point1, point2, cvScalar(0,200,200), 2);
			}
		}
		else if (mousePosInCVwmd.canDraw == 111)
		{///δ��ʼ������������ʱ����¼��껭��λ��
			pointsToShow.swap(vector<CPoint>());
			m_clickPosInCVWnd.x = mousePosInCVwmd.x;
			m_clickPosInCVWnd.y = mousePosInCVwmd.y;
			pointsToShow.push_back(m_clickPosInCVWnd);
			m_lBtnUpPosInCVWnd.x = mousePosInCVwmd.x1;
			m_lBtnUpPosInCVWnd.y = mousePosInCVwmd.y1;
			pointsToShow.push_back(m_lBtnUpPosInCVWnd);
		}
		break;
	case 5:///�ֻ�������Ƶ����״̬
		if (m_clickObjectID != -1)
		{
			int m_ObjID = m_clickObjectID;///<��¼�����λ�õ��˶�Ŀ������ID
			m_clickObjectID = -1;
			pointsToShow.swap(vector<CPoint>());
			RectToShow.swap(vector<CRect>());
			pointsToShow.push_back(CPoint(-1,-1));
			pointsToShow.push_back(CPoint(-1,-1));
			m_MysqlObjHandle->GetSingleTraceFromObjectTable(m_ObjID,objtablename,&RectToShow,&pointsToShow);///<��ȡĳһ�˶�Ŀ�������Rect���Ϻ͹켣�㼯�ϣ��ֱ����RectToShow��pointToShow
		}
		if(m_currentFrameNO-m_startFrameNO< RectToShow.size() )///��ȡָ������Rect��Ϣ(�ұߴ���Rect��Ϣ��һ�λ�ȡ�ģ�����ֱ����ʾ)
		{///��ȡ��Ӧ֡��������Rect�����ƿ�
			rect = RectToShow.at(m_currentFrameNO-m_startFrameNO);
			point1.x = rect.left;   point1.y = rect.top;
			point2.x = rect.right;  point2.y = rect.bottom;
			cvRectangle(frameCopyForDraw, point1, point2, cvScalar(0,200,200), 2);	
		}
		break;
	}
	drawDetection(pointsToShow, frameCopyForDraw, m_drawDetectFlag);///<ͼ��֡����/��/�켣
	disPlayImage.ShowPicture(m_windowName, frameCopyForDraw);///<��ʾͼ��֡

	return TRUE;
}


inline BOOL vidPlayer::pauseInDrawDetection()
{
	CvPoint point1, point2;
	CRect rect;
	frameCopyForDraw = m_curFrame;///<���Ƶ�ǰͼ��֡
	switch(m_drawDetectFlag)
	{
	case 3:///����
	case 4:///����
		if (m_IfStartDetect)///��ʼ���
		{
			for (int i = 0; i<RectToShow.size() ; i++)
			{///�����˶�Ŀ��Rect���ϲ����ƿ�
				rect = RectToShow.at(i);
				point1.x = rect.left;   point1.y = rect.top;
				point2.x = rect.right;  point2.y = rect.bottom;
				cvRectangle(frameCopyForDraw, point1, point2, cvScalar(0,200,200), 2);
			}
			if (m_gotCVlclick)
			{
				UpdatePauseData();///<�����������ʱ��vector��ʾ���ݸ���
			}
			drawDetection(pointsToShow, frameCopyForDraw, m_drawDetectFlag);///<ͼ��֡����ɫ�켣
		}
		break;
	case 5:///�ֻ�������Ƶ��ͣ״̬
		if (m_clickObjectID != -1)
		{
			int m_ObjID = m_clickObjectID;///<��¼�����λ�õ��˶�Ŀ������ID
			m_clickObjectID = -1;
			pointsToShow.swap(vector<CPoint>());
			RectToShow.swap(vector<CRect>());
			pointsToShow.push_back(CPoint(-1,-1));
			pointsToShow.push_back(CPoint(-1,-1));
			m_MysqlObjHandle->GetSingleTraceFromObjectTable(m_ObjID,objtablename,&RectToShow,&pointsToShow);///<��ȡĳһ�˶�Ŀ�������Rect���Ϻ͹켣�㼯�ϣ��ֱ����RectToShow��pointToShow
		}
		if ((m_currentFrameNO - m_startFrameNO)< RectToShow.size())///��ȡָ������Rect��Ϣ(�ұߴ���Rect��Ϣ��һ�λ�ȡ�ģ�����ֱ����ʾ)
		{///��ȡ��Ӧ֡��������Rect�����ƿ�
			rect = RectToShow.at(m_currentFrameNO - m_startFrameNO);
			point1.x = rect.left;   point1.y = rect.top;
			point2.x = rect.right;  point2.y = rect.bottom;
			cvRectangle(frameCopyForDraw, point1, point2, cvScalar(0,200,200), 2);
		}
		drawDetection(pointsToShow, frameCopyForDraw, m_drawDetectFlag);///<ͼ��֡����ɫ�켣
		break;
	}
	disPlayImage.ShowPicture(m_windowName, frameCopyForDraw);///<��ʾͼ��֡

	return TRUE;
}

BOOL vidPlayer::drawROI(vector <CvRect> rect, CvScalar rectColor, int thickness)
{
	int rectCount = rect.size();         ///<��ȡ��Ҫ���Ƶľ�������
	cvCopy(m_curFrame, frameCopyForDraw);///<���Ƶ�ǰͼ��֡
	CvPoint point1, point2;
	for (int i = 0; i<rectCount; i++)
	{///�������μ��ϲ����ƾ��ο�
		//point1.x = rect.at(i).left; point1.y = rect.at(i).top;
		//point2.x = rect.at(i).right; point2.y = rect.at(i).bottom;
		point1.x= rect.at(i).x;point1.y= rect.at(i).y;
		point2.x= rect.at(i).x+rect.at(i).width;point2.y= rect.at(i).y+rect.at(i).height;
		cvRectangle(frameCopyForDraw, point1, point2, rectColor, thickness);
	}
	disPlayImage.ShowPicture(m_windowName, frameCopyForDraw);///<��ʾ�����ͼƬ

	return TRUE;
}


BOOL vidPlayer::drawDetection(vector <CPoint> inputPoints, IplImage *img, int flag)
{
	CvPoint point1, point2;
	if (inputPoints.size() < 2)
		return FALSE;
	point1.x = inputPoints.at(0).x;
	point1.y = inputPoints.at(0).y;
	point2.x = inputPoints.at(1).x;
	point2.y = inputPoints.at(1).y;
	CvScalar color = CV_RGB(255, 0, 0);
	int thickness = 2;
	switch (flag)
	{
	case 1:
		cvLine(img, point1, point2, color, thickness);///<������
		break;
	case 2:
		cvRectangle(img, point1, point2, color, thickness);///<�����
		break;
	case 3:
		{
			cvLine(img, point1, point2, color, thickness);///<������
			int vecSize = inputPoints.size();
			if (vecSize<=2)
				break;
			color = CV_RGB(0, 255, 255);
			for (int drawCenterFlag=2; drawCenterFlag<vecSize-1; drawCenterFlag++)
			{///�����㼯�ϣ�����ɫ�켣
				if(inputPoints.at(drawCenterFlag+1).x == -1 &&
					inputPoints.at(drawCenterFlag+1).y == -1)
				{
					drawCenterFlag += 2;
				}
				point1.x = inputPoints.at(drawCenterFlag).x;
				point1.y = inputPoints.at(drawCenterFlag).y;
				point2.x = inputPoints.at(drawCenterFlag+1).x;
				point2.y = inputPoints.at(drawCenterFlag+1).y;
				cvLine(img, point1, point2, color, thickness);
			}
		}
		break;
	case 4:
		{
			cvRectangle(img, point1, point2, color, thickness);///<������
			int vecSize = inputPoints.size();
			if (vecSize<=2)
				break;
			color = CV_RGB(0, 255, 255);
			for (int drawCenterFlag=2; drawCenterFlag<vecSize-1; drawCenterFlag++)
			{///�����㼯�ϣ�����ɫ�켣
				if(inputPoints.at(drawCenterFlag+1).x == -1 &&
					inputPoints.at(drawCenterFlag+1).y == -1)
				{
					drawCenterFlag += 2;
				}
				point1.x = inputPoints.at(drawCenterFlag).x;
				point1.y = inputPoints.at(drawCenterFlag).y;
				point2.x = inputPoints.at(drawCenterFlag+1).x;
				point2.y = inputPoints.at(drawCenterFlag+1).y;
				cvLine(img, point1, point2, color, thickness);
			}
		}
		break;
	case 5:
		{
			int vecSize = inputPoints.size();
			if (vecSize<=2)
				break;
			color = CV_RGB(0, 255, 255);
			for (int drawCenterFlag=2; drawCenterFlag<vecSize-1; drawCenterFlag++)
			{///�����㼯�ϣ�����ɫ�켣
				if(inputPoints.at(drawCenterFlag+1).x == -1 &&
					inputPoints.at(drawCenterFlag+1).y == -1)
				{
					drawCenterFlag += 2;
				}
				point1.x = inputPoints.at(drawCenterFlag).x;
				point1.y = inputPoints.at(drawCenterFlag).y;
				point2.x = inputPoints.at(drawCenterFlag+1).x;
				point2.y = inputPoints.at(drawCenterFlag+1).y;
				cvLine(img, point1, point2, color, thickness);
			}
		}
		break;
	default:
		break;
	}
	return TRUE;
}


inline void vidPlayer::UpdatePlayData(int flag)
{
	if (pointsToShow.size()<2)
		return;
	CPoint drewPoit1, drewPoit2;
	drewPoit1 = pointsToShow[0];
	drewPoit2 = pointsToShow[1];
	RectToShow.swap(vector<CRect>());   ///<����˶�Ŀ��Rect����
	pointsToShow.swap(vector<CPoint>());///<�˶�Ŀ��켣�㼯��
	pointsToShow.push_back(drewPoit1);  ///<�����ֻ�������������1
	pointsToShow.push_back(drewPoit2);  ///<�����ֻ�������������2
	TempRect.swap(vector<CRect>());     ///<�����ʱRect����
	TempObjectID.swap(vector<int>());   ///<�����ʱ�켣�㼯��

	///���ݱ��������ȡĳһ֡���¶�Ӧ���˶�Ŀ����Ϣ
	m_MysqlObjHandle->GetRectFromObjectTable(m_currentFrameNO,objtablename,&TempRect,&TempObjectID);

	int rCloseCount = 0;
	double disP1P2 = sqrt(double((drewPoit1.x-drewPoit2.x)*(drewPoit1.x-drewPoit2.x) +
		(drewPoit1.y-drewPoit2.y)*(drewPoit1.y-drewPoit2.y)));///���������߶�p1p2����

	///�����³��ֵ�����
	for(int i=0; i<TempRect.size(); i+=2)
	{
		///��ȡ��ʱRect���ĵ�����
		int centerX = TempRect.at(i).left;
		int centerY = TempRect.at(i).top;
		///�жϵ�ǰĿ�����ĵ��Ƿ��� ����/���� ����Ӧ�ľ�����
		if (((centerX<=drewPoit1.x&&centerX>=drewPoit2.x)||(centerX<=drewPoit2.x&&centerX>=drewPoit1.x)) &&
			((centerY<=drewPoit1.y&&centerY>=drewPoit2.y)||(centerY<=drewPoit2.y&&centerY>=drewPoit1.y)))
		{
			if (flag == 2)
			{///------------����-----------------
				RectToShow.push_back(TempRect.at(i+1));///��¼�˶�Ŀ��Rect��Ϣ
				///���TempObjectID.at(i/2)��objectIDs��û���ֹ��������˶�Ŀ��ID¼��objectIDs��
				if (objectIDs.size()>0)
				{
					vector<int>::iterator it = find(objectIDs.begin(),objectIDs.end(),TempObjectID.at(i/2));
					if(it == objectIDs.end())
						objectIDs.push_back(TempObjectID.at(i/2));
				}
				else
				{
					objectIDs.push_back(TempObjectID.at(i/2));
				}
			}
			else
			{///------------����------------------
				double disP1C = sqrt(double((drewPoit1.x-centerX)*(drewPoit1.x-centerX) +
					(drewPoit1.y-centerY)*(drewPoit1.y-centerY)));
				double disP2C = sqrt(double((drewPoit2.x-centerX)*(drewPoit2.x-centerX) +
					(drewPoit2.y-centerY)*(drewPoit2.y-centerY)));
				if ((disP2C+disP1C-disP1P2) < 5)
				{
					rCloseCount += 1;
					if (rCloseCount > 1)
					{
						///��������ܽӽ��߶�p1p2����Ϊ����
						RectToShow.push_back(TempRect.at(i+1));
						///���TempObjectID.at(i/2)��objectIDs��û���ֹ��������˶�Ŀ��ID¼��objectIDs��
						if (objectIDs.size()>0)
						{
							vector<int>::iterator it = find(objectIDs.begin(),objectIDs.end(),TempObjectID.at(i/2));
							if(it == objectIDs.end())
								objectIDs.push_back(TempObjectID.at(i/2));
						}
						else
						{
							objectIDs.push_back(TempObjectID.at(i/2));
						}
					}
				}
			}
		}
	}
	///���objectIDs��û���ڵ�ǰ֡�г��ֵ�objectID
	vector<int>::size_type i = 0;
	while(i < objectIDs.size())
	{
		vector<int>::iterator it = find(TempObjectID.begin(),TempObjectID.end(),objectIDs[i]);
		if(it == TempObjectID.end())///û�ҵ����˶�Ŀ��
			objectIDs.erase(objectIDs.begin() + i);
		else///����objectID��֡�ŵõ�rect
		{
			RectToShow.push_back(TempRect.at((it - TempObjectID.begin()) * 2 + 1));
			i++;
		}
	}
}

inline void vidPlayer::UpdatePauseData()
{
	if (m_clickPoint == m_clickPosInCVWnd)///�����λ��δ�����仯���򲻸�������
		return;
	m_clickPoint = m_clickPosInCVWnd;///�����λ�÷����仯,��¼�����λ��
	int objID = -1;
	for (int i=0;i<RectToShow.size();i++)
	{
		if (m_clickPosInCVWnd.x>=RectToShow.at(i).left && m_clickPosInCVWnd.x <= RectToShow.at(i).right &&
			m_clickPosInCVWnd.y>=RectToShow.at(i).top  && m_clickPosInCVWnd.y <= RectToShow.at(i).bottom)
		{
			///���ĳһ֡����ĳһλ�õ��˶�Ŀ������ID
			objID = m_MysqlObjHandle->GetObjectIDFromObjectTable(m_currentFrameNO,RectToShow.at(i),objtablename);
			if (objID != -1)
			{
				CPoint p1 = pointsToShow.at(0);
				CPoint p2 = pointsToShow.at(1);
				pointsToShow.clear();
				pointsToShow.push_back(p1);
				pointsToShow.push_back(p2);
				m_MysqlObjHandle->GetCenterFromObjectTable(objID,objtablename,&pointsToShow);///<��ȡ���˶�Ŀ��Ĺ켣����Ϣ�����浽pointToShow
				break;
			}
		}
	}
}