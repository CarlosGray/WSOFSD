
// WSOFSD.h : WSOFSD Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CWSOFSDApp:
// �йش����ʵ�֣������ WSOFSD.cpp
//

class CWSOFSDApp : public CWinApp
{
public:
	CWSOFSDApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWSOFSDApp theApp;
