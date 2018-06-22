#include "stdafx.h"
#include "Box.h"
#include "BasicVertex.h"


BoxGeometry::BoxGeometry(float x, float y, float z) : _x(x), _y(y), _z(z)
{
}

BoxGeometry::~BoxGeometry()
{
}

int BoxGeometry::prepare(IDirect3DDevice9* pDev)
{
	float half_x = _x / 2.f;
	float half_y = _y / 2.f;
	float half_z = _z / 2.f;

	ColoredNormalVertex source[] =
	{
		// 좌(xz)
		{ D3DXVECTOR3(-half_x,-half_y, half_z), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(half_x,-half_y, half_z), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x,-half_y,-half_z), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3(-half_x,-half_y, -half_z), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(half_x,-half_y, half_z), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(half_x, -half_y, -half_z), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		// 우(xz)
		{ D3DXVECTOR3(half_x,half_y, half_z), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x,half_y, half_z), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x,half_y,-half_z), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3(half_x,half_y, half_z), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x,half_y, -half_z), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(half_x, half_y, -half_z), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		// 뒤(yz)
		{ D3DXVECTOR3(-half_x, half_y, half_z), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x,-half_y, half_z), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x,-half_y,-half_z), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3(-half_x, half_y, half_z), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x,-half_y,-half_z), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x, half_y,-half_z), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		// 앞(yz)
		{ D3DXVECTOR3(half_x,-half_y, half_z), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(half_x, half_y, half_z), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(half_x,-half_y,-half_z), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3(half_x,-half_y,-half_z), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(half_x, half_y, half_z), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(half_x, half_y,-half_z), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		// 상(xy)
		{ D3DXVECTOR3(half_x, half_y, half_z), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x,-half_y, half_z), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x, half_y, half_z), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3(half_x, half_y, half_z), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(half_x,-half_y, half_z), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x,-half_y, half_z), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },

		// 하(xy)
		{ D3DXVECTOR3(-half_x,-half_y, -half_z), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(half_x, half_y, -half_z), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x, half_y, -half_z), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3(half_x,-half_y, -half_z), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(half_x, half_y, -half_z), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-half_x,-half_y, -half_z), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },

	};

	int vert_space_sz = sizeof(ColoredNormalVertex) * 36;

	if (FAILED(pDev->CreateVertexBuffer(vert_space_sz, 0, D3DFVF_CNVERT, D3DPOOL_MANAGED, &pVB, NULL)))
	{
		AfxMessageBox(L"[ERROR] Box.cpp : Box::prepare() : CreateVB");
		return -1;
	}

	ColoredNormalVertex* vertices;
	if (FAILED(pVB->Lock(0, vert_space_sz, (void**)&vertices, 0)))
	{
		AfxMessageBox(L"[ERROR] Box.cpp : Box::prepare() : LockVB");
		return -2;
	}

	memcpy(vertices, source, vert_space_sz);

	pVB->Unlock();

	return 0;
}

int BoxGeometry::render(IDirect3DDevice9* pDev)
{
	pDev->SetStreamSource(0, pVB, 0, sizeof(ColoredNormalVertex));
	pDev->SetFVF(D3DFVF_CNVERT);

	pDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6 * 2);
	return 0;
}
