// FixedSplitterWnd.cpp : ���� �����Դϴ�.
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



// CFixedSplitterWnd �޽��� ó�����Դϴ�.




LRESULT CFixedSplitterWnd::OnNcHitTest(CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return HTNOWHERE;
}
