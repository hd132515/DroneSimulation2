#include "stdafx.h"
#include "Box.h"
#include "BasicVertex.h"


Box::Box() : pVB(NULL)
{
}

Box::~Box()
{
	release();
}

int Box::prepare(IDirect3DDevice9* pDev)
{
	ColoredNormalVertex source[] =
	{
		// 좌(xz)
		{ D3DXVECTOR3(-0.5f,-0.5f, 0.5f), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(0.5f,-0.5f, 0.5f), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3(-0.5f,-0.5f, -0.5f), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(0.5f,-0.5f, 0.5f), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.f, -1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		// 우(xz)
		{ D3DXVECTOR3(0.5f,0.5f, 0.5f), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f,0.5f, 0.5f), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f,0.5f,-0.5f), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3(0.5f,0.5f, 0.5f), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f,0.5f, -0.5f), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.f, 1.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		// 뒤(yz)
		{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f,-0.5f, 0.5f), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f, 0.5f,-0.5f), D3DXVECTOR3(-1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		// 앞(yz)
		{ D3DXVECTOR3(0.5f,-0.5f, 0.5f), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(0.5f,-0.5f,-0.5f), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3(0.5f,-0.5f,-0.5f), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(0.5f, 0.5f,-0.5f), D3DXVECTOR3(1.f, 0.f, 0.f), D3DCOLOR_XRGB(0, 0, 0) },

		// 상(xy)
		{ D3DXVECTOR3( 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f,-0.5f, 0.5f), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3( 0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3( 0.5f,-0.5f, 0.5f), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f,-0.5f, 0.5f), D3DXVECTOR3(0.f, 0.f, 1.f), D3DCOLOR_XRGB(0, 0, 0) },

		// 하(xy)
		{ D3DXVECTOR3(-0.5f,-0.5f, -0.5f), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },

		{ D3DXVECTOR3(0.5f,-0.5f, -0.5f), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },
		{ D3DXVECTOR3(-0.5f,-0.5f, -0.5f), D3DXVECTOR3(0.f, 0.f, -1.f), D3DCOLOR_XRGB(0, 0, 0) },

	};

	int vert_space_sz = sizeof(ColoredNormalVertex) * 36;

	if (FAILED(pDev->CreateVertexBuffer(vert_space_sz, 0, D3DFVF_CNVERT, D3DPOOL_MANAGED, &pVB, NULL)))
	{
		return -1;
	}

	ColoredNormalVertex* vertices;
	if (FAILED(pVB->Lock(0, vert_space_sz, (void**)&vertices, 0)))
	{
		return -2;
	}

	memcpy(vertices, source, vert_space_sz);

	pVB->Unlock();

	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient.a = 1.f;
	material.Ambient.r = material.Ambient.g = material.Ambient.b = 0.1f;
	material.Specular.a = material.Specular.r = material.Specular.g = material.Specular.b = 0.3f;
	material.Power = 10.f;

	return 0;
}

int Box::render(IDirect3DDevice9* pDev)
{
	pDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDev->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

	pDev->SetMaterial(&material);
	pDev->SetStreamSource(0, pVB, 0, sizeof(ColoredNormalVertex));
	pDev->SetFVF(D3DFVF_CNVERT);

	pDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6 * 2);
	return 0;
}

void Box::release()
{
	if (pVB != NULL)
	{
		pVB->Release();
		pVB = NULL;
	}
}