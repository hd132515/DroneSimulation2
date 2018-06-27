// ScenarioSetupView.cpp : ���� �����Դϴ�.
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


void CScenarioSetupView::OnBnClickedStartBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	btnStart.EnableWindow(TRUE);
	btnStop.EnableWindow(FALSE);
	PhysicsThread::get_instance().stop();
}
