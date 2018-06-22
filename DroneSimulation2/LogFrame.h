#pragma once

#include "DroneSimulation2Doc.h"
#include "FixedSplitterWnd.h"

// CLogFrame �������Դϴ�.

class CLogFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CLogFrame)
public:
	CLogFrame();
	CLogFrame(CDroneSimulation2Doc* ptargetdoc);           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CLogFrame();

private:
	CDroneSimulation2Doc* m_ptargetdoc;
	CFixedSplitterWnd m_splitterwnd;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


