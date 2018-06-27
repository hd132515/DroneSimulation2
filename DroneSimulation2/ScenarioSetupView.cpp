// ScenarioSetupView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "ScenarioSetupView.h"
#include "PhysicsThread.h"
#include "Body.h"


// CScenarioSetupView

IMPLEMENT_DYNCREATE(CScenarioSetupView, CFormView)

CScenarioSetupView::CScenarioSetupView()
	: CFormView(IDD_SCENARIOSETUPVIEW)
	, pos_x(0)
	, pos_y(0),
	 pos_z(0),
 vel_x(0),
vel_y(0),
vel_z(0),
ori_x(0),
ori_y(0),
ori_z(0),
av_x(0),
av_y(0),
av_z(0)
{

}

CScenarioSetupView::~CScenarioSetupView()
{
}

void CScenarioSetupView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, pos_x);
	DDX_Text(pDX, IDC_EDIT3, pos_y);
	DDX_Text(pDX, IDC_EDIT4, pos_z);
	DDX_Text(pDX, IDC_EDIT5, vel_x);
	DDX_Text(pDX, IDC_EDIT6, vel_y);
	DDX_Text(pDX, IDC_EDIT7, vel_z);
	DDX_Text(pDX, IDC_EDIT8, ori_x);
	DDX_Text(pDX, IDC_EDIT9, ori_y);
	DDX_Text(pDX, IDC_EDIT10, ori_z);
	DDX_Text(pDX, IDC_EDIT11, av_x);
	DDX_Text(pDX, IDC_EDIT12, av_y);
	DDX_Text(pDX, IDC_EDIT13, av_z);
	DDX_Control(pDX, IDC_START_BTN, btnStart);
	DDX_Control(pDX, IDC_STOP_BTN, btnStop);
}

BEGIN_MESSAGE_MAP(CScenarioSetupView, CFormView)
	ON_BN_CLICKED(IDC_START_BTN, &CScenarioSetupView::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CScenarioSetupView::OnBnClickedStopBtn)
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


void CScenarioSetupView::OnBnClickedStartBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	btnStart.EnableWindow(FALSE);
	btnStop.EnableWindow(TRUE);
	UpdateData();
	Body* drone = (Body*)PhysicsThread::get_instance().get_object(std::string("drone"));
	
	Vector3 position(pos_x, pos_y, pos_z);
	Vector3 velocity(vel_x, vel_y, vel_z);
	Vector3 rotation(ori_x, ori_y, ori_z);
	Vector3 angular_v(av_x, av_y, av_z);

	drone->set_position(position);
	drone->set_velocity(velocity);
	drone->set_orientation(rotation.getNorm(), rotation.length());
	drone->set_angular_velo(angular_v);

	PhysicsThread::get_instance().start();
}


void CScenarioSetupView::OnBnClickedStopBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	btnStart.EnableWindow(TRUE);
	btnStop.EnableWindow(FALSE);
	PhysicsThread::get_instance().stop();
}
