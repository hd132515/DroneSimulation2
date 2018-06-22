// LogTargetView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "LogTargetView.h"


// CLogTargetView

IMPLEMENT_DYNCREATE(CLogTargetView, CListView)

CLogTargetView::CLogTargetView()
{

}

CLogTargetView::~CLogTargetView()
{
}

BEGIN_MESSAGE_MAP(CLogTargetView, CListView)
END_MESSAGE_MAP()


// CLogTargetView 진단입니다.

#ifdef _DEBUG
void CLogTargetView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CLogTargetView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLogTargetView 메시지 처리기입니다.
