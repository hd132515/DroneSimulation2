#pragma once


// CLogContentsView ���Դϴ�.

class CLogContentsView : public CView
{
	DECLARE_DYNCREATE(CLogContentsView)

protected:
	CLogContentsView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CLogContentsView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


