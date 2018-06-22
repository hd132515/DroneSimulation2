#pragma once

#include "Geometry.h"

class BoxGeometry : public Geometry
{
public:
	BoxGeometry(float x, float y, float z);
	virtual ~BoxGeometry();
private:
	float _x, _y, _z;
public:
	virtual int prepare(IDirect3DDevice9* pDev);
	virtual int render(IDirect3DDevice9* pDev);
};
