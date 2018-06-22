#pragma once

#include <d3dx9.h>
#include <vector>
#include "Geometry.h"

class SceneNode
{
public:
	SceneNode();
	~SceneNode();
protected:
	bool material_using;
	D3DXMATRIX parent_trans;
	D3DXMATRIX transform;
	Geometry* geometry;
	std::vector<std::pair<D3DRENDERSTATETYPE, DWORD>> parent_state;
	std::vector<std::pair<D3DRENDERSTATETYPE, DWORD>> render_state;
	std::vector<SceneNode*> child_nodes;
public:
	D3DMATERIAL9 material;

private:
	void setup_node(IDirect3DDevice9* pDev, D3DXMATRIX* parent_transform);
	void rollback_node(IDirect3DDevice9* pDev);

public:
	void register_child_node(SceneNode* child_node);
	void register_render_state(D3DRENDERSTATETYPE rs_type, DWORD value);
	void register_transform(D3DXMATRIX& _transform);
	void register_geometry(Geometry* _geometry);

	bool validate_node();

	int render(IDirect3DDevice9* pDev, D3DXMATRIX* parent_transform);

	void release();
};
