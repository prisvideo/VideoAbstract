#pragma once

// WelcomeDlg �Ի���

class WelcomeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WelcomeDlg)

public:
	WelcomeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WelcomeDlg();

// �Ի�������
	enum { IDD = IDD_WELCOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
};
