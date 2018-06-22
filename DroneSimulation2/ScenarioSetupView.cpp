// ScenarioSetupView.cpp : 구현 파일입니다.
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


// CScenarioSetupView 진단입니다.

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


// CScenarioSetupView 메시지 처리기입니다.


void CScenarioSetupView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
