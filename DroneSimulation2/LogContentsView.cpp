// LogContentsView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "LogContentsView.h"


// CLogContentsView

IMPLEMENT_DYNCREATE(CLogContentsView, CView)

CLogContentsView::CLogContentsView()
{

}

CLogContentsView::~CLogContentsView()
{
}

BEGIN_MESSAGE_MAP(CLogContentsView, CView)
END_MESSAGE_MAP()


// CLogContentsView 그리기입니다.

void CLogContentsView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CLogContentsView 진단입니다.

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


// CLogContentsView 메시지 처리기입니다.
