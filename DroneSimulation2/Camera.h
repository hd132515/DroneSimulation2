#pragma once

#include <d3dx9.h>


//class BasicCamera
// This class is camera class providing view matrix to Direct3D device.
// This camera class doesn't support movement.
// So can be used to record.
class BasicCamera
{
public:
	BasicCamera(D3DXVECTOR3 _pos, D3DXVECTOR3 _lookat, D3DXVECTOR3 _up);
private:

protected:
	bool updated = false;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 lookat;
	D3DXVECTOR3 up;

	D3DXMATRIX view_matrix;

protected:
	virtual void update_matrix();

public:
	void setup(IDirect3DDevice9* pDev);

	D3DXVECTOR3 get_position();
	D3DXVECTOR3 get_lookat();

	void set_up_vector(D3DXVECTOR3 _up);
	void set_position(D3DXVECTOR3 _pos);
};

enum class MoveType {
	FORWARD = 1, BACKWARD=2, RIGHTWARD=4, LEFTWARD=8
};


//class FirstPersonCam
// This class is camera class inheriting from BasicCamera
// This camera class support first-person view movement.
// This make users control the camera as their eye moves.
// <coordinate>
// pos : camera position in cartesian
// theta : view direction in spherical coordinate from z-axis RH
// phi : view direction in spherical coordinate from x-axis about z-axis RH
class FirstPersonCam : public BasicCamera
{
public:
public:
	FirstPersonCam(D3DXVECTOR3 _pos, float _theta, float _phi);
private:
	float theta, phi;

protected:
	virtual void update_matrix();
public:
	void move(int move_type);

	void change_direction(float delta_theta, float delta_phi);

};

#define FPC_MOVE_FACTOR 0.1f
#define FPC_DIR_FACTOR 0.005f


//class SphericalCam
// This class is camera class inheriting from BasicCamera
// This camera class support spherical coordinate movement.
// This make users concentrate the target.
// The theta axis is z axis
class SphericalCam : public BasicCamera
{
public:
	SphericalCam(D3DXVECTOR3 _target, D3DXVECTOR3 _up, float _r, float _theta, float _phi);
private:
	D3DXVECTOR3 target;
	float r, theta, phi;
protected:

protected:
	virtual void update_matrix();
public:
	void move(MoveType type);
	void change_radius(float delta_radius);
	void change_direction(float delta_theta, float delta_phi);
	void set_target(D3DXVECTOR3 _target);
};

#define SPH_MOVE_FACTOR 1.f
#define SPH_DIR_FACTOR 1.f