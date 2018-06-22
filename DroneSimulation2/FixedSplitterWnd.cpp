// FixedSplitterWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "FixedSplitterWnd.h"


// CFixedSplitterWnd

IMPLEMENT_DYNAMIC(CFixedSplitterWnd, CSplitterWnd)

CFixedSplitterWnd::CFixedSplitterWnd()
{

}

CFixedSplitterWnd::~CFixedSplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CFixedSplitterWnd, CSplitterWnd)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()



// CFixedSplitterWnd 메시지 처리기입니다.




LRESULT CFixedSplitterWnd::OnNcHitTest(CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return HTNOWHERE;
}
