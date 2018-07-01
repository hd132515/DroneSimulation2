#include "stdafx.h"
#include "Drone.h"
#include "Box.h"
#include "PhysicsThread.h"
#include "DroneInterface.h"

Drone::Drone() : GeneralObject("drone")
{
}

Drone::~Drone()
{
}

int Drone::prepare_scenenode(IDirect3DDevice9* pDev)
{
	D3DXMATRIX transform;

	node->material.Ambient.a = 1.f;
	node->material.Ambient.r = node->material.Ambient.g = node->material.Ambient.b = 0.1f;
	node->material.Specular.a = node->material.Specular.r = node->material.Specular.g = node->material.Specular.b = 0.2f;
	node->material.Power = 10.f;

	node->register_render_state(D3DRS_LIGHTING, TRUE);
	node->register_render_state(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	
	BoxGeometry* diag13 = new BoxGeometry(0.45f, 0.02f, 0.02f);
	if (diag13->prepare(pDev)) return -1;
	{
		D3DXMATRIX rotation;
		D3DXMatrixRotationZ(&rotation, -D3DX_PI / 4.f);
		transform = rotation;
	}
	SceneNode* diag13_n = new SceneNode();
	diag13_n->register_geometry(diag13);
	diag13_n->register_transform(transform);
	memcpy(&diag13_n->material, &node->material, sizeof(D3DMATERIAL9));



	BoxGeometry* diag24 = new BoxGeometry(0.45f, 0.02f, 0.02f);
	if (diag24->prepare(pDev)) return -1;
	{
		D3DXMATRIX rotation;
		D3DXMatrixRotationZ(&rotation, D3DX_PI / 4.f);
		transform = rotation;
	}
	SceneNode* diag24_n = new SceneNode();
	diag24_n->register_geometry(diag24);
	diag24_n->register_transform(transform);
	memcpy(&diag24_n->material, &node->material, sizeof(D3DMATERIAL9));

	BoxGeometry* prop1 = new BoxGeometry(0.11f, 0.01f, 0.01f);
	if (prop1->prepare(pDev)) return -1;
	SceneNode* prop1_n = new SceneNode();
	prop1_n->register_geometry(prop1);
	memcpy(&prop1_n->material, &node->material, sizeof(D3DMATERIAL9));
	prop1_n->material.Ambient.r = 1.f;

	BoxGeometry* prop2 = new BoxGeometry(0.11f, 0.01f, 0.01f);
	if (prop2->prepare(pDev)) return -1;
	SceneNode* prop2_n = new SceneNode();
	prop2_n->register_geometry(prop2);
	memcpy(&prop2_n->material, &node->material, sizeof(D3DMATERIAL9));
	prop2_n->material.Ambient.g = 1.f;

	BoxGeometry* prop3 = new BoxGeometry(0.11f, 0.01f, 0.01f);
	if (prop3->prepare(pDev)) return -1;
	SceneNode* prop3_n = new SceneNode();
	prop3_n->register_geometry(prop3);
	memcpy(&prop3_n->material, &node->material, sizeof(D3DMATERIAL9));
	prop3_n->material.Ambient.b = 1.f;

	BoxGeometry* prop4 = new BoxGeometry(0.11f, 0.01f, 0.01f);
	if (prop4->prepare(pDev)) return -1;
	SceneNode* prop4_n = new SceneNode();
	prop4_n->register_geometry(prop4);
	memcpy(&prop4_n->material, &node->material, sizeof(D3DMATERIAL9));

	{
		D3DXMATRIX trans1;
		D3DXMatrixTranslation(&trans1, 0.225f, 0.f, 0.01f + 0.005f);
		D3DXMATRIX trans2;
		D3DXMatrixTranslation(&trans2, -0.225f, 0.f, 0.01f + 0.005f);

		D3DXMATRIX rot1, rot2;
		D3DXMatrixRotationZ(&rot1, -D3DX_PI / 4.f);
		D3DXMatrixRotationZ(&rot2, D3DX_PI / 4.f);

		prop1_n->register_transform(trans1*rot1);
		prop2_n->register_transform(trans1*rot2);
		prop3_n->register_transform(trans2*rot1);
		prop4_n->register_transform(trans2*rot2);
	}

	node->register_child_node(diag13_n);
	node->register_child_node(diag24_n);
	node->register_child_node(prop1_n);
	node->register_child_node(prop2_n);
	node->register_child_node(prop3_n);
	node->register_child_node(prop4_n);

	return 0;
}

int Drone::prepare_body()
{
	MassList masses;

	float diag = 0.45f;
	float mtr_coord = diag / 2.f / 1.4142f;
	float arm_coord = mtr_coord / 2.f;


	//Local Coordinate
	masses.push_back({ Vector3(arm_coord, arm_coord, 0.005f), 0.2f });
	masses.push_back({ Vector3(-arm_coord, arm_coord, 0.005f), 0.2f });
	masses.push_back({ Vector3(-arm_coord, -arm_coord, 0.005f), 0.2f });
	masses.push_back({ Vector3(arm_coord, -arm_coord, 0.005f), 0.2f });
	masses.push_back({ Vector3(0.f, 0.f, 0.f), 0.2f });

	motorpos[0] = Vector3(mtr_coord, mtr_coord, 0.01f);
	motorpos[1] = Vector3(-mtr_coord, mtr_coord, 0.01f);
	motorpos[2] = Vector3(-mtr_coord, -mtr_coord, 0.01f);
	motorpos[3] = Vector3(mtr_coord, -mtr_coord, 0.01f);

	masses.push_back({ motorpos[0], 0.05f });
	masses.push_back({ motorpos[1], 0.05f });
	masses.push_back({ motorpos[2], 0.05f });
	masses.push_back({ motorpos[3], 0.05f });

	//wires and esc module, controller module etc..
	masses.push_back({ Vector3(0.008f, -0.001f, 0.007f) , 0.1f });
	//masses.push_back({ Vector3(0.01f, -0.01f, 0.07f) , 0.1f });

	body->body_init(this, this, masses, Vector3(), Vector3(), Vector3(), 0.f, Vector3());


	for (int i = 0; i < 4; i++)
	{
		motorpos[i] -= body->get_COM();
	}

	return 0;
}

void Drone::interaction(ForceList& forces, Body* body)
{
	//Local
	forces.emplace_back(Vector3(), Vector3(0.f, 0.f, -9.8f*body->get_mass()));

	Vector3 temp_motorpos;
	Vector3 prop_dir = Vector3(body->get_orientation()._13, body->get_orientation()._23, body->get_orientation()._33);

	for (int i = 0; i < 4; i++)
	{
		temp_motorpos = body->get_orientation()* motorpos[i];
		forces.emplace_back(temp_motorpos, body->get_orientation() * (prop_dir * motor[i].get_output()));
	}

	if (body->get_position()._3 < 0.f)
	{
		Vector3 new_pos = body->get_position();
		new_pos._3 = 0.f;
		body->set_position(new_pos);
		Vector3 new_vel = body->get_velocity();
		new_vel._3 = 0.f;
		body->set_velocity(new_vel);
	}
}

void Drone::post_update()
{
	accelerometer.update(body->get_acceleration(), body->get_orientation());
}

Servo* Drone::get_motor_array()
{
	return motor;
}

BluetoothModule& Drone::get_bluetooth()
{
	return blmodule;
}

Accelerometer& Drone::get_accelerometer()
{
	return accelerometer;
}