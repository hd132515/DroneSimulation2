// LogContentsView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "LogContentsView.h"


// CLogContentsView

IMPLEMENT_DYNCREATE(CLogContentsView, CView)

CLogContentsView::CLogContentsView() : graph(nullptr)
{

}

CLogContentsView::~CLogContentsView()
{
	if (graph != nullptr)
	{
		delete graph;
	}
}

BEGIN_MESSAGE_MAP(CLogContentsView, CView)
END_MESSAGE_MAP()


// CLogContentsView �׸����Դϴ�.

void CLogContentsView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CLogContentsView �����Դϴ�.

#ifdef _DEBUG
void CLogContentsView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CLogContentsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLogContentsView �޽��� ó�����Դϴ�.
void CLogContentsView::test()
{
	graph = new COScopeCtrl();

	RECT rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	graph->Create(WS_VISIBLE | WS_CHILD, rect, this);
	graph->InvalidateCtrl();
}
