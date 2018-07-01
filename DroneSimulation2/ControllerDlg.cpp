// ControllerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "DroneSimulation2Doc.h"
#include "DroneSimulation2View.h"
#include "ControllerDlg.h"
#include "afxdialogex.h"
#include <windowsx.h>


// CControllerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CControllerDlg, CDialogEx)

CControllerDlg::CControllerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONTROLLER, pParent)
{

}

CControllerDlg::~CControllerDlg()
{
}

void CControllerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON6, btn_up);
}


BEGIN_MESSAGE_MAP(CControllerDlg, CDialogEx)
END_MESSAGE_MAP()


// CControllerDlg 메시지 처리기입니다.



BOOL CControllerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		RECT rect;
		POINT point;

		btn_up.GetWindowRect(&rect);
		ScreenToClient(&rect);
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (PtInRect(&rect, point))
		{
			((CDroneSimulation2View*)m_pParentWnd)->PostMessage(WM_UPCOMMAND);
		}
	}

	if (pMsg->message == WM_LBUTTONUP)
	{
		RECT rect;
		POINT point;

		btn_up.GetWindowRect(&rect);
		ScreenToClient(&rect);
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (PtInRect(&rect, point))
		{
			((CDroneSimulation2View*)m_pParentWnd)->PostMessage(WM_CMDCANCEL);
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
