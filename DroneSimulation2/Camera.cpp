#include "stdafx.h"
#include "Camera.h"

BasicCamera::BasicCamera(D3DXVECTOR3 _pos, D3DXVECTOR3 _lookat, D3DXVECTOR3 _up) : pos(_pos), lookat(_lookat), up(_up)
{
	update_matrix();
}

void BasicCamera::update_matrix()
{
	D3DXMatrixLookAtRH(&view_matrix, &pos, &lookat, &up);
}

void BasicCamera::setup(IDirect3DDevice9* pDev)
{
	if (updated)
	{
		update_matrix();
		updated = false;
	}
	pDev->SetTransform(D3DTS_VIEW, &view_matrix);
}

D3DXVECTOR3 BasicCamera::get_position()
{
	return pos;
}

D3DXVECTOR3 BasicCamera::get_lookat()
{
	return lookat;
}

void BasicCamera::set_up_vector(D3DXVECTOR3 _up)
{
	up = _up;
	updated = true;
}

void BasicCamera::set_position(D3DXVECTOR3 _pos)
{
	pos = _pos;
	updated = true;
}

FirstPersonCam::FirstPersonCam(D3DXVECTOR3 _pos, float _theta, float _phi) : 
	BasicCamera(_pos, _pos + D3DXVECTOR3(sinf(_theta) * cosf(_phi), sinf(_theta) * sinf(_phi), cosf(_theta)),
		D3DXVECTOR3(0.f, 0.f, 1.f)),
	theta(_theta), phi(_phi)
{
}

void FirstPersonCam::update_matrix()
{
	lookat = pos + D3DXVECTOR3(sinf(theta) * cosf(phi), sinf(theta) * sinf(phi), cosf(theta));

	BasicCamera::update_matrix();
}

void FirstPersonCam::move(int move_type)
{
	D3DXVECTOR3 dir = lookat - pos;
	D3DXVECTOR3 displacement = D3DXVECTOR3(0.f, 0.f, 0.f);

	if ((char)move_type & (char)MoveType::FORWARD || (char)move_type & (char)MoveType::BACKWARD)
	{
		D3DXVECTOR3 dir_hat;
		D3DXVec3Normalize(&dir_hat, &dir);
		if ((char)move_type & (char)MoveType::FORWARD)
		{
			displacement += dir_hat;
		}
		if((char)move_type & (char)MoveType::BACKWARD)
		{
			displacement -= dir_hat;
		}
	}
	if((char)move_type & (char)MoveType::RIGHTWARD || (char)move_type & (char)MoveType::LEFTWARD)
	{
		D3DXVECTOR3 right_hat;
		D3DXVec3Cross(&right_hat, &dir, &up);
		D3DXVec3Normalize(&right_hat, &right_hat);
		if ((char)move_type & (char)MoveType::RIGHTWARD)
		{
			displacement += right_hat;
		}
		if((char)move_type & (char)MoveType::LEFTWARD)
		{
			displacement -= right_hat;
		}
	}

	float len = D3DXVec3Length(&displacement);
	if (fabsf(len-0.f) > FLT_EPSILON)
	{
		displacement *= (FPC_MOVE_FACTOR / len);
		pos += displacement;
	}

	updated = true;
}

void FirstPersonCam::change_direction(float delta_theta, float delta_phi)
{
	theta += delta_theta*FPC_DIR_FACTOR;
	phi += delta_phi*FPC_DIR_FACTOR;

	updated = true;
}
/*
SphericalCam::SphericalCam(D3DXVECTOR3 _target, D3DXVECTOR3 _up, float _r, float _theta, float _phi) :
	target(_target), r(_r), theta(_theta), phi(_phi),
	BasicCamera(D3DXVECTOR3(_r * sinf(_theta) * cosf(_phi),
		_r * sinf(_theta) * sinf(_phi),
		_r * cosf(_theta)),
		_target - D3DXVECTOR3(_r * sinf(_theta) * cosf(_phi),
			_r * sinf(_theta) * sinf(_phi),
			_r * cosf(_theta)),
		up)
{
}

void SphericalCam::move(MoveType type)
{
	D3DXVECTOR3 displacement = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXVECTOR3 dir_shade = dir;
	dir_shade.z = 0;
	if ((char)type & (char)MoveType::FORWARD || (char)type & (char)MoveType::BACKWARD)
	{
		D3DXVECTOR3 dir_hat;
		D3DXVec3Normalize(&dir_hat, &dir_shade);
		if ((char)type & (char)MoveType::FORWARD)
		{
			displacement += dir_hat;
		}
		if ((char)type & (char)MoveType::BACKWARD)
		{
			displacement -= dir_hat;
		}
	}
	if ((char)type & (char)MoveType::RIGHTWARD || (char)type & (char)MoveType::LEFTWARD)
	{
		D3DXVECTOR3 right_hat;
		D3DXVECTOR3 temp_up(0.f, 0.f, 1.f);
		D3DXVec3Cross(&right_hat, &dir_shade, &temp_up);
		D3DXVec3Normalize(&right_hat, &right_hat);
		if ((char)type & (char)MoveType::RIGHTWARD)
		{
			displacement += right_hat;
		}
		if ((char)type & (char)MoveType::LEFTWARD)
		{
			displacement -= right_hat;
		}
	}

	float len = D3DXVec3Length(&displacement);
	if (fabsf(len - 0.f) > FLT_EPSILON)
	{
		displacement *= (SPH_MOVE_FACTOR / len);
		pos += displacement;
		update_matrix();
	}
}

void SphericalCam::update_matrix()
{
	dir = -D3DXVECTOR3(r * sinf(theta) * cosf(phi),
		r * sinf(theta) * sinf(phi),
		r * cosf(theta));

	pos = -dir + target;

	BasicCamera::update_matrix();
}

void SphericalCam::change_radius(float delta_radius)
{
	r += delta_radius;
	updated = true;
}

void SphericalCam::change_direction(float delta_theta, float delta_phi)
{
	theta += delta_theta;
	phi += delta_phi;
	updated = true;
}

void SphericalCam::set_target(D3DXVECTOR3 _target)
{
	target = _target;

	pos = -dir + target;
	updated = true;
}*/