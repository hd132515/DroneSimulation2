#pragma once
#include "afxwin.h"

#define WM_CMDCANCEL WM_USER+99
#define WM_UPCOMMAND WM_USER+100
#define WM_DOWNCOMMAND WM_USER+101


// CControllerDlg ��ȭ �����Դϴ�.

class CControllerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CControllerDlg)

public:
	CControllerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CControllerDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTROLLER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CButton btn_up;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
