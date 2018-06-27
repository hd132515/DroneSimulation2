#pragma once

#include "GeneralObject.h"

class Drone : public GeneralObject
{
public:
	Drone();
	~Drone();

private:
	Vector3 motorpos[4];
	float prop[4];

protected:
	virtual int prepare_scenenode(IDirect3DDevice9* pDev);
	virtual int prepare_body();
public:
	virtual void interaction(ForceList& forces, Body* body);
};