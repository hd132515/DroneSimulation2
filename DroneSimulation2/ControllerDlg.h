#pragma once


// CControllerDlg 대화 상자입니다.

class CControllerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CControllerDlg)

public:
	CControllerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CControllerDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTROLLER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
