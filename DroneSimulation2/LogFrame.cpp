// LogFrame.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "LogFrame.h"


// CLogFrame

IMPLEMENT_DYNCREATE(CLogFrame, CFrameWnd)

CLogFrame::CLogFrame()
{
}

CLogFrame::CLogFrame(CDroneSimulation2Doc* targetdoc) : m_ptargetdoc(targetdoc)
{

}

CLogFrame::~CLogFrame()
{
}


BEGIN_MESSAGE_MAP(CLogFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CLogFrame 메시지 처리기입니다.


int CLogFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


BOOL CLogFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (!m_splitterwnd.CreateStatic(this, 1, 2)) {
		AfxMessageBox(L"LogFrame.cpp : CLogFrame::OnCreateClient / m_splitterwnd.CreateStatic");
		return FALSE;
	}

	int scwidth = GetSystemMetrics(SM_CXFULLSCREEN);

	CCreateContext newContext;
	newContext.m_pNewViewClass = NULL;
	newContext.m_pNewDocTemplate = NULL;
	newContext.m_pLastView = NULL;
	newContext.m_pCurrentFrame = NULL;
	newContext.m_pCurrentDoc = m_ptargetdoc;
	if (!m_splitterwnd.CreateView(0, 0, RUNTIME_CLASS(CLogTargetView), CSize((UINT)(scwidth * 0.1f), 0), &newContext)) {
		AfxMessageBox(L"LogFrame.cpp : CLogFrame::OnCreateClient / m_splitterwnd.CreateView(CLogTargetView)");
		return FALSE;
	}

	if (!m_splitterwnd.CreateView(0, 1, RUNTIME_CLASS(CLogContentsView), CSize((UINT)(scwidth * 0.9f), 0), &newContext)) {
		AfxMessageBox(L"LogFrame.cpp : CLogFrame::OnCreateClient / m_splitterwnd.CreateView(CLogContentsView)");
		return FALSE;
	}

	pView = (CLogContentsView*)m_splitterwnd.GetPane(0, 1);

	return TRUE;
}

void CLogFrame::initview()
{
	pView->test();
}