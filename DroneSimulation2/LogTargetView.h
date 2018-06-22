#pragma once


// CLogTargetView 뷰입니다.

class CLogTargetView : public CListView
{
	DECLARE_DYNCREATE(CLogTargetView)

protected:
	CLogTargetView();           // 동적 만들기에 사용되는 protected 생성자입니다.
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


