#include "stdafx.h"
#include "Drone.h"
#include "Box.h"

DroneNode::DroneNode()
{
}

DroneNode::~DroneNode()
{
}

int DroneNode::prepare(IDirect3DDevice9* pDev)
{
	D3DXMATRIX transform;

	material.Ambient.a = 1.f;
	material.Ambient.r = material.Ambient.g = material.Ambient.b = 0.1f;
	material.Specular.a = material.Specular.r = material.Specular.g = material.Specular.b = 0.2f;
	material.Power = 10.f;

	register_render_state(D3DRS_LIGHTING, TRUE);
	register_render_state(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	
	BoxGeometry* diag13 = new BoxGeometry(0.45f, 0.02f, 0.02f);
	if (diag13->prepare(pDev)) return -1;
	{
		D3DXMATRIX rotation;
		D3DXMatrixRotationZ(&rotation, -D3DX_PI / 4.f);
		transform = rotation;
	}
	SceneNode* diag13_n = new SceneNode();
	diag13_n->register_geometry(diag13);
	diag13_n->register_transform(transform);
	memcpy(&diag13_n->material, &material, sizeof(D3DMATERIAL9));



	BoxGeometry* diag24 = new BoxGeometry(0.45f, 0.02f, 0.02f);
	if (diag24->prepare(pDev)) return -1;
	{
		D3DXMATRIX rotation;
		D3DXMatrixRotationZ(&rotation, D3DX_PI / 4.f);
		transform = rotation;
	}
	SceneNode* diag24_n = new SceneNode();
	diag24_n->register_geometry(diag24);
	diag24_n->register_transform(transform);
	memcpy(&diag24_n->material, &material, sizeof(D3DMATERIAL9));

	child_nodes.push_back(diag13_n);
	child_nodes.push_back(diag24_n);

	return 0;
}
