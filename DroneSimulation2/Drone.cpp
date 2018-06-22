#include "Drone.h"

extern IDirect3DDevice9* g_pd3dDevice;

void Drone::build_structure(std::list<Mass>& masses, Vector3** COM)
{
	float arm_dist = 0.225f / 2 / 1.4142f;
	float mtr_dist = 0.225f / 1.4142f;

	masses.push_back({ Vector3(arm_dist, arm_dist, 0.01f), 0.35f });
	masses.push_back({ Vector3(-arm_dist, arm_dist, 0.01f), 0.35f });
	masses.push_back({ Vector3(-arm_dist, -arm_dist, 0.01f), 0.35f });
	masses.push_back({ Vector3(arm_dist, -arm_dist, 0.01f), 0.35f });

	motorpos[0] = Vector3(mtr_dist, mtr_dist, 0.023f);
	motorpos[1] = Vector3(-mtr_dist, mtr_dist, 0.023f);
	motorpos[2] = Vector3(-mtr_dist, -mtr_dist, 0.023f);
	motorpos[3] = Vector3(mtr_dist, -mtr_dist, 0.023f);

	masses.push_back({ motorpos[0], 0.05f });
	masses.push_back({ motorpos[1], 0.05f });
	masses.push_back({ motorpos[2], 0.05f });
	masses.push_back({ motorpos[3], 0.05f });

	//noise
	masses.push_back({ Vector3(0.0154f, 0.00846f, 0.002f), 0.5f });

	*COM = &(this->COM);
}

Drone::Drone() : RigidBody(), standard(0.f, 0.f, 1.f)
{
	ready = false;
	observation_time = 0.f;
}

void Drone::initialize()
{
	float angle = 3.14f/4.f;
	rb_init(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f), Vector3(cosf(angle), sinf(angle), 0.f), angle,
		Vector3(0.f, 0.f, 0.f));

	for (int i = 0; i < 4; i++)
	{
		motorpos[i] -= COM;
	}
	D3DXVECTOR3 source[] =
	{
		// 좌
		D3DXVECTOR3(0.225f,-0.01f, 0.02f),
		D3DXVECTOR3(0.225f,-0.01f,0.0f),
		D3DXVECTOR3(-0.225f,-0.01f,0.0f),

		D3DXVECTOR3(-0.225f,-0.01f,0.0f),
		D3DXVECTOR3(-0.225f,-0.01f, 0.02f),
		D3DXVECTOR3(0.225f,-0.01f, 0.02f),

		// 우
		D3DXVECTOR3(-0.225f, 0.01f, 0.02f),
		D3DXVECTOR3(-0.225f, 0.01f,0.0f),
		D3DXVECTOR3(0.225f, 0.01f,0.0f),

		D3DXVECTOR3(0.225f, 0.01f,0.0f),
		D3DXVECTOR3(0.225f, 0.01f, 0.02f),
		D3DXVECTOR3(-0.225f, 0.01f, 0.02f),

		// 뒤
		D3DXVECTOR3(-0.225f,-0.01f, 0.02f),
		D3DXVECTOR3(-0.225f,-0.01f,0.0f),
		D3DXVECTOR3(-0.225f, 0.01f,0.0f),

		D3DXVECTOR3(-0.225f, 0.01f,0.0f),
		D3DXVECTOR3(-0.225f, 0.01f, 0.02f),
		D3DXVECTOR3(-0.225f,-0.01f, 0.02f),

		// 앞
		D3DXVECTOR3(0.225f, 0.01f, 0.02f),
		D3DXVECTOR3(0.225f, 0.01f,0.0f),
		D3DXVECTOR3(0.225f,-0.01f,0.0f),

		D3DXVECTOR3(0.225f,-0.01f,0.0f),
		D3DXVECTOR3(0.225f,-0.01f, 0.02f),
		D3DXVECTOR3(0.225f, 0.01f, 0.02f),

		// 상
		D3DXVECTOR3(0.225f, 0.01f, 0.02f),
		D3DXVECTOR3(0.225f,-0.01f, 0.02f),
		D3DXVECTOR3(-0.225f,-0.01f, 0.02f),

		D3DXVECTOR3(-0.225f,-0.01f, 0.02f),
		D3DXVECTOR3(-0.225f, 0.01f, 0.02f),
		D3DXVECTOR3(0.225f, 0.01f, 0.02f),

		// 하
		D3DXVECTOR3(0.225f,-0.01f,0.0f),
		D3DXVECTOR3(0.225f, 0.01f,0.0f),
		D3DXVECTOR3(-0.225f, 0.01f,0.0f),

		D3DXVECTOR3(-0.225f, 0.01f,0.0f),
		D3DXVECTOR3(-0.225f,-0.01f,0.0f),
		D3DXVECTOR3(0.225f,-0.01f,0.0f)

	};

	D3DXMATRIX rotater;
	D3DXVECTOR4 droneStrc[36];
	D3DXVECTOR4 droneCOM(COM._1, COM._2, COM._3, 1.f);
	for (int k = 0; k < 2; k++)
	{
		if (k == 0)
		{
			D3DXMatrixRotationZ(&rotater, D3DX_PI / 4);
			D3DXMatrixTranspose(&rotater, &rotater);
		}
		if (k == 1)
		{
			D3DXMatrixRotationZ(&rotater, -D3DX_PI / 4);
			D3DXMatrixTranspose(&rotater, &rotater);
		}

		for (int i = 0; i < 36; i++)
		{
			D3DXVec3Transform(&droneStrc[i], &source[i], &rotater);
			droneStrc[i] -= droneCOM;
		}

		g_pd3dDevice->CreateVertexBuffer(36 * sizeof(Vertex), 0, D3DFVF_DEFAULTVTX, D3DPOOL_MANAGED, &pVB[k], NULL);

		Vertex* vtx;
		pVB[k]->Lock(0, 36 * sizeof(Vertex), (void**)&vtx, 0);
		for (int i = 0; i < 36; i++)
		{
			vtx[i].x = droneStrc[i].x;
			vtx[i].y = droneStrc[i].y;
			vtx[i].z = droneStrc[i].z;
			if (18 <= i && i < 24)
			{
				if(k == 1)
					vtx[i].color = 0xFFFF0000;
				if (k == 0)
					vtx[i].color = 0xFF00FF00;
			}
			else vtx[i].color = 0xFF777777;
		}

		pVB[k]->Unlock();
	}
	D3DXMatrixIdentity(&matTrans);
}

void Drone::interaction(std::list<std::pair<Vector3, Vector3>>& forces)
{
	forces.emplace_back(Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, -9.8f*mass));

	Vector3 temp_motorpos;
	Vector3 temp_standard = R * standard;

	for (int i = 0; i < 4; i++)
	{
		temp_motorpos = R * motorpos[i];
		forces.emplace_back(temp_motorpos, temp_standard * prop[i]);
	}
}

void Drone::update(float deltaTime)
{
	RigidBody::update(deltaTime);

	if (0.001f >= x._3 && v._3 < 0.f)
	{
		x._3 = 0.f;
		P._3 = 0.f;

		q = Quaternion(1.f, 0.f, 0.f, 0.f);
		R = Matrix3x3::rotation(Vector3(), 0.f);
		L = Vector3();
	}

	/*x._3 = 1.f;
	x._2 = 0.f;
	x._1 = 0.f;*/

	D3DXMATRIX rot;
	memset(&rot, 0, sizeof(D3DXMATRIX));
	rot._11 = R._11; rot._12 = R._12; rot._13 = R._13;
	rot._21 = R._21; rot._22 = R._22; rot._23 = R._23;
	rot._31 = R._31; rot._32 = R._32; rot._33 = R._33;
	rot._44 = 1.f;
	D3DXMatrixTranspose(&rot, &rot);


	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, x._1, x._2, x._3);
	matTrans = rot * trans;

	observation_time += deltaTime;
	ready = true;
}

extern D3DXMATRIX matShad;

void Drone::render()
{
	D3DXMATRIX W = matTrans * matShad;

	g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILREF, 0x0);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILMASK, 0xFFFFFFFF);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xFFFFFFFF);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

	g_pd3dDevice->SetTransform(D3DTS_WORLD, &W);

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));

	mtrl.Diffuse.a = 1.f;
	g_pd3dDevice->SetMaterial(&mtrl);

	for (int i = 0; i < 2; i++)
	{
		g_pd3dDevice->SetStreamSource(0, pVB[i], 0, sizeof(Vertex));
		g_pd3dDevice->SetFVF(D3DFVF_DEFAULTVTX);
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);
	}

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);


	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matTrans);

	g_pd3dDevice->SetTexture(0, 0);
	for (int i = 0; i < 2; i++)
	{
		g_pd3dDevice->SetStreamSource(0, pVB[i], 0, sizeof(Vertex));
		g_pd3dDevice->SetFVF(D3DFVF_DEFAULTVTX);
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);
	}
}

void Drone::setProp(float* prop)
{
	for (int i = 0; i < 4; i++)
	{
		this->prop[i] = prop[i];
	}
}

void Drone::measuring()
{
	x = Vector3(0.f, 0.f, 1.f);
	v = Vector3();
	q = Quaternion(1.f, 0.f, 0.f, 0.f);
	L = Vector3();
}


void Drone::getMotorPos(Vector3* vecs)
{
	memcpy(vecs, motorpos, sizeof(Vector3) * 4);
}

float Drone::getObsTime()
{
	float retval = observation_time;
	if (observation_time == 0.f)
		retval = -1.f;
	else
		observation_time = 0.f;
	return retval;
}

bool Drone::isReady()
{
	return ready;
}

