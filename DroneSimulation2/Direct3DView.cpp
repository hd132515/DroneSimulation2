// Direct3DView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "Direct3DView.h"
#include <d3dx9.h>

IDirect3D9* g_pDirect3D = NULL;

// CDirect3DView

IMPLEMENT_DYNCREATE(CDirect3DView, CView)

CDirect3DView::CDirect3DView() : m_pDev(NULL)
{
	
}

CDirect3DView::~CDirect3DView()
{
}

BEGIN_MESSAGE_MAP(CDirect3DView, CView)
END_MESSAGE_MAP()



// CDirect3DView 진단입니다.


void CDirect3DView::OnDraw(CDC* /*pDC*/)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


#ifdef _DEBUG
void CDirect3DView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CDirect3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDirect3DView 메시지 처리기입니다.
int CDirect3DView::initialize_d3d()
{
	RECT window_rect;
	HWND target_window_handle = GetSafeHwnd();
	GetClientRect(&window_rect);

	if ((g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		AfxMessageBox(L"[ERROR]Direct3DView.cpp : CDirect3DView::initialize_d3d(), Direct3DCreate9");
		return -1;
	}

	D3DCAPS9 caps;
	g_pDirect3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 2;
	d3dpp.BackBufferWidth = window_rect.right - window_rect.left;
	d3dpp.BackBufferHeight = window_rect.bottom - window_rect.top;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	if (FAILED(g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, target_window_handle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pDev)))
	{
		AfxMessageBox(L"[ERROR]Direct3DView.cpp : CDirect3DView::initialize_d3d(), CreateDevice");
		return -1;
	}

	return 0;
}

void CDirect3DView::prepare()
{
	RECT window_rect;
	GetClientRect(&window_rect);
	float aspect = (float)(window_rect.right - window_rect.left) / (window_rect.bottom - window_rect.left);
	
	D3DXMatrixPerspectiveFovRH(&projection, D3DX_PI / 3.f, aspect, 0.1f, 1000.f);
}

void CDirect3DView::process_input()
{
}

void CDirect3DView::pre_render()
{
	if (m_pDev == NULL)
	{
		AfxMessageBox(L"[ERROR]Direct3DView.cpp : CDirect3DView::render / Device lost before rendering.");
		PostQuitMessage(-1);
	}

	m_pDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.f, 1);
	
	m_pDev->BeginScene();
}

void CDirect3DView::render_process()
{
}

void CDirect3DView::post_render()
{
	m_pDev->EndScene();

	m_pDev->Present(NULL, NULL, NULL, NULL);
}

void CDirect3DView::release_all()
{
	if (m_pDev != NULL)
	{
		m_pDev->Release();
		m_pDev = NULL;
	}
}

BOOL CDirect3DView::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	release_all();

	return CView::DestroyWindow();
}
