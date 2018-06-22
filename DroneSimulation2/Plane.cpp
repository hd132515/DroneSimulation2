#include "stdafx.h"
#include "Plane.h"
#include "BasicVertex.h"
#include "BasicIndex.h"

PlaneGeometry::PlaneGeometry(int _cell, float _unit) : cell(_cell), unit(_unit)
{
}

PlaneGeometry::~PlaneGeometry()
{
}

int PlaneGeometry::prepare(IDirect3DDevice9* pDev)
{
	int row_vert = cell + 1;
	int vert_space_sz = sizeof(ColoredNormalVertex) * row_vert * row_vert;

	if (FAILED(pDev->CreateVertexBuffer(vert_space_sz, 0, D3DFVF_CNVERT, D3DPOOL_MANAGED, &pVB, 0)))
	{
		return -1;
	}

	ColoredNormalVertex* vertices;
	if (FAILED(pVB->Lock(0, vert_space_sz, (void**)&vertices, 0)))
	{
		return -2;
	}

	int idx = 0;
	for (int row = 0; row < row_vert; row++)
	{
		for (int col = 0; col < row_vert; col++)
		{
			vertices[idx].pos.x = (float)col * unit - (float)cell * unit / 2.f;
			vertices[idx].pos.y = -(float)row * unit + (float)cell * unit / 2.f;
			vertices[idx].pos.z = 0.f;

			vertices[idx].normal.x = 0.f;
			vertices[idx].normal.y = 0.f;
			vertices[idx].normal.z = 1.f;

			vertices[idx].color = 0xFFFFFFFF;
			idx++;
		}
	}

	pVB->Unlock();

	
	int idx_space_sz = sizeof(TriIdx) * cell * cell * 2;
	if (FAILED(pDev->CreateIndexBuffer(idx_space_sz, 0, IDXFMT_TRI, D3DPOOL_MANAGED, &pIB, NULL)))
	{
		return -3;
	}

	TriIdx* indices;
	if (FAILED(pIB->Lock(0, idx_space_sz, (void**)&indices, 0)))
	{
		return -4;
	}

	idx = 0;
	for (int row = 0; row < cell; row++)
	{
		for (int col = 0; col < cell; col++)
		{
			indices[idx]._0 = row * row_vert + col;
			indices[idx]._1 = row * row_vert + col + 1;
			indices[idx]._2 = (row + 1) * row_vert + col;
			idx++;

			indices[idx]._0 = (row + 1) * row_vert + col;
			indices[idx]._1 = row * row_vert + col + 1;
			indices[idx]._2 = (row + 1) * row_vert + col + 1;
			idx++;
		}
	}

	pIB->Unlock();


	return 0;
}

int PlaneGeometry::render(IDirect3DDevice9* pDev)
{
	pDev->SetStreamSource(0, pVB, 0, sizeof(ColoredNormalVertex));
	pDev->SetIndices(pIB);
	pDev->SetFVF(D3DFVF_CNVERT);
	pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (cell + 1)*(cell + 1), 0, cell * (cell) * 2);

	return 0;
}

Plane::Plane()
{
}

Plane::~Plane()
{
}

int Plane::prepare(IDirect3DDevice9* pDev)
{
	material.Ambient.a = 1.f;
	material.Ambient.r = material.Ambient.g = material.Ambient.b = 0.9f;
	material.Specular.a = material.Specular.r = material.Specular.g = material.Specular.b = 0.13f;
	material.Power = 0.8f;

	register_render_state(D3DRS_LIGHTING, TRUE);
	register_render_state(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);


	PlaneGeometry* geometry = new PlaneGeometry(256, 0.25f);
	geometry->prepare(pDev);

	register_geometry(geometry);

	D3DXMATRIX transform;
	D3DXMatrixIdentity(&transform);
	register_transform(transform);

	return 0;
}