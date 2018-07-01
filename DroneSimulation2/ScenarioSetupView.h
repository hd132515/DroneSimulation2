#pragma once
#include "afxwin.h"

#include "Controller.h"

// CScenarioSetupView �� ���Դϴ�.

class CScenarioSetupView : public CFormView
{
	DECLARE_DYNCREATE(CScenarioSetupView)

protected:
	CScenarioSetupView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CScenarioSetupView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCENARIOSETUPVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

private:
	Controller* controller;
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedStartBtn();
	afx_msg void OnBnClickedStopBtn();
	float pos_x;
	float pos_y;
	float pos_z;
	float vel_x;
	float vel_y;
	float vel_z;
	float ori_x;
	float ori_y;
	float ori_z;
	float av_x;
	float av_y;
	float av_z;
	CButton btnStart;
	CButton btnStop;

	void set_controller(Controller* _controller);
};


