#pragma once

#include "Node.h"

class DroneNode : public SceneNode
{
public:
	DroneNode();
	virtual ~DroneNode();

public:
	int prepare(IDirect3DDevice9* pDev);
};