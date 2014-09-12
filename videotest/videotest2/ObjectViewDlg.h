#pragma once
#include "afxwin.h"
#include "vidPlayer.h"
#include "LibMySql.h"


// CObjectViewDlg �Ի���





class CObjectViewDlg : public CDialog
{
	DECLARE_DYNAMIC(CObjectViewDlg)

public:
	CObjectViewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CObjectViewDlg();
	void ShowImage( IplImage* img, UINT ID,CString WName);    // ID ��Picture Control�ؼ���ID��

// �Ի�������
	enum { IDD = IDD_OBJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedButtonObject();
	afx_msg void OnBnClickedObjectLeft();
	afx_msg void OnBnClickedObjectRight();
	afx_msg void OnStnClickedStaticObject1();
	afx_msg void OnStnClickedStaticObject2();
	afx_msg void OnStnClickedStaticObject3();
	afx_msg void OnStnClickedStaticObject4();
	
	CStatic ObjectPicture_1;
	int m_pageSum;							///<��¼һҳ���ٸ�����ͼ
	int m_pageNum;							///<��¼��ǰ����ͼ����ʾ��Ϊ�ڼ�ҳ
	CDataMySql* m_MysqlVideoHandle;
	CVideo *videoPro;
	vidPlayer oriPlayer;
	void DisplayPageSumImg();
	vector<objectInfo> objDetectedInfos;	///<�洢���ݿ��������Ϣ��������ʾ����ͼ
	void DetectResult();
	bool UserClick;///<�����ж��û����ް�����꣬�޲���ʱΪFALSE���в���ʱΪTRUE
	bool Generated;///<�û��Ƿ����ˡ����ɡ���ť
	int OriFrame;//���ڴ��������Ի����ò�����������Ӧ��֡
};
