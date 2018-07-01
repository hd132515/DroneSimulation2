#include "stdafx.h"
#include "Body.h"
#include "utility.h"
#include "PhysicsThread.h"
#include <iostream>

Body::Body()
{
}

void Body::set_position(Vector3& position)
{
	x = position;
}

void Body::set_velocity(Vector3& velocity)
{
	v = velocity;
	P = velocity * mass;
}

void Body::set_orientation(Vector3& rotation_axis, float angle)
{
	q.rotater(rotation_axis, angle);
	R = q.normalize().to_matrix();
	Iinv = R * Ibodyinv * R.transpose();
}

void Body::set_angular_velo(Vector3& ang_vel)
{
	L = Ibody * ang_vel;
	omega = ang_vel;
}

void Body::body_init(InteractionFunc* _interaction, PostUpdateFunc* _post_update, MassList& masses, Vector3& position, Vector3& velocity, Vector3& rotation_axis, float angle, Vector3& ang_vel)
{
	interaction = _interaction;
	post_update = _post_update;
	
	calculate_constants(masses);

	set_position(position);
	set_velocity(velocity);
	set_orientation(rotation_axis, angle);
	set_angular_velo(ang_vel);
}

void Body::calculate_constants(std::list<Mass>& masses)
{
	for (auto mass_e : masses)
	{
		float m = mass_e.mass;
		mass += m;
		COM += m * mass_e.pos;
	}
	COM /= mass;

	//CM Coordinate
	for (auto mass : masses)
	{
		mass.pos -= COM;
	}

	//x:1, y:2, z:3
	for (auto mass : masses)
	{
		Vector3 pos = mass.pos;
		float m = mass.mass;
		Ibody._11 += m * (pow(pos._2, 2) + pow(pos._3, 2));
		Ibody._22 += m * (pow(pos._1, 2) + pow(pos._3, 2));
		Ibody._33 += m * (pow(pos._1, 2) + pow(pos._2, 2));
		Ibody._12 -= m * pos._1 * pos._2;
		Ibody._13 -= m * pos._1 * pos._3;
		Ibody._23 -= m * pos._2 * pos._3;
	}

	Ibody._21 = Ibody._12;
	Ibody._31 = Ibody._13;
	Ibody._32 = Ibody._23;

	float det;
	Ibodyinv = Ibody.inverse(&det);
}


void Body::start()
{
	update_frame();
}

void Body::update_frame()
{
	D3DXMATRIX transform;
	ZeroMemory(transform, sizeof(D3DXMATRIX));

	transform._11 = R._11; transform._12 = R._21; transform._13 = R._31;
	transform._21 = R._12; transform._22 = R._22; transform._23 = R._32;
	transform._31 = R._13; transform._32 = R._23; transform._33 = R._33;
	
	transform._41 = -COM._1*R._11 - COM._2*R._12 - COM._3*R._13 + x._1; 
	transform._42 = -COM._1*R._21 - COM._2*R._22 - COM._3*R._23 + x._2;
	transform._43 = -COM._1*R._31 - COM._2*R._32 - COM._3*R._33 + x._3;
	transform._44 = 1.f;

	frame_datas.push_back(transform);
}

void Body::update(float deltaTime)
{
	force = Vector3();
	torque = Vector3();

	std::list<std::pair<Vector3, Vector3>> forces;
	interaction->interaction(forces, this);

	//pair1 : target, pair2 : force
	for (auto force_e : forces)
	{
		force += force_e.second;
		torque += Vector3::cross(force_e.first, force_e.second);
	}
	P += force * deltaTime;
	v = P / mass;
	x += v * deltaTime;

	L += torque * deltaTime;
	Iinv = R * Ibodyinv * R.transpose();
	omega = Iinv * L;

	
	q += Quaternion::multiply(0.5f * Quaternion(0.f, omega._1, omega._2, omega._3), q) * deltaTime;
	R = q.normalize().to_matrix();

	update_frame();
	if (post_update != nullptr)
		post_update->post_update();
}

D3DXMATRIX Body::get_render_frame()
{
	int target_frame = PhysicsThread::get_instance().get_render_target_frame();

	if (target_frame > frame_datas.size())
	{
		std::cout << "target_frame > frame_datas";
		return D3DXMATRIX();
	}

	auto itr = frame_datas.begin();
	for (int i = 0; i < target_frame; i++, itr++);
	return *itr;
}

float Body::get_mass()
{
	return mass;
}

Vector3& Body::get_COM()
{
	return COM;
}

Vector3& Body::get_position()
{
	return x;
}

Vector3& Body::get_velocity()
{
	return v;
}

Matrix3x3& Body::get_orientation()
{
	return R;
}

Vector3 Body::get_acceleration()
{
	return (force / mass);
}

void Body::clean_frames(int target_frames)
{
	if (target_frames < 0)
	{
		frame_datas.clear();
	}
	else
	{
		for (int i = 0; i < target_frames; i++)
		{
			frame_datas.erase(frame_datas.begin());
		}
	}
}