
// DroneSimulation2.h : DroneSimulation2 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CDroneSimulation2App:
// �� Ŭ������ ������ ���ؼ��� DroneSimulation2.cpp�� �����Ͻʽÿ�.
//

class CDroneSimulation2App : public CWinApp
{
public:
	CDroneSimulation2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CDroneSimulation2App theApp;
