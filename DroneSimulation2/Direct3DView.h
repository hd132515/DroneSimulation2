#pragma once


// CDirect3DView 뷰입니다.

#include <d3dx9.h>

class CDirect3DView : public CView
{
	DECLARE_DYNCREATE(CDirect3DView)

protected:
	CDirect3DView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CDirect3DView();

	virtual void OnDraw(CDC* /*pDC*/);
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	IDirect3DDevice9* m_pDev;
	D3DXMATRIX projection;

public:
	//<summary>
	// initializing Direct3D Base Handles
	// called by MainFrame
	//<returns>
	// -1 : failed
	// 0 : succeeded
	int initialize_d3d();
	virtual void prepare();

	virtual void process_input();
	void pre_render();
	virtual void render_process();
	void post_render();
	void release_all();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
};


