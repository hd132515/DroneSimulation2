#include "stdafx.h"
#include "SceneNode.h"

SceneNode::SceneNode() : geometry(NULL)
{
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	D3DXMatrixIdentity(&rigid_transform);
}

SceneNode::~SceneNode()
{
	release();
}

void SceneNode::register_child_node(SceneNode* child_node)
{
	if (child_node != NULL)
	{
		child_nodes.push_back(child_node);
	}
}

void SceneNode::register_render_state(D3DRENDERSTATETYPE rs_type, DWORD value)
{
	render_state[rs_type] = value;
}

void SceneNode::register_transform(D3DXMATRIX& _transform)
{
	rigid_transform = _transform;
}

void SceneNode::register_geometry(Geometry* _geometry)
{
	geometry = _geometry;
}

void SceneNode::setup_node(IDirect3DDevice9* pDev, D3DXMATRIX* parent_transform)
{
	applied = rigid_transform;
	if (parent_transform != NULL)
		applied *= *parent_transform;

	if(geometry != NULL)
		pDev->SetTransform(D3DTS_WORLD, &applied);

	pDev->GetMaterial(&parent_material);
	pDev->SetMaterial(&material);

	for (auto elem : render_state)
	{
		DWORD parent;

		pDev->GetRenderState(elem.first, &parent);
		parent_state[elem.first] = parent;

		pDev->SetRenderState(elem.first, elem.second);
	}
}

void SceneNode::rollback_node(IDirect3DDevice9* pDev)
{
	pDev->SetMaterial(&parent_material);

	for (auto elem : parent_state)
	{
		pDev->SetRenderState(elem.first, elem.second);
	}
}

int SceneNode::render(IDirect3DDevice9* pDev, D3DXMATRIX* parent_transform)
{
	setup_node(pDev, parent_transform);

	if (geometry != NULL)
		geometry->render(pDev);

	for (auto child : child_nodes)
	{
		child->render(pDev, &applied);
	}

	rollback_node(pDev);

	return 0;
}


bool SceneNode::validate_node()
{
	return geometry != NULL;
}

void SceneNode::release()
{
	if (geometry != NULL)
	{
		delete geometry;
		geometry = NULL;
	}

	for (auto elem : child_nodes)
	{
		delete elem;
	}
	child_nodes.clear();
}