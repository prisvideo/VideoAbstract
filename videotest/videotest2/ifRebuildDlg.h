#pragma once


// ifRebuildDlg �Ի���

class ifRebuildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ifRebuildDlg)

public:
	boolean ifrebuild;	//�Ƿ���������
	ifRebuildDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ifRebuildDlg();

// �Ի�������
	enum { IDD = IDD_IFREBUILD };
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
