
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
extern DWORD WM_ret;


class CMainFrame : public CWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:
private:
	wchar_t remmi[1618];
	CWinThread *rew;
	CWinThread *rewh;
	int trigger=17;
	
// Operations
public:

// Overrides
public:

// Implementation
public:
	virtual ~CMainFrame();



// Generated message map functions
protected:

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void tr();
	afx_msg void w();
	afx_msg void OnDestroy();
protected:

public:
protected:
	afx_msg LRESULT OnCtlcolorstatic(WPARAM wParam, LPARAM lParam);
};
extern HINSTANCE h;

