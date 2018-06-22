#include "stdafx.h"
#include "Grid.h"

GridGeometry::GridGeometry(int _size, int _unit) : size(_size), unit(_unit)
{
}

GridGeometry::~GridGeometry()
{
	release();
}

int GridGeometry::prepare(IDirect3DDevice9* pDev)
{
	int cells = size;
	int lines = size + 1;


	int vertex_space = sizeof(ColoredVertex) * 2 * 2 * lines;
	if (FAILED(pDev->CreateVertexBuffer(vertex_space, 0, D3DFVF_COLOREDVERT, D3DPOOL_MANAGED, &pVB, NULL)))
	{
		return -1;
	}

	ColoredVertex* vertices;
	if (FAILED(pVB->Lock(0, vertex_space, (void**)&vertices, 0)))
	{
		return -2;
	}
	ZeroMemory(vertices, vertex_space);


	float half_length = cells / 2.f * unit;
	int i, j;

	for (i = 0; i < lines; i++)
	{
		vertices[i * 2 + 0].pos = D3DXVECTOR3((-cells / 2 + i) * unit, -half_length, 0.001f);
		vertices[i * 2 + 0].color = D3DCOLOR_ARGB(30, 0, 0, 0);
		vertices[i * 2 + 1].pos = D3DXVECTOR3((-cells / 2 + i) * unit, half_length, 0.001f);
		vertices[i * 2 + 1].color = D3DCOLOR_ARGB(30, 0, 0, 0);
	}

	for (j = 0; j < lines; j++)
	{
		vertices[(i + j) * 2 + 0].pos = D3DXVECTOR3(-half_length, (-cells / 2 + j) * unit, 0.001f);
		vertices[(i + j) * 2 + 0].color = D3DCOLOR_ARGB(30, 0, 0, 0);
		vertices[(i + j) * 2 + 1].pos = D3DXVECTOR3(half_length, (-cells / 2 + j) * unit, 0.001f);
		vertices[(i + j) * 2 + 1].color = D3DCOLOR_ARGB(30, 0, 0, 0);
	}

	pVB->Unlock();

	return 0;
}

int GridGeometry::render(IDirect3DDevice9* pDev)
{
	pDev->SetStreamSource(0, pVB, 0, sizeof(ColoredVertex));
	pDev->SetFVF(D3DFVF_COLOREDVERT);
	if (FAILED(pDev->DrawPrimitive(D3DPT_LINELIST, 0, 2*(size+1))))
	{
		return -1;
	}
	pDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	return 0;
}




Grid::Grid()
{
}

Grid::~Grid()
{
}

int Grid::prepare(IDirect3DDevice9* pDev)
{
	register_render_state(D3DRS_ALPHABLENDENABLE, TRUE);
	register_render_state(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	register_render_state(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR1);
	register_render_state(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	register_render_state(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	register_render_state(D3DRS_LIGHTING, FALSE);

	GridGeometry* grid = new GridGeometry(64, 1);
	grid->prepare(pDev);

	register_geometry(grid);

	D3DXMATRIX transform;
	D3DXMatrixIdentity(&transform);
	register_transform(transform);

	return 0;
}