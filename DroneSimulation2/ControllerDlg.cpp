// ControllerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "ControllerDlg.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(CControllerDlg, CDialogEx)
END_MESSAGE_MAP()


// CControllerDlg 메시지 처리기입니다.
