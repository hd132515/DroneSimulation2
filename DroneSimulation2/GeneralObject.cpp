#include "stdafx.h"
#include "GeneralObject.h"
#include "PhysicsThread.h"

GeneralObject::GeneralObject(std::string _name) : name(_name), node(NULL), body(NULL)
{
}

GeneralObject::~GeneralObject()
{
}

int GeneralObject::prepare(IDirect3DDevice9* pDev, SceneNode* parent)
{
	node = new SceneNode();
	body = new Body();

	int ret;

	ret = prepare_scenenode(pDev);
	if (ret) return 0x10000 & ret;

	ret = prepare_body();
	if (ret) return 0x20000 & ret;

	parent->register_child_node(node);
	PhysicsThread::get_instance().register_object(name, body);

	return 0;
}

void GeneralObject::update()
{
	node->register_transform(body->get_render_frame());
}