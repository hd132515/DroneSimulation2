#pragma once



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

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};


