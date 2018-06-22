
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "DroneSimulation2.h"
#include "ScenarioSetupView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CONTROLLER, &CMainFrame::OnViewController)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame() : m_pControllerDlg(NULL), m_plogframe(NULL)
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
	if (m_pControllerDlg != NULL)
	{
		m_pControllerDlg->DestroyWindow();
		delete m_pControllerDlg;
	}

	if (m_plogframe != NULL)
	{
		m_plogframe->DestroyWindow();
		//delete m_plogframe;
	}
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: ���� ������ ��ŷ�� �� ���� �Ϸ��� �� �� ���� �����Ͻʽÿ�.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//Automatically Open Controller Dialog(Modeless)
	if (m_pControllerDlg == NULL)
	{
		m_pControllerDlg = new CControllerDlg(this);
		m_pControllerDlg->Create(IDD_CONTROLLER, this);
	}
	m_pControllerDlg->ShowWindow(SW_SHOW);



	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	cs.style ^= WS_MAXIMIZEBOX;
	cs.style ^= WS_MINIMIZEBOX;

	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (!m_splitterwnd.CreateStatic(this, 1, 2)) {
		AfxMessageBox(L"MainFrm.cpp : CMainFrame::OnCreateClient / m_splitterwnd.CreateStatic");
		return FALSE;
	}

	int scwidth = GetSystemMetrics(SM_CXFULLSCREEN);

	if (!m_splitterwnd.CreateView(0, 1, RUNTIME_CLASS(CScenarioSetupView), CSize((UINT)(scwidth * 0.1f), 0), pContext)) {
		AfxMessageBox(L"MainFrm.cpp : CMainFrame::OnCreateClient / m_splitterwnd.CreateView(0,1)");
		return FALSE;
	}

	if (!m_splitterwnd.CreateView(0, 0, RUNTIME_CLASS(CDroneSimulation2View), CSize((UINT)(scwidth * 0.9f), 0), pContext)) {
		AfxMessageBox(L"MainFrm.cpp : CMainFrame::OnCreateClient / m_splitterwnd.CreateView(0,0)");
		return FALSE;
	}



	CDroneSimulation2View* pView = (CDroneSimulation2View*)m_splitterwnd.GetPane(0, 0);
	/*int res = pView->initialize_d3d();*/


	m_plogframe = new CLogFrame((CDroneSimulation2Doc*)pContext->m_pCurrentDoc);

	LPCTSTR classname = AfxRegisterWndClass(CS_CLASSDC);
	m_plogframe->Create(classname, L"Log Window");

	m_plogframe->ShowWindow(SW_MAXIMIZE);
	m_plogframe->UpdateWindow();

	return TRUE;
}

CDroneSimulation2View* CMainFrame::getmainview()
{
	return (CDroneSimulation2View*)m_splitterwnd.GetPane(0, 0);
}

void CMainFrame::OnViewController()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(m_pControllerDlg != NULL)
		m_pControllerDlg->ShowWindow(SW_SHOW);
}
