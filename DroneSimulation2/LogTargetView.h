#pragma once


// CLogTargetView ���Դϴ�.

class CLogTargetView : public CListView
{
	DECLARE_DYNCREATE(CLogTargetView)

protected:
	CLogTargetView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CLogTargetView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


