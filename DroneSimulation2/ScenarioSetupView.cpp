// ScenarioSetupView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "ScenarioSetupView.h"


// CScenarioSetupView

IMPLEMENT_DYNCREATE(CScenarioSetupView, CFormView)

CScenarioSetupView::CScenarioSetupView()
	: CFormView(IDD_SCENARIOSETUPVIEW)
{

}

CScenarioSetupView::~CScenarioSetupView()
{
}

void CScenarioSetupView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScenarioSetupView, CFormView)
END_MESSAGE_MAP()


// CScenarioSetupView �����Դϴ�.

#ifdef _DEBUG
void CScenarioSetupView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CScenarioSetupView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CScenarioSetupView �޽��� ó�����Դϴ�.


void CScenarioSetupView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
