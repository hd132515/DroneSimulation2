#pragma once

#include <d3dx9.h>
#include <string>
#include "SceneNode.h"
#include "Body.h"

class GeneralObject : public InteractionFunc
{
public:
	GeneralObject(std::string _name);
	~GeneralObject();
private:
	std::string name;
protected:
	SceneNode* node;
	Body* body;
protected:
	virtual int prepare_scenenode(IDirect3DDevice9* pDev) = 0;
	virtual int prepare_body() = 0;
public:
	virtual void interaction(ForceList& forces, Body* body) = 0;
	int prepare(IDirect3DDevice9* pDev, SceneNode* parent);
	void update();
};