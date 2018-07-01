// ControllerDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "DroneSimulation2Doc.h"
#include "DroneSimulation2View.h"
#include "ControllerDlg.h"
#include "afxdialogex.h"
#include <windowsx.h>


// CControllerDlg ��ȭ �����Դϴ�.

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


// CControllerDlg �޽��� ó�����Դϴ�.



BOOL CControllerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
