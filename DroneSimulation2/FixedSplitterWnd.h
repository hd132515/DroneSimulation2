#pragma once


// CFixedSplitterWnd

class CFixedSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CFixedSplitterWnd)

public:
	CFixedSplitterWnd();
	virtual ~CFixedSplitterWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
};


