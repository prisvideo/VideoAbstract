// ifRebuildDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "videotest2.h"
#include "ifRebuildDlg.h"
#include "afxdialogex.h"


// ifRebuildDlg �Ի���

IMPLEMENT_DYNAMIC(ifRebuildDlg, CDialogEx)

ifRebuildDlg::ifRebuildDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ifRebuildDlg::IDD, pParent)
{

}

ifRebuildDlg::~ifRebuildDlg()
{
}

void ifRebuildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ifRebuildDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ifRebuildDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ifRebuildDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// ifRebuildDlg ��Ϣ�������


void ifRebuildDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ifrebuild = true;
	CDialogEx::OnOK();
}


void ifRebuildDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ifrebuild = false;
	CDialogEx::OnCancel();
}
