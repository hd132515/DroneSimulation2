
// DroneSimulation2View.h : CDroneSimulation2View 클래스의 인터페이스
//

#pragma once

#include "Axis.h"
#include "Plane.h"
#include "Grid.h"
#include "Camera.h"
#include "Direct3DView.h"
#include "SceneNode.h"
#include "Drone.h"

class CDroneSimulation2View : public CDirect3DView
{
private:
	D3DLIGHT9 main_light;
	FirstPersonCam camera;
	BasicCamera* active_camera;
	Grid* grid;
	Plane* plane;
	Axis axis;
	SceneNode* world_root;
	Drone drone;

	bool left_clicked;
	CPoint old_pt;

protected: // serialization에서만 만들어집니다.
	CDroneSimulation2View();
	DECLARE_DYNCREATE(CDroneSimulation2View)

// 특성입니다.
public:
	CDroneSimulation2Doc* GetDocument() const;

// 작업입니다.
public:

	virtual void prepare();
	virtual void process_input();
	virtual void render_process();

// 재정의입니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CDroneSimulation2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
	virtual void PostNcDestroy();
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // DroneSimulation2View.cpp의 디버그 버전
inline CDroneSimulation2Doc* CDroneSimulation2View::GetDocument() const
   { return reinterpret_cast<CDroneSimulation2Doc*>(m_pDocument); }
#endif

