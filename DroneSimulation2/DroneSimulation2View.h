
// DroneSimulation2View.h : CDroneSimulation2View Ŭ������ �������̽�
//

#pragma once

#include "Axis.h"
#include "Plane.h"
#include "Grid.h"
#include "Camera.h"
#include "Direct3DView.h"
#include "Box.h"

class CDroneSimulation2View : public CDirect3DView
{
private:
	D3DLIGHT9 main_light;
	FirstPersonCam camera;
	BasicCamera* active_camera;
	Grid grid;
	Plane plane;
	Axis axis;
	Box box;

	bool left_clicked;
	CPoint old_pt;

protected: // serialization������ ��������ϴ�.
	CDroneSimulation2View();
	DECLARE_DYNCREATE(CDroneSimulation2View)

// Ư���Դϴ�.
public:
	CDroneSimulation2Doc* GetDocument() const;

// �۾��Դϴ�.
public:

	virtual void prepare();
	virtual void process_input();
	virtual void render_process();

// �������Դϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CDroneSimulation2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
};

#ifndef _DEBUG  // DroneSimulation2View.cpp�� ����� ����
inline CDroneSimulation2Doc* CDroneSimulation2View::GetDocument() const
   { return reinterpret_cast<CDroneSimulation2Doc*>(m_pDocument); }
#endif

