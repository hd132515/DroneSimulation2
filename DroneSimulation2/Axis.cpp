#include "stdafx.h"
#include "Axis.h"
#include "BasicVertex.h"

Axis::Axis() : pVB(NULL)
{
}

Axis::~Axis()
{
	release();
}

int Axis::prepare(IDirect3DDevice9* pDev)
{
	ColoredVertex vertices[] = {
		{ D3DXVECTOR3(0.f, 0.f, 0.002f), D3DCOLOR_XRGB(255, 0, 0) },
		{ D3DXVECTOR3(1.f, 0.f, 0.002f), D3DCOLOR_XRGB(255, 0, 0) },
		{ D3DXVECTOR3(0.f, 0.f, 0.002f), D3DCOLOR_XRGB(0, 255, 0) },
		{ D3DXVECTOR3(0.f, 1.f, 0.002f), D3DCOLOR_XRGB(0, 255, 0) },
		{ D3DXVECTOR3(0.f, 0.f, 0.002f), D3DCOLOR_XRGB(0, 0, 255) },
		{ D3DXVECTOR3(0.f, 0.f, 1.002f), D3DCOLOR_XRGB(0, 0, 255) },
	};

	if (FAILED(pDev->CreateVertexBuffer(6 * sizeof(ColoredVertex), 0, D3DFVF_COLOREDVERT, D3DPOOL_MANAGED, &pVB, NULL)))
	{
		return -1;
	}

	ColoredVertex* vert_addr;
	if (FAILED(pVB->Lock(0, 6 * sizeof(ColoredVertex), (void**)&vert_addr, 0)))
	{
		return -2;
	}

	memcpy(vert_addr, vertices, 6 * sizeof(ColoredVertex));

	if (FAILED(pVB->Unlock()))
	{
		return -3;
	}

	return 0;
}

int Axis::render(IDirect3DDevice9* pDev)
{
	pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDev->SetStreamSource(0, pVB, 0, sizeof(ColoredVertex));
	pDev->SetFVF(D3DFVF_COLOREDVERT);
	if (FAILED(pDev->DrawPrimitive(D3DPT_LINELIST, 0, 3)))
	{
		return -1;
	}
	pDev->SetRenderState(D3DRS_LIGHTING, TRUE);

	return 0;
}

void Axis::release()
{
	if (pVB != NULL)
	{
		pVB->Release();
		pVB = NULL;
	}
}