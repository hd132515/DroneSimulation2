#pragma once

#include <deque>
#include <list>
#include <d3dx9.h>
#include <functional>

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

struct Mass
{
	Vector3 pos;
	float mass;
};

class Body;

typedef std::list<std::pair<Vector3, Vector3>> ForceList;
typedef std::list<Mass> MassList;

class InteractionFunc
{
public:
	virtual void interaction(ForceList& forces, Body* body) = 0;
};

class Body
{
public:
	Body();
private:
	std::list<D3DXMATRIX> frame_datas;
protected:
	/*Constant quantities*/
	Vector3 COM;
	float mass;
	Matrix3x3 Ibody, Ibodyinv;

	/*State variables*/
	Vector3 x;
	Quaternion q;
	Vector3 P;
	Vector3 L;

	/*Derived quantities(auxiliary variables)*/
	Matrix3x3 Iinv, R;
	Vector3 v, omega;

	InteractionFunc* interaction;
private:
	void update_frame();

	void calculate_constants(std::list<Mass>& masses);
protected:
public:
	void set_position(Vector3& position);
	void set_velocity(Vector3& velocity);
	void set_orientation(Vector3& rotation_axis, float angle);
	void set_angular_velo(Vector3& ang_vel);

	float get_mass();
	Vector3& get_position();
	Vector3& get_velocity();
	Matrix3x3& get_orientation();

	void body_init(InteractionFunc* _interaction, MassList& masses, Vector3& position, Vector3& velocity, Vector3& rotation_axis, float angle, Vector3& ang_vel);

	void start();

	virtual void update(float deltaTime);

	D3DXMATRIX get_render_frame();

	void clean_frames(int target_frames);
};