
// videotest2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
//#include "mfcvideoplayer.h"
#include "vidPlayer.h"

// Cvideotest2App:
// �йش����ʵ�֣������ videotest2.cpp
//

class Cvideotest2App : public CWinApp
{
public:
	Cvideotest2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cvideotest2App theApp;