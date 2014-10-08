// WelcomeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "videotest2.h"
#include "WelcomeDlg.h"
#include "afxdialogex.h"
#include <Windows.h>


// WelcomeDlg �Ի���

IMPLEMENT_DYNAMIC(WelcomeDlg, CDialogEx)

	WelcomeDlg::WelcomeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(WelcomeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

WelcomeDlg::~WelcomeDlg()
{ 
}

void WelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WelcomeDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// WelcomeDlg ��Ϣ�������


void WelcomeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
	switch(nIDEvent)  
	{  
	case 1: //���idΪ1��timer��������ִ�йرմ��ڲ���  
		SendMessage(WM_CLOSE);  
		break;  
	default:  
		break;  
	} 
}


BOOL WelcomeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	//SetBackgroundImage(IDB_WELCOME);
	SetTimer(1, 3000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void WelcomeDlg::OnPaint()
{
	//UIBeautifier.PaintBackground(this->GetSafeHwnd());
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		//ʹͼ���ڹ����������о���
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
		CPaintDC   dc(this);   
		CRect   rect;   
		GetClientRect(&rect);   
		CDC   dcMem;   
		dcMem.CreateCompatibleDC(&dc);   
		CBitmap   bmpBackground;   
		bmpBackground.LoadBitmap(IDB_WELCOME);   
		//IDB_BITMAP�����Լ���ͼ��Ӧ��ID   
		BITMAP   bitmap;   
		bmpBackground.GetBitmap(&bitmap);   
		CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);  
		CDialogEx::OnPaint();

	}
	
}


HCURSOR WelcomeDlg::OnQueryDragIcon()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return static_cast<HCURSOR>(m_hIcon);
}
