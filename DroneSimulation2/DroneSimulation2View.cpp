
// DroneSimulation2View.cpp : CDroneSimulation2View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "DroneSimulation2.h"
#endif

#include "DroneSimulation2Doc.h"
#include "DroneSimulation2View.h"
#include <typeinfo>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDroneSimulation2View

IMPLEMENT_DYNCREATE(CDroneSimulation2View, CView)

BEGIN_MESSAGE_MAP(CDroneSimulation2View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CDroneSimulation2View ����/�Ҹ�

CDroneSimulation2View::CDroneSimulation2View() :
	camera(D3DXVECTOR3(1.f, 1.f, 1.f), 2.186276035f, 1.25f*D3DX_PI),
	grid(64, 1),
	plane(256, 0.25f),
	left_clicked(false),
	drone_node(new DroneNode()),
	world_root(new SceneNode())
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	active_camera = &camera;
}

CDroneSimulation2View::~CDroneSimulation2View()
{

}

BOOL CDroneSimulation2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CDroneSimulation2View �׸���


// CDroneSimulation2View ����

#ifdef _DEBUG
void CDroneSimulation2View::AssertValid() const
{
	CView::AssertValid();
}

void CDroneSimulation2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDroneSimulation2Doc* CDroneSimulation2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDroneSimulation2Doc)));
	return (CDroneSimulation2Doc*)m_pDocument;
}
#endif //_DEBUG


// CDroneSimulation2View �޽��� ó����


void CDroneSimulation2View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	initialize_d3d();
	prepare();
}


void CDroneSimulation2View::OnDraw(CDC* /*pDC*/)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void CDroneSimulation2View::prepare()
{
	CDirect3DView::prepare();

	ZeroMemory(&main_light, sizeof(D3DLIGHT9));
	main_light.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 dir(3.f, 3.f, -1.f);
	D3DXVec3Normalize((D3DXVECTOR3*)&main_light.Direction, &dir);
	main_light.Ambient.a = 1.f;
	main_light.Ambient.r = main_light.Ambient.g = main_light.Ambient.b = 1.f;
	main_light.Specular.a = main_light.Specular.r = main_light.Specular.g = main_light.Specular.b = 0.9f;

	main_light.Range = 10;
	main_light.Falloff = 2;
	main_light.Attenuation0 = 1;

	int res;
	if ((res = axis.prepare(m_pDev)) < 0)
	{
		AfxMessageBox(L"[ERROR]CDroneSi..View.cpp : CDroneSi..View::prepare() / axis.prepare");
		PostQuitMessage(-1);
		return;
	}

	grid.prepare(m_pDev);
	plane.prepare(m_pDev);

	world_root->register_render_state(D3DRS_SPECULARENABLE, TRUE);
	world_root->register_child_node(drone_node);
	drone_node->prepare(m_pDev);
}

void CDroneSimulation2View::process_input()
{
	int move_type = 0;
	if (GetAsyncKeyState('W'))
	{
		move_type |= (int)MoveType::FORWARD;
	}
	if (GetAsyncKeyState('A'))
	{
		move_type |= (int)MoveType::LEFTWARD;
	}
	if (GetAsyncKeyState('S'))
	{
		move_type |= (int)MoveType::BACKWARD;
	}
	if (GetAsyncKeyState('D'))
	{
		move_type |= (int)MoveType::RIGHTWARD;
	}

	if (move_type)
	{
		if (typeid(*active_camera) == typeid(FirstPersonCam))
		{
			((FirstPersonCam*)active_camera)->move(move_type);
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) >> 16)
	{
		CPoint point;
		GetCursorPos(&point);

		if (!left_clicked)
		{
			left_clicked = true;
			old_pt = point;
		}
		else
		{
			CPoint displ = point - old_pt;

			if (typeid(*active_camera) == typeid(FirstPersonCam))
			{
				((FirstPersonCam*)active_camera)->change_direction(displ.y, -displ.x);
			}

			old_pt = point;
		}
	}
	else
		left_clicked = false;
}

void CDroneSimulation2View::render_process()
{
	//3D area
	//m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pDev->SetTransform(D3DTS_PROJECTION, &projection);
	active_camera->setup(m_pDev);


	m_pDev->SetLight(1, &main_light);
	m_pDev->LightEnable(1, TRUE);
	world_root->render(m_pDev, NULL);
	plane.render(m_pDev);


	grid.render(m_pDev);
	axis.render(m_pDev);

	//multi cam
	
	//2D area
}
