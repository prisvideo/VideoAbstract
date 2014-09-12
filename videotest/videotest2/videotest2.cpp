
// videotest2.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "videotest2.h"
#include "videotest2Dlg.h"
#include "ChangeIniFileDlg.h"
#include "SkinPPWTL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cvideotest2App

BEGIN_MESSAGE_MAP(Cvideotest2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)	
	ON_COMMAND(ID_MENU_CHANGEINIFILE, &Cvideotest2App::OnMenuChangeinifile)
END_MESSAGE_MAP()


// Cvideotest2App ����

Cvideotest2App::Cvideotest2App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Cvideotest2App ����

Cvideotest2App theApp;


// Cvideotest2App ��ʼ��

BOOL Cvideotest2App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	
	CWinApp::InitInstance();
	
	//Skin++ initializie
	skinppLoadSkin(_T("..\\SkinPlusplus\\AquaOS.ssk"));

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	Cvideotest2Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int Cvideotest2App::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	skinppExitSkin();
	
	AfxOleTerm(FALSE);
	
	return CWinApp::ExitInstance();
}



void Cvideotest2App::OnMenuChangeinifile()
{
	// TODO: Add your command handler code here
	ChangeIniFileDlg m_ChangeIniDlg;
	m_ChangeIniDlg.DoModal();
}
