#pragma once

#include "Vertex.h"
#include "RigidBody.h"
#include "Vector.h"


class Drone : public RigidBody
{
public:
	Drone();
private:
	float prop[4];

	Vector3 motorpos[4];

	Vector3 standard;
	float observation_time;
	
	D3DXMATRIX matTrans;

	IDirect3DVertexBuffer9* pVB[2];
	IDirect3DIndexBuffer9* pIB;
	bool ready;

	Vector3 COM;
public:
	virtual void build_structure(std::list<Mass>& masses, Vector3** COM);
	virtual void interaction(std::list<std::pair<Vector3, Vector3>>& forces);
	virtual void update(float deltaTime);
public:
	void initialize();
	void render();

	void setProp(float* prop);
	void measuring();

	void getEulerAngles(float& roll, float& pitch, float& yaw);
	void getMotorPos(Vector3* vecs);
	float getHeight();

	float getMass();
	float getObsTime();
	bool isReady();
};