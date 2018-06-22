#pragma once

#include "Node.h"

class PlaneGeometry : public Geometry
{
public:
	PlaneGeometry(int _cell, float _unit);
	~PlaneGeometry();
private:
	int cell;
	float unit;
protected:
public:
	int prepare(IDirect3DDevice9* pDev);
	int render(IDirect3DDevice9* pDev);
};

class Plane : public SceneNode
{
public:
	Plane();
	virtual ~Plane();
public:
	int prepare(IDirect3DDevice9* pDev);
};